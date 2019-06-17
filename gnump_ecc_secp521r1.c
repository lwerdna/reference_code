/* demonstrate GNU MP big integer library by implementing ECC using secp521 params

	doc:
		secp521r1 from SEC2: Recommended Elliptic Curve Domain Parameters
		by Certicom Research, see: http://www.secg.org/sec2-v2.pdf

	compile with:
		gcc -O0 -g secp521_gnump.c -o test -lgmp

	notes:
		probably some memory leaks in here, be sure to mpz_init() and mpz_clear()

	history:
		2017-07-04 first version

	flman!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <gmp.h>

/* define two types: curves, points */
typedef struct ecurve_ {
	mpz_t p, a, b;
} ecurve;

typedef struct epoint_ {
	bool is_ident;
	mpz_t x, y;
} epoint;

/* operations on our point type */
void epoint_init(epoint *p);
void epoint_clear(epoint *p);
void epoint_copy(epoint *p, epoint *q);
void epoint_from_mpz_ts(epoint *p, mpz_t x, mpz_t y);
void epoint_from_str16s(epoint *p, char *x, char *y);
int epoint_cmp(epoint *p, epoint *q);
void epoint_print(epoint *p);
void epoint_println(epoint *p);

/* operations on our curve type */
void ecurve_init(ecurve *e);
void ecurve_clear(ecurve *e);
void ecurve_set(ecurve *e, mpz_t a, mpz_t b, mpz_t p);
bool ecurve_iselem(ecurve *e, epoint *p);
void ecurve_add(ecurve *curve, epoint *s, epoint *p, epoint *q);
void ecurve_mul(ecurve *curve, epoint *q, epoint *p, mpz_t n_);
bool ecurve_test_opposites(ecurve *curve, epoint *a, epoint *b);
void ecurve_print(ecurve *e);
void ecurve_println(ecurve *e);

/* little helpers */
void
mpz_print(mpz_t a)
{
	char buf[256];
	mpz_get_str(buf, 16, a);
	printf("%s", buf);
}

void
mpz_println(mpz_t a)
{
	mpz_print(a);
	printf("\n");
}

/******************************************************************************/
/* CURVE INIT, PRINT */
/******************************************************************************/

void
ecurve_init(ecurve *e)
{
	mpz_inits(e->a, e->b, e->p, NULL);
}

void
ecurve_clear(ecurve *e)
{
	mpz_clears(e->a, e->b, e->p, NULL);
}

void
ecurve_set(ecurve *e, mpz_t a, mpz_t b, mpz_t p)
{
	mpz_set(e->a, a);
	mpz_set(e->b, b);
	mpz_set(e->p, p);
}

/* is the given point on the curve? */
bool
ecurve_iselem(ecurve *e, epoint *p)
{
	bool retval;
	mpz_t lhs, rhs, tmp;
	mpz_inits(lhs, rhs, tmp, NULL);

	mpz_powm_ui(lhs, p->y, 2, e->p);	// y^2

	mpz_powm_ui(rhs, p->x, 3, e->p);	// x^3
	mpz_addmul(rhs, e->a, p->x);		// + a*x
	mpz_add(rhs, rhs, e->b);			// + b
	mpz_mod(rhs, rhs, e->p);

	if(mpz_cmp(lhs, rhs) == 0)
		retval = true;
	else
		retval = false;

	mpz_clears(lhs, rhs, tmp, NULL);
	return retval;
}

