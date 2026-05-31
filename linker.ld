ENTRY(kernel_main)

PHDRS
{
	text PT_LOAD FLAGS(5);
	rodata PT_LOAD FLAGS(4);
	data PT_LOAD FLAGS(6);
}

SECTIONS
{
	. = 0xffffffff80000000;

	.text : {
		*(.text .text.*)
	} : text

	. = ALIGN(4096);

	.limine_requests : {
		KEEP(*(.limine_requests))
	} : rodata

	.rodata : {
		*(.rodata .rodata.*)
	} :rodata

	. = ALIGN(4096);

	.data : {
		*(.data .data.*)
	} : data

	.bss : {
		*(.bss .bss.*)
		*(COMMON)
	} : data

	/DISCARD/ : {
		*(.note .note.*)
		*(.interp)
		*(.comment)
	}
	
}
