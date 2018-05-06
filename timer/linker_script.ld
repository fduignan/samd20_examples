/* useful reference: www.linuxselfhelp.com/gnu/ld/html_chapter/ld_toc.html */
MEMORY
{
    flash : org = 0x00000000, len = 64k
    ram : org = 0x20000000, len = 8k
}
  
SECTIONS
{
        
	. = ORIGIN(flash);
        .text : {
		  *(.vectors); /* The interrupt vectors */
		  *(.text);
		  *(.rodata);
		  *(.comment);
		  *(.ARM.attributes);
		
		  . = ALIGN(4);
        } >flash
	. = ORIGIN(ram);
        .data : {
	  INIT_DATA_VALUES = LOADADDR(.data);
	  INIT_DATA_START = .;
	    *(.data);
	  INIT_DATA_END = .;
	  . = ALIGN(4);
        } >ram AT>flash
	BSS_START = .;
	.bss : {	  
	    *(.bss);
	    . = ALIGN(4);
	} > ram
	BSS_END = .;
}
