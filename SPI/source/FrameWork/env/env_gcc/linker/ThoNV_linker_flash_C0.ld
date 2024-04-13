ENTRY(Reset_Handler)

/*
* FLASH(rx):ORIGIN =0x08000000,LENGTH =1024K
* SRAM(rwx):ORIGIN =0x20000000,LENGTH =128K
* ITCM (rx):ORIGIN = 0x00000000, LENGTH = 64K   Instruction Tightly-Coupled Memory (Luu lenh vao day giup truy cap nhanh hon)
* DTCM (rwx):ORIGIN = 0x10000000, LENGTH = 128K Data Tightly-Coupled Memory (Luu data vao day giup truy cap nhanh hon)
*/

MEMORY
{
    int_itcm                   : ORIGIN = 0x00000000, LENGTH = 64K     /* 64K */
    int_dtcm                   : ORIGIN = 0x10000000, LENGTH = 128K    /* 128K */

    int_flash_c0               : ORIGIN = 0x08000000, LENGTH = 0x000F9F00    /* 1024K - 0.1K */
    int_flash_fls_rsv_c0       : ORIGIN = 0x080F9F00, LENGTH = 0x00000100    /* 0.1K */

    int_sram_c0                : ORIGIN = 0x20000000, LENGTH = 0x00013880    /* 80K */
    int_sram_fls_rsv_c0        : ORIGIN = 0x20013880, LENGTH = 0x00000100    /* 0.1K */
	int_sram_stack_c0          : ORIGIN = 0x20013980, LENGTH = 0x00006C60    /* 27744  */
    int_sram_no_cacheable_c0   : ORIGIN = 0x2001A5E0, LENGTH = 0x00002710    /* 10KB */
    int_sram_shareable         : ORIGIN = 0x2001CCF0, LENGTH = 0x00002710    /* 10KB */
    ram_end_c0                 : ORIGIN = 0x2001F400, LENGTH = 0x00000000

    int_sram_stack_c1          : ORIGIN = 0x30000000, LENGTH = 0x00001000    /* 4KB */
    init_system_SC             : ORIGIN = 0xE000ED00, LENGTH = 0x00000100    /* SC module */
}

HEAP_SIZE  = DEFINED(heap_size)  ? heap_size  : 0x00000200;

