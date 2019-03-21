#include <boot/Multiboot.h>

// declarations
void kernel_entry(multiboot_header* header);
void kernel_main(/*unsigned long magic, unsigned long addr*/);



/*  This is the one of most important thing to be able to load a PE kernel
with GRUB. Because PE header are in the begining of the file, code section
will be shifted. The value used to shift the code section is the linker
align option /ALIGN:value. Note the header size sum is larger than 512,
so ALIGN value must be greater */
#define   ALIGN               0x400

/*   Must be >= 1Mo for GRUB
Base adress from advanced linker option */
#define LOADBASE            0x100000

/*   PE header are stored at the beginning of the file.
Code section is placed after */
#define   HEADER_ADDRESS         LOADBASE+ALIGN


/*************************************************************
 MULTIBOOT Header
 These data are placed at the beginning of the kernel file
 Grub 2 needs these data to boot properly
 see multiboot specification
*************************************************************/
#pragma code_seg(".a$0")
__declspec(allocate(".a$0"))
multiboot_header _MultibootHeader = {

	(unsigned long)MULTIBOOT_HEADER_MAGIC,
	(unsigned long)MULTIBOOT_HEADER_FLAGS,
	(unsigned long)CHECKSUM,
	(unsigned long)HEADER_ADDRESS,
	(unsigned long)LOADBASE,
	(unsigned long)0, //load end address
	(unsigned long)0, //bss end address
	(unsigned long)kernel_entry,
	(unsigned long)0,
	(unsigned long)800,
	(unsigned long)600,
	(unsigned long)8
};
#pragma comment(linker, "/merge:.text=.a")


/*************************************************************
 kernel_entry
 this function is referenced by multiboot header to let
 Grub 2 start operating system
*************************************************************/
void kernel_entry(multiboot_header* header) {

	unsigned long magic;
	unsigned long multibootInfoPointer;

	/* set parameters */
	__asm {
		mov	magic, eax
		mov multibootInfoPointer, ebx
	}

	/* Start operating system */
	if (magic == 0x2BADB002)
	{
		kernel_main(/*magic, multibootInfoPointer*/);
	}

	// just stop if not loaded by Grub
	_asm hlt;
}

/*************************************************************
 kernel_main
 The main entry for
 let Grub 2 start operating system
*************************************************************/
void kernel_main(/*unsigned long magic, unsigned long addr*/) {

	const char *sHello = "Hello world from VS2017 Kernel template !\0";
	char *videoMemory = (char*)(0xB8000);
	const unsigned char color = 0x0F;

	// erase screen
	for (int i = 0; i< 80 * 25; i++)
	{
		*videoMemory++ = ' ';      // character value
		*videoMemory++ = 0x00;      // color value
	}

	videoMemory = (char*)(0xB8000);  // reset video memory pointer

	// display message
	while (*sHello != '\0')
	{
		*videoMemory++ = *sHello++;   // character value
		*videoMemory++ = color;      // color value
	}
	_asm hlt;                  // stop to not hang on
}