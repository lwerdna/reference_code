#ifndef __EFI_SYSTEM_TABLE_H__
#define __EFI_SYSTEM_TABLE_H__

#include "boot_table.h"
#include "simple_text_output_protocol.h"
#include "types.h"

struct efi_system_table
{
	struct efi_table_header header;
	uint16_t *FirmwareVendor;
	uint32_t FirmwareRevision;

	void *ConsoleInHandle;
	void *ConIn;

	void *ConsoleOutputHandle;
	struct efi_simple_text_output_protocol *ConOut;

	void *StandardErrorHandle;
	struct efi_simple_text_output_protocol *StdError;

	void *RuntimeServices;
	struct efi_boot_table *BootServices;

	efi_uint_t NumberOfTableEntries;
	void *ConfigurationTable;
};

#endif // __EFI_SYSTEM_TABLE_H__