SECTIONS
{
    .flash :
    {
        init_vectortable_start = .;
        KEEP(*(.intc_vector))
        . = ALIGN(4);
        init_vectortable_end = .;

        . = ALIGN(4);
        *(.startup)
        *(.systeminit)
        *(.text.startup)
        *(.text)
        *(.text*)
        *(.mcal_text)
        *(.acmcu_code_rom)
        *(.rodata)
        *(.rodata*)
        *(.mcal_const_cfg)
        *(.mcal_const)
        . = ALIGN(4);

        init_table = .;
        KEEP(*(.init_table))
        . = ALIGN(4);
        init_table_end = .;

        zero_table = .;
        KEEP(*(.zero_table))
        . = ALIGN(4);
        zero_table_end = .;

        KEEP(*(.init))
        . = ALIGN(4);
        KEEP(*(.fini))
        . = ALIGN(4);

        code_end = .;
    } > int_flash_c0

    init_data_start = code_end;

    .acfls_code_rom :
    {
        acfls_code_rom_start = .;
        *(.acfls_code_rom) 
        . = ALIGN(4);
        acfls_code_rom_end = .;
    } > int_flash_fls_rsv_c0

    .data_ram : AT(init_data_start)
    {
        data_start = .;

        *(.data)
        *(.data*)
        . = ALIGN(4);
        *(.mcal_data)
        . = ALIGN(4);
        *(.ramcode)
        . = ALIGN(4);

        data_end = .;
    } > int_sram_c0
    init_data_end = init_data_start + (data_end - data_start);

    .bss_ram :
    {
        . = ALIGN(16);
        bss_start = .;

        *(.bss)
        *(.bss*)
        . = ALIGN(16);
        *(.mcal_bss)
        . = ALIGN(4);

        bss_end = .;
    } > int_sram_c0

    .heap (NOLOAD):
    {
        . += ALIGN(4);
        end = .;
        heap_start = .;

        . += HEAP_SIZE;

        heap_end = .;
    } > int_sram_c0

    .acfls_code_ram :
    {
        acfls_code_ram_start  = .;

        *(.acfls_code_ram)

        acfls_code_ram_stop   = .;
    } > int_sram_fls_rsv_c0

    .vectortable_nocache :
    {
        . = ALIGN(4096);
        vectortable_start = .;

        . += init_vectortable_end - init_vectortable_start;
        . = ALIGN(4);

        vectortable_end = .;
    } > int_sram_no_cacheable_c0

    init_data_nocache_start = init_data_end;
    .data_nocache : AT(init_data_nocache_start)
	{
		data_nocache_start = .;

        *(.mcal_data_no_cacheable)
        . = ALIGN(4);
        *(.mcal_const_no_cacheable)
        . = ALIGN(4);

        data_nocache_end = .;
	} > int_sram_no_cacheable_c0
    init_data_nocache_end = init_data_nocache_start + (data_nocache_end - data_nocache_start);

    .bss_nocache :
	{
		bss_nocache_start = .;

        *(.mcal_bss_no_cacheable)
        . = ALIGN(4);

        bss_nocache_end = .;
	} > int_sram_no_cacheable_c0
    
  	init_data_shareable_start = init_data_nocache_end;
	.data_shareable : AT(init_data_shareable_start)
	{
	    data_shareable_start = .;

        *(.mcal_shared_data)
        . = ALIGN(4);

        data_shareable_end = .;
	} > int_sram_shareable
	init_data_shareable_end = init_data_shareable_start + (data_shareable_end - data_shareable_start);

    .bss_shareable :
    {
        bss_shareable_start = .;

        *(.mcal_shared_bss )
        . = ALIGN(4);

        bss_shareable_end = .;
    } > int_sram_shareable

    .system_sc :
    {
        KEEP(*(.system_sc))
    } > init_system_SC

    Stack_end_c0              = ORIGIN(int_sram_stack_c0);
    Stack_start_c0            = ORIGIN(int_sram_stack_c0) + LENGTH(int_sram_stack_c0);
    Stack_end_c1              = ORIGIN(int_sram_stack_c1);
    Stack_start_c1            = ORIGIN(int_sram_stack_c1) + LENGTH(int_sram_stack_c1);

    INT_SRAM_START            = ORIGIN(int_sram_c0);
    INT_SRAM_END              = ORIGIN(ram_end_c0);

    INT_ITCM_START            = ORIGIN(int_itcm);
    INT_ITCM_END              = ORIGIN(int_itcm) + LENGTH(int_itcm);

    INT_DTCM_START            = ORIGIN(int_dtcm);
    INT_DTCM_END              = ORIGIN(int_dtcm) + LENGTH(int_dtcm);

    ROM_CODE_START            = ORIGIN(int_flash_c0);
    RAM_SHAREABLE_START       = ORIGIN(int_sram_shareable);
    RAM_STACK_START           = ORIGIN(int_sram_stack_c0);
    RAM_NO_CACHEABLE_START    = ORIGIN(int_sram_no_cacheable_c0);

    Fls_ACEraseRomStart         = acfls_code_rom_start;
    Fls_ACEraseRomEnd           = acfls_code_rom_end;
    Fls_ACEraseSize             = (acfls_code_rom_end - acfls_code_rom_start)/4;    /* 1 word = 4 byte */

    Fls_ACWriteRomStart         = acfls_code_rom_start;
    Fls_ACWriteRomEnd           = acfls_code_rom_end;
    Fls_ACWriteSize             = (acfls_code_rom_end - acfls_code_rom_start)/4;    /* 1 word = 4 byte */

    Fls_ACBlankReadRomStart     = acfls_code_rom_start;
    Fls_ACBlankReadRomEnd       = acfls_code_rom_end;
    Fls_ACBlankReadSize         = (acfls_code_rom_end - acfls_code_rom_start)/4;    /* 1 word = 4 byte */

    ERASE_FUNC_ADDRESS        = ADDR(.acfls_code_ram);
    WRITE_FUNC_ADDRESS        = ADDR(.acfls_code_ram);
    BLANK_READ_FUNC_ADDRESS   = ADDR(.acfls_code_ram);

    RAM_INIT                  = 1;
    ITCM_INIT                 = 1;
    DTCM_INIT                 = 1;
    CORE_ID                   = 0;
	
}