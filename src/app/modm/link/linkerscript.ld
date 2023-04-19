/*
 * Copyright (c) 2011-2012, 2019, Fabian Greif
 * Copyright (c) 2012, 2015-2022, Niklas Hauser
 * Copyright (c) 2013, Sascha Schade
 * Copyright (c) 2013, 2015, Kevin Läufer
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 * ------------------------------------------------------------------------- */


OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(Reset_Handler)

MEMORY
{
	FLASH (rx) : ORIGIN = 0x00400000, LENGTH = 1048576
	RAM (rwx) : ORIGIN = 0x20400000, LENGTH = 393216
}

__flash_start = ORIGIN(FLASH);
__flash_end = ORIGIN(FLASH) + LENGTH(FLASH);
__ram_start = ORIGIN(RAM);
__ram_end = ORIGIN(RAM) + LENGTH(RAM);


MAIN_STACK_SIZE = 3072;

SECTIONS
{
	__rom_start = ORIGIN(FLASH);


	/* Read-only vector table in FLASH */
	.text :
	{
		__vector_table_rom_start = .;
		__vector_table_ram_load = .;
		KEEP(*(.vector_rom))
		__vector_table_rom_end = .;
	} >FLASH


	/* build id directly after vector table */
	.build_id :
	{
		__build_id = .;
		KEEP(*(.note.gnu.build-id))
	} >FLASH

	/* Read-only sections in FLASH */
	.text :
	{
		*(.text .text.* .gnu.linkonce.t.*)
	} >FLASH

	.rodata :
	{
		*(.rodata .rodata.* .gnu.linkonce.r.*)
		KEEP(*(.init))

		. = ALIGN(4);
		__init_array_start = .;
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		. = ALIGN(4);
		__init_array_end = .;

		__hardware_init_start = .;
		KEEP(*(SORT(.hardware_init.order_*)))
		KEEP(*(SORT(.hardware_init)))
		. = ALIGN(4);
		__hardware_init_end = .;

		__assertion_table_start = .;
		KEEP(*(.assertion))
		. = ALIGN(4);
		__assertion_table_end = .;
	} >FLASH

	/* We do not call static destructors ever */
	/DISCARD/ :
	{
		*(.fini_array .fini_array.*)
	}

	/* C++ exception unwind tables are discarded */
	/DISCARD/ :
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
		*(.eh_frame*)
	}

	/* Catch use of dynamic memory without `modm:platform:heap` module. */
	/DISCARD/ :
	{
		*(.Heap_is_not_implemented!__Please_include_the__modm:platform:heap__module_in_your_project!)
	}


	/* Main stack in RAM */
	.stack (NOLOAD) :
	{
		__stack_start = .;

		. += MAIN_STACK_SIZE;
		. = ALIGN(8);
		__main_stack_top = .;

		__stack_end = .;
	} >RAM


	/* Read-write sections in RAM */
	.data :
	{
		. = ALIGN(4);
		__data_load = LOADADDR(.data);
		__data_start = .;
		*(.data .data.* .gnu.linkonce.d.*)
		. = ALIGN(4);
		__data_end = .;
	} >RAM AT >FLASH

	.fastdata :
	{
		__fastdata_load = LOADADDR(.fastdata);
		__fastdata_start = .;
		*(.fastdata .fastdata.*)
		. = ALIGN(4);
		__fastdata_end = .;
	} >RAM AT >FLASH

	.fastcode :
	{
		__fastcode_load = LOADADDR(.fastcode);
		__fastcode_start = .;
		*(.fastcode .fastcode.*)
		. = ALIGN(4);
		__fastcode_end = .;
	} >RAM AT >FLASH

	.data_ram :
	{
		__data_ram_load = LOADADDR(.data_ram);
		__data_ram_start = .;
		*(.data_ram .data_ram.*)
		. = ALIGN(4);
		__data_ram_end = .;
	} >RAM AT >FLASH

	.bss (NOLOAD) :
	{
		__bss_start = . ;
		*(.bss .bss.* .gnu.linkonce.b.*)
		. = ALIGN(4);
	} >RAM

	.bss_ram (NOLOAD) :
	{
		__bss_ram_start = . ;
		*(.bss_ram .bss_ram.*)
		. = ALIGN(4);
		__bss_ram_end = .;
		__bss_end = .;
	} >RAM


	.noinit (NOLOAD) :
	{
		__noinit_start = . ;
		*(.noinit .noinit.*)
		. = ALIGN(4);
		__noinit_end = .;
	} >RAM

	.faststack (NOLOAD) :
	{
		__faststack_start = . ;
		*(.faststack .faststack.*)
		. = ALIGN(4);
		__faststack_end = .;
	} >RAM


	/* Sections in RAM */
	.noinit_ram (NOLOAD) :
	{
		. = ALIGN(4);
		__noinit_ram_start = .;
		*(.noinit_ram .noinit_ram.*)
		. = ALIGN(4);
		__noinit_ram_end = .;
	} >RAM

	.heap_ram (NOLOAD) :
	{
		. = ALIGN(4);
		__heap_ram_start = .;
		. = MAX(ABSOLUTE(.), ORIGIN(RAM) + LENGTH(RAM));
		__heap_ram_end = .;
	} >RAM




	/* Memory layout configuration tables */
	.rodata :
	{
		. = ALIGN(4);
		__table_zero_intern_start = .;
		LONG(__bss_start)
		LONG(__bss_end)
		__table_zero_intern_end = .;

		__table_copy_intern_start = .;
		LONG(__data_load)
		LONG(__data_start)
		LONG(__data_end)
		LONG(__fastdata_load)
		LONG(__fastdata_start)
		LONG(__fastdata_end)
		LONG(__fastcode_load)
		LONG(__fastcode_start)
		LONG(__fastcode_end)
		LONG(__data_ram_load)
		LONG(__data_ram_start)
		LONG(__data_ram_end)
		__table_copy_intern_end = .;

		__table_zero_extern_start = .;
		__table_zero_extern_end = .;

		__table_copy_extern_start = .;
		__table_copy_extern_end = .;

		/* See `modm:architecture:memory` for bitmask */
		__table_heap_start = .;
		LONG(0x001f)
		LONG(__heap_ram_start)
		LONG(__heap_ram_end)
		__table_heap_end = .;
	} >FLASH


	. = ALIGN(4);
	__rom_end = .;


	/* DWARF debug sections */
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_aranges  0 : { *(.debug_aranges) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_info     0 : { *(.debug_info) }
	.debug_line     0 : { *(.debug_line) }
	.debug_loc      0 : { *(.debug_loc) }
	.debug_macinfo  0 : { *(.debug_macinfo) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	.debug_pubtypes 0 : { *(.debug_pubtypes) }
	.debug_ranges   0 : { *(.debug_ranges) }
	.debug_str      0 : { *(.debug_str) }

	.comment 0 : { *(.comment) }
	.ARM.attributes 0 : { KEEP(*(.ARM.attributes)) }
	/DISCARD/ : { *(.note.GNU-stack)  }

}