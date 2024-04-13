ENTRY(Reset_Handler)

/*
* FLASH(rx):ORIGIN =0x08000000,LENGTH =1024K
* SRAM(rwx):ORIGIN =0x20000000,LENGTH =128K
* ITCM (rx):ORIGIN = 0x00000000, LENGTH = 64K       Instruction Tightly-Coupled Memory (Luu lenh vao day giup truy cap nhanh hon)
* DTCM (rwx):ORIGIN = 0x10000000, LENGTH = 128K     Data Tightly-Coupled Memory (Luu data vao day giup truy cap nhanh hon)
*/

MEMORY
{
    int_itcm                   : ORIGIN = 0x00000000, LENGTH = 64K     /* 64K */
    int_dtcm                   : ORIGIN = 0x10000000, LENGTH = 128K    /* 128K */

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
    .sram :
    {
        . = ALIGN(4);
        *(.startup) 
        *(.systeminit)
        *(.text.startup) 
        *(.text)
        *(.text*) 
        *(.mcal_text)
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

        data_start = .;

        *(.data)
        *(.data*)
        . = ALIGN(4);
        *(.mcal_data)
        *(.ramcode)
        *(.acmcu_code_rom)
        . = ALIGN(4);
    } > int_sram_c0

    .acfls_code_rom :
    {
        acfls_code_rom_start = .;

        . = ALIGN(0x4);
        *(.acfls_code_rom)

        acfls_code_rom_end = .;
    } > int_sram_c0

    .acfls_code_ram :
    {
        acfls_code_ram_start  = .;

        . += (acfls_code_rom_end - acfls_code_rom_start );

        acfls_code_ram_stop   = .;
    } > int_sram_c0

    data_end = .;

    .sram_bss :
    {
        . = ALIGN(64);
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

    .sram_nocache :
    {
        vectortable_start = .;
        KEEP(*(.intc_vector))
        . = ALIGN(4096);
        vectortable_end = .;

        data_nocache_start = .;
        *(.mcal_data_no_cacheable)
        . = ALIGN(4);
        *(.mcal_const_no_cacheable)
        . = ALIGN(4);
        data_nocache_end = .;

        bss_nocache_start = .;
        *(.mcal_bss_no_cacheable)
        . = ALIGN(4);
        bss_nocache_end = .;

    } > int_sram_no_cacheable_c0

    .sram_shareable :
    {
        data_shareable_start = .;
        KEEP(*(.mcal_shared_data))
        . = ALIGN(4);
        data_shareable_end = .;

        bss_shareable_start = .;
        *(.mcal_shared_bss)
        . = ALIGN(4);
        bss_shareable_end = .;
    } > int_sram_shareable

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

    init_vectortable_start    = 0;
    init_vectortable_end      = 0;
    init_data_start           = 0;
    init_data_end             = 0;
    init_data_nocache_start   = 0;
    init_data_nocache_end     = 0;
    init_data_shareable_start = 0;
    init_data_shareable_end   = 0;

    ROM_CODE_START            = 0x08000000;
    RAM_SHAREABLE_START       = ORIGIN(int_sram_shareable);
    RAM_STACK_START           = ORIGIN(int_sram_stack_c0);
    RAM_NO_CACHEABLE_START    = ORIGIN(int_sram_no_cacheable_c0);

    Fls_ACEraseRomStart         = ADDR(.acfls_code_rom);
    Fls_ACEraseRomEnd           = ADDR(.acfls_code_rom) + SIZEOF(.acfls_code_rom);
    Fls_ACEraseSize             = (SIZEOF(.acfls_code_rom)+3) / 4;

    Fls_ACWriteRomStart         = ADDR(.acfls_code_rom);
    Fls_ACWriteRomEnd           = ADDR(.acfls_code_rom) + SIZEOF(.acfls_code_rom);
    Fls_ACWriteSize             = (SIZEOF(.acfls_code_rom)+3) / 4;

    ERASE_FUNC_ADDRESS        = ADDR(.acfls_code_ram);
    WRITE_FUNC_ADDRESS        = ADDR(.acfls_code_ram);
    BLANK_READ_FUNC_ADDRESS   = ADDR(.acfls_code_ram);

    RAM_INIT                  = 0;
    ITCM_INIT                 = 1;
    DTCM_INIT                 = 1;
    CORE_ID                   = 0;
	
}