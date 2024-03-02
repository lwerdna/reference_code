#include "efi/efi.h"

typedef void *efi_handle_t;

efi_status_t efi_main(
	efi_handle_t handle, struct efi_system_table *system_table)
{
	__asm__("here: jmp here");

	uint16_t msg[] = u"Hello World!";
	efi_status_t status;

	status = system_table->ConOut->clear_screen(system_table->ConOut);
	if (status != 0)
		return status;

	status = system_table->ConOut->output_string(system_table->ConOut, msg);
	if (status != 0)
		return status;

	return 0;
}

