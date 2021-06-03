#!/usr/bin/env python

import pprint

import tatsu
from tatsu.ast import AST

class CalcBasicSemantics(object):
    def number(self, ast):
        return int(ast)

    def term(self, ast):
        if not isinstance(ast, AST):
            return ast
        elif ast.op == '*':
            return ast.left * ast.right
        elif ast.op == '/':
            return ast.left / ast.right
        else:
            raise Exception('Unknown operator', ast.op)

    def expression(self, ast):
        if not isinstance(ast, AST):
            return ast
        elif ast.op == '+':
            return ast.left + ast.right
        elif ast.op == '-':
            return ast.left - ast.right
        else:
            raise Exception('Unknown operator', ast.op)

def parse(expr):
    grammar = open('calc.ebnf').read()

    parser = tatsu.compile(grammar)
    ast = parser.parse(expr)

    print('# BASIC RESULT')
    pprint.pprint(ast, width=20, indent=4)

def parse_with_basic_semantics(expr):
    grammar = open('calc.ebnf').read()

    parser = tatsu.compile(grammar)
    ast = parser.parse(expr, semantics=CalcBasicSemantics())

    print('# BASIC SEMANTICS RESULT')
    pprint.pprint(ast, width=20, indent=4)

def main():
    parse('3 + 5 * ( 10 - 20 )')
    parse_with_basic_semantics('3 + 5 * ( 10 - 20 )')

if __name__ == '__main__':
    main()    
