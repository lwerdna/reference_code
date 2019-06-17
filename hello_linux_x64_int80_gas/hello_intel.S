.intel_syntax noprefix

.text						# section declaration
							# we must export the entry point to the ELF linker or
.global _start				# loader. They conventionally recognize _start as their
							# entry point. Use ld -e foo to override the default.

_start:
							# write our string to stdout

	 mov	edx, offset len	# third argument: message length
	 mov	ecx, offset msg	# second argument: pointer to message to write
	 mov	ebx, 1			# first argument: file handle (stdout)
	 mov	eax, 4			# system call number (sys_write)
	 int	0x80			# call kernel

							# and exit

	 mov	ebx, 0			# first argument: exit code
	 mov	eax, 1			# system call number (sys_exit)
	 int	0x80			# call kernel

.data						# section declaration

msg:
	.ascii	"Hello, world!\n"		# our dear string
	len = . - msg			# length of our dear string