/* add two points on the curve

	assumes they're on the curve, does not check!
*/
void
ecurve_add(ecurve *curve, epoint *s, epoint *p, epoint *q)
{
	mpz_t xr, yr, numer, denom, slope;
	mpz_inits(xr, yr, numer, denom, slope, NULL);

	/* p == O -> return q */
	if(p->is_ident) {
		epoint_copy(s, q);
		return;
	}

	/* q == 0 -> return p */
	if(q->is_ident) {
		epoint_copy(s, p);
		return;
	}

	/* opposite points add to the point at infinity */
	else if(ecurve_test_opposites(curve, p, q)) {
		s->is_ident = true;
		return;
	}

	/* calculate slope */
	if(epoint_cmp(p, q) == 0) { /* point doubling */
		/* numerator */
		mpz_powm_ui(numer, p->x, 2, curve->p);				// x^2
		mpz_mul_ui(numer, numer, 3);						// 3*x^2
		mpz_add(numer, numer, curve->a);					// 3*x^2 + a
		mpz_mod(numer, numer, curve->p);

		/* denominator */
		mpz_mul_ui(denom, p->y, 2);							// (2*y_p)
		mpz_invert(denom, denom, curve->p);					// (2*y_p) ^ -1

		/* slope */
		mpz_mul(slope, numer, denom);
		mpz_mod(slope, slope, curve->p);
	}
	else { /* distinct points */
		mpz_sub(numer, q->y, p->y);							// (y_q - y_p)
		mpz_sub(denom, q->x, p->x);
		mpz_invert(denom, denom, curve->p);					// (x_q - x_p)^-1

		mpz_mul(slope, numer, denom);						// (y_q - yp)/(x_q - x_p)
		mpz_mod(slope, slope, curve->p);
	}

	/* and now the new points */
	mpz_mul(xr, slope, slope);
	mpz_sub(xr, xr, p->x);
	mpz_sub(xr, xr, q->x);									// x_r = slope^2 - x_p - x_q
	mpz_mod(xr, xr, curve->p);

	mpz_sub(yr, p->x, xr);
	mpz_mul(yr, yr, slope);
	mpz_sub(yr, yr, p->y);									// y_r = slope*(x_p - x_r) - y_p
	mpz_mod(yr, yr, curve->p);

	/* write to result */
	s->is_ident = false;
	mpz_set(s->x, xr);
	mpz_set(s->y, yr);
}

/* compute P = n*Q */
void
ecurve_mul(ecurve *curve, epoint *q, epoint *p, mpz_t n_)
{
	epoint answer, runner;
	mpz_t n;

	epoint_init(&answer);
	epoint_init(&runner);
	mpz_inits(n, NULL);

	/* any point times 0 is 0 */
	if(mpz_sgn(n_) == 0) {
		q->is_ident = true;
		return;
	}

	/* we modify n in the process */
	mpz_set(n, n_);

	answer.is_ident = true;
	epoint_copy(&runner, p);

	while(mpz_sgn(n) != 0 /* is nonzero */) {
		if(mpz_tstbit(n, 0))
			ecurve_add(curve, &answer, &answer, &runner);

		/* runner = 2*runner */
		ecurve_add(curve, &runner, &runner, &runner);

		/* n >>= 2 */
		mpz_tdiv_q_2exp(n, n, 1);
	}

	epoint_copy(q, &answer);
}

/* returns true if these points are opposites

	in the context of elliptic curves, they are points reflected about the x
	axis, the two solutions to the y^2 on the left-hand-side of the equation
*/
bool
ecurve_test_opposites(ecurve *curve, epoint *a, epoint *b)
{
	mpz_t tmp;
	mpz_inits(tmp, NULL);

	/* requirement #1: x coord is same */
	if(mpz_cmp(a->x, b->x) != 0)
		return false;

	/* requirement #2: y coord is reflected vertically */
	mpz_add(tmp, a->y, b->y);
	if(mpz_cmp(tmp, curve->p) == 0)
		return true;

	return false;
}

void
ecurve_print(ecurve *e)
{
	printf("y^2 = x^3");

	if(mpz_sgn(e->a) != 0) {
		printf(" + ");
		mpz_print(e->a);
		printf(" * x");
	}

	if(mpz_sgn(e->b) != 0) {
		printf(" + ");
		mpz_print(e->b);
	}
}

void
ecurve_println(ecurve *e)
{
	ecurve_print(e);
	printf("\n");
}

/******************************************************************************/
/* POINT STUFF */
/******************************************************************************/

void
epoint_init(epoint *p)
{
	p->is_ident = false;
	mpz_inits(p->x, p->y, NULL);
}

void
epoint_clear(epoint *p)
{
	mpz_clears(p->x, p->y, NULL);
}

void
epoint_copy(epoint *p, epoint *q)
{
	p->is_ident = q->is_ident;
	mpz_set(p->x, q->x);
	mpz_set(p->y, q->y);
}

void
epoint_from_mpz_ts(epoint *p, mpz_t x, mpz_t y)
{
	p->is_ident = false;
	mpz_set(p->x, x);
	mpz_set(p->y, y);
}

void
epoint_from_str16s(epoint *p, char *x, char *y)
{
	p->is_ident = false;
	mpz_set_str(p->x, x, 16);
	mpz_set_str(p->y, y, 16);
}

int
epoint_cmp(epoint *p, epoint *q)
{
	if(p->is_ident && q->is_ident)
		return 0;
	if(mpz_cmp(p->x, q->x) != 0)
		return -1;
	if(mpz_cmp(p->y, q->y) != 0)
		return -1;
	return 0;
}

void
epoint_print(epoint *p)
{
	if(p->is_ident) {
		printf("(0)");
		return;
	}

	printf("(");
	mpz_print(p->x);
	printf(", ");
	mpz_print(p->y);
	printf(")");
}

void
epoint_println(epoint *p)
{
	epoint_print(p);
	printf("\n");
}

/******************************************************************************/
/* MAIN */
/******************************************************************************/

int main(int ac, char **av)
{
	int i;
	ecurve curve;
	mpz_t fchar, a, b, c;
	epoint G, Q, id;

	ecurve_init(&curve);
	mpz_inits(fchar, a, b, c, NULL);

	epoint_init(&G);
	epoint_init(&Q);
	epoint_init(&id);
	id.is_ident = true;

	mpz_set_str(fchar,
		"1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
		"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 16);
	mpz_set_str(a,
		"1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
		"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC", 16);
	mpz_set_str(b,
		"51953EB9618E1C9A1F929A21A0B68540EEA2DA725B99B315F3B8B489918EF109E1561"
		"93951EC7E937B1652C0BD3BB1BF073573DF883D2C34F1EF451FD46B503F00", 16);

	ecurve_set(&curve, a, b, fchar);
	ecurve_print(&curve);
	printf("\n");

	epoint_from_str16s(&G,
		"C6858E06B70404E9CD9E3ECB662395B4429C648139053FB521F828AF606B4D3DBAA14"
		"B5E77EFE75928FE1DC127A2FFA8DE3348B3C1856A429BF97E7E31C2E5BD66",
		"11839296A789A3BC0045C8A5FB42C7D1BD998F54449579B446817AFBD17273E662C97"
		"EE72995EF42640C550B9013FAD0761353C7086A272C24088BE94769FD16650"
	);

	for(i=0; i<10; ++i) {
		mpz_set_ui(c, i);
		ecurve_mul(&curve, &Q, &G, c);
		printf("%d*G = ", i); epoint_println(&Q);
		printf("is it on the curve? %d\n", ecurve_iselem(&curve, &Q));
	}

	/* times the order, we should get the identity */
	mpz_set_str(c,
		"01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA5"
		"1868783BF2F966B7FCC0148F709A5D03BB5C9B8899C47AEBB6FB71E91386409", 16);
	ecurve_mul(&curve, &Q, &G, c);
	printf("nG = "); epoint_println(&Q);
	if(!epoint_cmp(&Q, &id))
		{ printf("PASS!\n"); } else { printf("FAIL!\n"); return -1; }

	/* times one less than the order, we should get a random point */
	mpz_sub_ui(c, c, 1);
	ecurve_mul(&curve, &Q, &G, c);
	printf("(n-1)G = "); epoint_println(&Q);
	if(!epoint_cmp(&Q, &id) || !epoint_cmp(&Q, &G))
		{ printf("FAIL!\n"); return -1; } else { printf("PASS!\n"); }

	/* times one more than the order, we should get G again */
	mpz_add_ui(c, c, 1);
	mpz_add_ui(c, c, 1);
	ecurve_mul(&curve, &Q, &G, c);
	printf("(n+1)G = "); epoint_println(&Q);
	if(!epoint_cmp(&Q, &G))
		{ printf("PASS!\n"); } else { printf("FAIL!\n"); return -1; }

	/* cleanup */
	ecurve_clear(&curve);
	mpz_clears(fchar, a, b, c, NULL);
}
