#define MEMMAP_ERROR
#define _IAR_HULA_
/********************************* GREENHILLS *********************************/
#if defined (_GREENHILLS_HULA_)
#ifdef START_CONFIG_DATA_BOOLEAN
    #undef START_CONFIG_DATA_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma ghs section rodata=".mcal_const_cfg"
#endif

#ifdef STOP_CONFIG_DATA_BOOLEAN
    #undef STOP_CONFIG_DATA_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CONFIG_DATA_8
    #undef START_CONFIG_DATA_8
    #undef MEMMAP_ERROR
    #pragma ghs section rodata=".mcal_const_cfg"
#endif

#ifdef STOP_CONFIG_DATA_8
    #undef STOP_CONFIG_DATA_8
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CONFIG_DATA_16
    #undef START_CONFIG_DATA_16
    #undef MEMMAP_ERROR
    #pragma ghs section rodata=".mcal_const_cfg"
#endif

#ifdef STOP_CONFIG_DATA_16
    #undef STOP_CONFIG_DATA_16
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CONFIG_DATA_32
    #undef START_CONFIG_DATA_32
    #undef MEMMAP_ERROR
    #pragma ghs section rodata=".mcal_const_cfg"
#endif

#ifdef STOP_CONFIG_DATA_32
    #undef STOP_CONFIG_DATA_32
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CONFIG_DATA_UNSPECIFIED
    #undef START_CONFIG_DATA_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma ghs section rodata=".mcal_const_cfg"
#endif

#ifdef STOP_CONFIG_DATA_UNSPECIFIED
    #undef STOP_CONFIG_DATA_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CONFIG_DATA_8_NO_CACHEABLE
    #undef START_CONFIG_DATA_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section rodata=".mcal_const_no_cacheable"
#endif

#ifdef STOP_CONFIG_DATA_8_NO_CACHEABLE
    #undef STOP_CONFIG_DATA_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CONFIG_DATA_16_NO_CACHEABLE
    #undef START_CONFIG_DATA_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section rodata=".mcal_const_no_cacheable"
#endif

#ifdef STOP_CONFIG_DATA_16_NO_CACHEABLE
    #undef STOP_CONFIG_DATA_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CONFIG_DATA_32_NO_CACHEABLE
    #undef START_CONFIG_DATA_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section rodata=".mcal_const_no_cacheable"
#endif

#ifdef STOP_CONFIG_DATA_32_NO_CACHEABLE
    #undef STOP_CONFIG_DATA_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CONFIG_DATA_UNSPECIFIED_NO_CACHEABLE
    #undef START_CONFIG_DATA_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section rodata=".mcal_const_no_cacheable"
#endif

#ifdef STOP_CONFIG_DATA_UNSPECIFIED_NO_CACHEABLE
    #undef STOP_CONFIG_DATA_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CONST_BOOLEAN
    #undef START_CONST_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma ghs section rodata=".mcal_const"
#endif

#ifdef STOP_CONST_BOOLEAN
    #undef STOP_CONST_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CONST_8
    #undef START_CONST_8
    #undef MEMMAP_ERROR
    #pragma ghs section rodata=".mcal_const"
#endif

#ifdef STOP_CONST_8
    #undef STOP_CONST_8
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CONST_16
    #undef START_CONST_16
    #undef MEMMAP_ERROR
    #pragma ghs section rodata=".mcal_const"
#endif

#ifdef STOP_CONST_16
    #undef STOP_CONST_16
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CONST_32
    #undef START_CONST_32
    #undef MEMMAP_ERROR
    #pragma ghs section rodata=".mcal_const"
#endif

#ifdef STOP_CONST_32
    #undef STOP_CONST_32
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CONST_UNSPECIFIED
    #undef START_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma ghs section rodata=".mcal_const"
#endif

#ifdef STOP_CONST_UNSPECIFIED
    #undef STOP_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CODE
    #undef START_CODE
    #undef MEMMAP_ERROR
    #pragma ghs section text=".mcal_text"
#endif

#ifdef STOP_CODE
    #undef STOP_CODE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CODE_FAST
    #undef START_CODE_FAST
    #undef MEMMAP_ERROR
    #pragma ghs section text=".mcal_text"
#endif

#ifdef STOP_CODE_FAST
    #undef STOP_CODE_FAST
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CODE_SLOW
    #undef START_CODE_SLOW
    #undef MEMMAP_ERROR
    #pragma ghs section text=".mcal_text"
#endif

#ifdef STOP_CODE_SLOW
    #undef STOP_CODE_SLOW
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_CALLOUT_CODE
    #undef START_CALLOUT_CODE
    #undef MEMMAP_ERROR
    #pragma ghs section text=".mcal_text"
#endif

#ifdef STOP_CALLOUT_CODE
    #undef STOP_CALLOUT_CODE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_RAMCODE
    #undef START_RAMCODE
    #undef MEMMAP_ERROR
    #pragma ghs section text=".ramcode"
    #pragma ghs inlineprologue
    #pragma ghs callmode=far
#endif

#ifdef STOP_RAMCODE
    #undef STOP_RAMCODE
    #undef MEMMAP_ERROR
    #pragma ghs section
    #pragma ghs noinlineprologue
    #pragma ghs callmode=default
#endif

#ifdef START_CODE_AC
    #undef START_CODE_AC
    #undef MEMMAP_ERROR
    #pragma ghs section text=".access_code_rom"
    #pragma ghs inlineprologue
#endif

#ifdef STOP_CODE_AC
    #undef STOP_CODE_AC
    #undef MEMMAP_ERROR
    #pragma ghs section
    #pragma ghs noinlineprologue
#endif

#ifdef START_VAR_CLEARED_BOOLEAN
    #undef START_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma ghs section bss=".mcal_bss"
#endif

#ifdef STOP_VAR_CLEARED_BOOLEAN
    #undef STOP_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_CLEARED_8
    #undef START_VAR_CLEARED_8
    #undef MEMMAP_ERROR
    #pragma ghs section bss=".mcal_bss"
#endif

#ifdef STOP_VAR_CLEARED_8
    #undef STOP_VAR_CLEARED_8
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_CLEARED_16
    #undef START_VAR_CLEARED_16
    #undef MEMMAP_ERROR
    #pragma ghs section bss=".mcal_bss"
#endif

#ifdef STOP_VAR_CLEARED_16
    #undef STOP_VAR_CLEARED_16
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_CLEARED_32
    #undef START_VAR_CLEARED_32
    #undef MEMMAP_ERROR
    #pragma ghs section bss=".mcal_bss"
#endif

#ifdef STOP_VAR_CLEARED_32
    #undef STOP_VAR_CLEARED_32
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_CLEARED_UNSPECIFIED
    #undef START_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma ghs section bss=".mcal_bss"
#endif

#ifdef STOP_VAR_CLEARED_UNSPECIFIED
    #undef STOP_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_INIT_BOOLEAN
    #undef START_VAR_INIT_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma ghs section data=".mcal_data" bss=".mcal_bss"
#endif

#ifdef STOP_VAR_INIT_BOOLEAN
    #undef STOP_VAR_INIT_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_INIT_8
    #undef START_VAR_INIT_8
    #undef MEMMAP_ERROR
    #pragma ghs section data=".mcal_data" bss=".mcal_bss"
#endif

#ifdef STOP_VAR_INIT_8
    #undef STOP_VAR_INIT_8
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_INIT_16
    #undef START_VAR_INIT_16
    #undef MEMMAP_ERROR
    #pragma ghs section data=".mcal_data" bss=".mcal_bss"
#endif

#ifdef STOP_VAR_INIT_16
    #undef STOP_VAR_INIT_16
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_INIT_32
    #undef START_VAR_INIT_32
    #undef MEMMAP_ERROR
    #pragma ghs section data=".mcal_data" bss=".mcal_bss"
#endif

#ifdef STOP_VAR_INIT_32
    #undef STOP_VAR_INIT_32
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_INIT_UNSPECIFIED
    #undef START_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma ghs section data=".mcal_data" bss=".mcal_bss"
#endif

#ifdef STOP_VAR_INIT_UNSPECIFIED
    #undef STOP_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
    #undef START_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section bss=".mcal_bss_no_cacheable"
#endif

#ifdef STOP_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_CLEARED_8_NO_CACHEABLE
    #undef START_VAR_CLEARED_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section bss=".mcal_bss_no_cacheable"
#endif

#ifdef STOP_VAR_CLEARED_8_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_CLEARED_16_NO_CACHEABLE
    #undef START_VAR_CLEARED_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section bss=".mcal_bss_no_cacheable"
#endif

#ifdef STOP_VAR_CLEARED_16_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_CLEARED_32_NO_CACHEABLE
    #undef START_VAR_CLEARED_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section bss=".mcal_bss_no_cacheable"
#endif

#ifdef STOP_VAR_CLEARED_32_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef START_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section bss=".mcal_bss_no_cacheable"
#endif

#ifdef STOP_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_INIT_BOOLEAN_NO_CACHEABLE
    #undef START_VAR_INIT_BOOLEAN_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section data=".mcal_data_no_cacheable" bss=".mcal_bss_no_cacheable"
#endif

#ifdef STOP_VAR_INIT_BOOLEAN_NO_CACHEABLE
    #undef STOP_VAR_INIT_BOOLEAN_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_INIT_8_NO_CACHEABLE
    #undef START_VAR_INIT_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section data=".mcal_data_no_cacheable"  bss=".mcal_bss_no_cacheable"
#endif

#ifdef STOP_VAR_INIT_8_NO_CACHEABLE
    #undef STOP_VAR_INIT_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_INIT_16_NO_CACHEABLE
    #undef START_VAR_INIT_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section data=".mcal_data_no_cacheable"  bss=".mcal_bss_no_cacheable"
#endif

#ifdef STOP_VAR_INIT_16_NO_CACHEABLE
    #undef STOP_VAR_INIT_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_INIT_32_NO_CACHEABLE
    #undef START_VAR_INIT_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section data=".mcal_data_no_cacheable"  bss=".mcal_bss_no_cacheable"
#endif

#ifdef STOP_VAR_INIT_32_NO_CACHEABLE
    #undef STOP_VAR_INIT_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef START_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section data=".mcal_data_no_cacheable"  bss=".mcal_bss_no_cacheable"
#endif

#ifdef STOP_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef STOP_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_CLEARED_UNSPECIFIED_AE_NO_CACHEABLE
    #undef START_VAR_CLEARED_UNSPECIFIED_AE_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section bss=".dma_dest_buffer_bss" data=".dma_dest_buffer"
#endif

#ifdef STOP_VAR_CLEARED_UNSPECIFIED_AE_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_UNSPECIFIED_AE_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_INIT_UNSPECIFIED_AE_NO_CACHEABLE
    #undef START_VAR_INIT_UNSPECIFIED_AE_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section bss=".dma_dest_buffer_bss" data=".dma_dest_buffer"
#endif

#ifdef STOP_VAR_INIT_UNSPECIFIED_AE_NO_CACHEABLE
    #undef STOP_VAR_INIT_UNSPECIFIED_AE_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_SHARED_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef START_VAR_SHARED_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section data=".mcal_shared_data" bss=".mcal_shared_bss"
#endif

#ifdef STOP_VAR_SHARED_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef STOP_VAR_SHARED_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif

#ifdef START_VAR_SHARED_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef START_VAR_SHARED_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section bss=".mcal_shared_bss"
#endif

#ifdef STOP_VAR_SHARED_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef STOP_VAR_SHARED_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma ghs section
#endif
/********************************** IAR ***************************************/
#elif defined (_IAR_HULA_)
#ifdef START_CONFIG_DATA_BOOLEAN
    #undef START_CONFIG_DATA_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_const_cfg"
#endif

#ifdef STOP_CONFIG_DATA_BOOLEAN
    #undef STOP_CONFIG_DATA_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif
#ifdef START_CONFIG_DATA_8
    #undef START_CONFIG_DATA_8
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_const_cfg"
#endif

#ifdef STOP_CONFIG_DATA_8
    #undef STOP_CONFIG_DATA_8
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_CONFIG_DATA_16
    #undef START_CONFIG_DATA_16
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_const_cfg"
#endif

#ifdef STOP_CONFIG_DATA_16
    #undef STOP_CONFIG_DATA_16
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_CONFIG_DATA_32
    #undef START_CONFIG_DATA_32
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_const_cfg"
#endif

#ifdef STOP_CONFIG_DATA_32
    #undef STOP_CONFIG_DATA_32
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_CONFIG_DATA_UNSPECIFIED
    #undef START_CONFIG_DATA_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_const_cfg"
#endif

#ifdef STOP_CONFIG_DATA_UNSPECIFIED
    #undef STOP_CONFIG_DATA_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_CONFIG_DATA_8_NO_CACHEABLE
    #undef START_CONFIG_DATA_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_const_no_cacheable"
#endif

#ifdef STOP_CONFIG_DATA_8_NO_CACHEABLE
    #undef STOP_CONFIG_DATA_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_CONFIG_DATA_16_NO_CACHEABLE
    #undef START_CONFIG_DATA_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_const_no_cacheable"
#endif

#ifdef STOP_CONFIG_DATA_16_NO_CACHEABLE
    #undef STOP_CONFIG_DATA_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_CONFIG_DATA_32_NO_CACHEABLE
    #undef START_CONFIG_DATA_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_const_no_cacheable"
#endif

#ifdef STOP_CONFIG_DATA_32_NO_CACHEABLE
    #undef STOP_CONFIG_DATA_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_CONFIG_DATA_UNSPECIFIED_NO_CACHEABLE
    #undef START_CONFIG_DATA_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_const_no_cacheable"
#endif

#ifdef STOP_CONFIG_DATA_UNSPECIFIED_NO_CACHEABLE
    #undef STOP_CONFIG_DATA_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_CONST_BOOLEAN
    #undef START_CONST_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_const"
#endif

#ifdef STOP_CONST_BOOLEAN
    #undef STOP_CONST_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_CONST_8
    #undef START_CONST_8
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_const"
#endif

#ifdef STOP_CONST_8
    #undef STOP_CONST_8
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_CONST_16
    #undef START_CONST_16
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_const"
#endif

#ifdef STOP_CONST_16
    #undef STOP_CONST_16
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_CONST_32
    #undef START_CONST_32
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_const"
#endif

#ifdef STOP_CONST_32
    #undef STOP_CONST_32
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_CONST_UNSPECIFIED
    #undef START_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_const"
#endif

#ifdef STOP_CONST_UNSPECIFIED
    #undef STOP_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_CODE
    #undef START_CODE
    #undef MEMMAP_ERROR
    #pragma default_function_attributes = @ ".mcal_text"
#endif

#ifdef STOP_CODE
    #undef STOP_CODE
    #undef MEMMAP_ERROR
    #pragma default_function_attributes =
#endif

#ifdef START_CODE_FAST
    #undef START_CODE_FAST
    #undef MEMMAP_ERROR
    #pragma default_function_attributes = @ ".mcal_text"
#endif

#ifdef STOP_CODE_FAST
    #undef STOP_CODE_FAST
    #undef MEMMAP_ERROR
    #pragma default_function_attributes =
#endif

#ifdef START_CODE_SLOW
    #undef START_CODE_SLOW
    #undef MEMMAP_ERROR
    #pragma default_function_attributes = @ ".mcal_text"
#endif

#ifdef STOP_CODE_SLOW
    #undef STOP_CODE_SLOW
    #undef MEMMAP_ERROR
    #pragma default_function_attributes =
#endif

#ifdef START_CALLOUT_CODE
    #undef START_CALLOUT_CODE
    #undef MEMMAP_ERROR
    #pragma default_function_attributes = @ ".mcal_text"
#endif

#ifdef STOP_CALLOUT_CODE
    #undef STOP_CALLOUT_CODE
    #undef MEMMAP_ERROR
    #pragma default_function_attributes =
#endif

#ifdef START_RAMCODE
    #undef START_RAMCODE
    #undef MEMMAP_ERROR
    #pragma default_function_attributes = @ ".ramcode"
#endif

#ifdef STOP_RAMCODE
    #undef STOP_RAMCODE
    #undef MEMMAP_ERROR
    #pragma default_function_attributes =
#endif

#ifdef START_CODE_AC
    #undef START_CODE_AC
    #undef MEMMAP_ERROR
    #pragma default_function_attributes = @ ".access_code_rom"
#endif

#ifdef STOP_CODE_AC
    #undef STOP_CODE_AC
    #undef MEMMAP_ERROR
    #pragma default_function_attributes =
#endif

#ifdef START_VAR_CLEARED_BOOLEAN
    #undef START_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_bss"
#endif

#ifdef STOP_VAR_CLEARED_BOOLEAN
    #undef STOP_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_CLEARED_8
    #undef START_VAR_CLEARED_8
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_bss"
#endif

#ifdef STOP_VAR_CLEARED_8
    #undef STOP_VAR_CLEARED_8
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_CLEARED_16
    #undef START_VAR_CLEARED_16
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_bss"
#endif

#ifdef STOP_VAR_CLEARED_16
    #undef STOP_VAR_CLEARED_16
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_CLEARED_32
    #undef START_VAR_CLEARED_32
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_bss"
#endif

#ifdef STOP_VAR_CLEARED_32
    #undef STOP_VAR_CLEARED_32
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_CLEARED_UNSPECIFIED
    #undef START_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_bss"
#endif

#ifdef STOP_VAR_CLEARED_UNSPECIFIED
    #undef STOP_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_INIT_BOOLEAN
    #undef START_VAR_INIT_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_data"
#endif

#ifdef STOP_VAR_INIT_BOOLEAN
    #undef STOP_VAR_INIT_BOOLEAN
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_INIT_8
    #undef START_VAR_INIT_8
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_data"
#endif

#ifdef STOP_VAR_INIT_8
    #undef STOP_VAR_INIT_8
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_INIT_16
    #undef START_VAR_INIT_16
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_data"
#endif

#ifdef STOP_VAR_INIT_16
    #undef STOP_VAR_INIT_16
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_INIT_32
    #undef START_VAR_INIT_32
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_data"
#endif

#ifdef STOP_VAR_INIT_32
    #undef STOP_VAR_INIT_32
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_INIT_UNSPECIFIED
    #undef START_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_data"
#endif

#ifdef STOP_VAR_INIT_UNSPECIFIED
    #undef STOP_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
    #undef START_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_bss_no_cacheable"
#endif

#ifdef STOP_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_CLEARED_8_NO_CACHEABLE
    #undef START_VAR_CLEARED_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_bss_no_cacheable"
#endif

#ifdef STOP_VAR_CLEARED_8_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_CLEARED_16_NO_CACHEABLE
    #undef START_VAR_CLEARED_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_bss_no_cacheable"
#endif

#ifdef STOP_VAR_CLEARED_16_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_CLEARED_32_NO_CACHEABLE
    #undef START_VAR_CLEARED_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_bss_no_cacheable"
#endif

#ifdef STOP_VAR_CLEARED_32_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef START_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_bss_no_cacheable"
#endif

#ifdef STOP_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_INIT_BOOLEAN_NO_CACHEABLE
    #undef START_VAR_INIT_BOOLEAN_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_data_no_cacheable"
#endif

#ifdef STOP_VAR_INIT_BOOLEAN_NO_CACHEABLE
    #undef STOP_VAR_INIT_BOOLEAN_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_INIT_8_NO_CACHEABLE
    #undef START_VAR_INIT_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
   #pragma default_variable_attributes = @ ".mcal_data_no_cacheable"
#endif

#ifdef STOP_VAR_INIT_8_NO_CACHEABLE
    #undef STOP_VAR_INIT_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_INIT_16_NO_CACHEABLE
    #undef START_VAR_INIT_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
   #pragma default_variable_attributes = @ ".mcal_data_no_cacheable"
#endif

#ifdef STOP_VAR_INIT_16_NO_CACHEABLE
    #undef STOP_VAR_INIT_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_INIT_32_NO_CACHEABLE
    #undef START_VAR_INIT_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
   #pragma default_variable_attributes = @ ".mcal_data_no_cacheable"
#endif

#ifdef STOP_VAR_INIT_32_NO_CACHEABLE
    #undef STOP_VAR_INIT_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef START_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
   #pragma default_variable_attributes = @ ".mcal_data_no_cacheable"
#endif

#ifdef STOP_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef STOP_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_CLEARED_UNSPECIFIED_AE_NO_CACHEABLE
    #undef START_VAR_CLEARED_UNSPECIFIED_AE_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".dma_dest_buffer_bss"
#endif

#ifdef STOP_VAR_CLEARED_UNSPECIFIED_AE_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_UNSPECIFIED_AE_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_INIT_UNSPECIFIED_AE_NO_CACHEABLE
    #undef START_VAR_INIT_UNSPECIFIED_AE_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".dma_dest_buffer"
#endif

#ifdef STOP_VAR_INIT_UNSPECIFIED_AE_NO_CACHEABLE
    #undef STOP_VAR_INIT_UNSPECIFIED_AE_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_SHARED_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef START_VAR_SHARED_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_shared_data"
#endif

#ifdef STOP_VAR_SHARED_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef STOP_VAR_SHARED_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif

#ifdef START_VAR_SHARED_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef START_VAR_SHARED_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes = @ ".mcal_shared_bss"
#endif

#ifdef STOP_VAR_SHARED_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef STOP_VAR_SHARED_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
    #pragma default_variable_attributes =
#endif
/********************************** GCC ****************************************/
#elif defined (_GCC_HULA_)
#ifdef START_CONFIG_DATA_BOOLEAN
    #undef START_CONFIG_DATA_BOOLEAN
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CONFIG_DATA_BOOLEAN
    #undef STOP_CONFIG_DATA_BOOLEAN
    #undef MEMMAP_ERROR
#endif
#ifdef START_CONFIG_DATA_8
    #undef START_CONFIG_DATA_8
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CONFIG_DATA_8
    #undef STOP_CONFIG_DATA_8
    #undef MEMMAP_ERROR
#endif

#ifdef START_CONFIG_DATA_16
    #undef START_CONFIG_DATA_16
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CONFIG_DATA_16
    #undef STOP_CONFIG_DATA_16
    #undef MEMMAP_ERROR
#endif

#ifdef START_CONFIG_DATA_32
    #undef START_CONFIG_DATA_32
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CONFIG_DATA_32
    #undef STOP_CONFIG_DATA_32
    #undef MEMMAP_ERROR
#endif

#ifdef START_CONFIG_DATA_UNSPECIFIED
    #undef START_CONFIG_DATA_UNSPECIFIED
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CONFIG_DATA_UNSPECIFIED
    #undef STOP_CONFIG_DATA_UNSPECIFIED
    #undef MEMMAP_ERROR
#endif

#ifdef START_CONFIG_DATA_8_NO_CACHEABLE
    #undef START_CONFIG_DATA_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CONFIG_DATA_8_NO_CACHEABLE
    #undef STOP_CONFIG_DATA_8_NO_CACHEABLE
    #undef MEMMAP_ERROR

#endif

#ifdef START_CONFIG_DATA_16_NO_CACHEABLE
    #undef START_CONFIG_DATA_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CONFIG_DATA_16_NO_CACHEABLE
    #undef STOP_CONFIG_DATA_16_NO_CACHEABLE
    #undef MEMMAP_ERROR

#endif

#ifdef START_CONFIG_DATA_32_NO_CACHEABLE
    #undef START_CONFIG_DATA_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CONFIG_DATA_32_NO_CACHEABLE
    #undef STOP_CONFIG_DATA_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef START_CONFIG_DATA_UNSPECIFIED_NO_CACHEABLE
    #undef START_CONFIG_DATA_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CONFIG_DATA_UNSPECIFIED_NO_CACHEABLE
    #undef STOP_CONFIG_DATA_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef START_CONST_BOOLEAN
    #undef START_CONST_BOOLEAN
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CONST_BOOLEAN
    #undef STOP_CONST_BOOLEAN
    #undef MEMMAP_ERROR
#endif

#ifdef START_CONST_8
    #undef START_CONST_8
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CONST_8
    #undef STOP_CONST_8
    #undef MEMMAP_ERROR
#endif

#ifdef START_CONST_16
    #undef START_CONST_16
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CONST_16
    #undef STOP_CONST_16
    #undef MEMMAP_ERROR
#endif

#ifdef START_CONST_32
    #undef START_CONST_32
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CONST_32
    #undef STOP_CONST_32
    #undef MEMMAP_ERROR
#endif

#ifdef START_CONST_UNSPECIFIED
    #undef START_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CONST_UNSPECIFIED
    #undef STOP_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#endif

#ifdef START_CODE
    #undef START_CODE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CODE
    #undef STOP_CODE
    #undef MEMMAP_ERROR
#endif

#ifdef START_CODE_FAST
    #undef START_CODE_FAST
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CODE_FAST
    #undef STOP_CODE_FAST
    #undef MEMMAP_ERROR
#endif

#ifdef START_CODE_SLOW
    #undef START_CODE_SLOW
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CODE_SLOW
    #undef STOP_CODE_SLOW
    #undef MEMMAP_ERROR
#endif

#ifdef START_CALLOUT_CODE
    #undef START_CALLOUT_CODE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CALLOUT_CODE
    #undef STOP_CALLOUT_CODE
    #undef MEMMAP_ERROR
#endif

#ifdef START_RAMCODE
    #undef START_RAMCODE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_RAMCODE
    #undef STOP_RAMCODE
    #undef MEMMAP_ERROR
#endif

#ifdef START_CODE_AC
    #undef START_CODE_AC
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_CODE_AC
    #undef STOP_CODE_AC
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_CLEARED_BOOLEAN
    #undef START_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_CLEARED_BOOLEAN
    #undef STOP_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_CLEARED_8
    #undef START_VAR_CLEARED_8
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_CLEARED_8
    #undef STOP_VAR_CLEARED_8
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_CLEARED_16
    #undef START_VAR_CLEARED_16
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_CLEARED_16
    #undef STOP_VAR_CLEARED_16
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_CLEARED_32
    #undef START_VAR_CLEARED_32
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_CLEARED_32
    #undef STOP_VAR_CLEARED_32
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_CLEARED_UNSPECIFIED
    #undef START_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_CLEARED_UNSPECIFIED
    #undef STOP_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_INIT_BOOLEAN
    #undef START_VAR_INIT_BOOLEAN
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_INIT_BOOLEAN
    #undef STOP_VAR_INIT_BOOLEAN
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_INIT_8
    #undef START_VAR_INIT_8
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_INIT_8
    #undef STOP_VAR_INIT_8
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_INIT_16
    #undef START_VAR_INIT_16
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_INIT_16
    #undef STOP_VAR_INIT_16
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_INIT_32
    #undef START_VAR_INIT_32
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_INIT_32
    #undef STOP_VAR_INIT_32
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_INIT_UNSPECIFIED
    #undef START_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_INIT_UNSPECIFIED
    #undef STOP_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
    #undef START_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_BOOLEAN_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_CLEARED_8_NO_CACHEABLE
    #undef START_VAR_CLEARED_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_CLEARED_8_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_CLEARED_16_NO_CACHEABLE
    #undef START_VAR_CLEARED_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_CLEARED_16_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_CLEARED_32_NO_CACHEABLE
    #undef START_VAR_CLEARED_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_CLEARED_32_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef START_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_INIT_BOOLEAN_NO_CACHEABLE
    #undef START_VAR_INIT_BOOLEAN_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_INIT_BOOLEAN_NO_CACHEABLE
    #undef STOP_VAR_INIT_BOOLEAN_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_INIT_8_NO_CACHEABLE
    #undef START_VAR_INIT_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_INIT_8_NO_CACHEABLE
    #undef STOP_VAR_INIT_8_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_INIT_16_NO_CACHEABLE
    #undef START_VAR_INIT_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_INIT_16_NO_CACHEABLE
    #undef STOP_VAR_INIT_16_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_INIT_32_NO_CACHEABLE
    #undef START_VAR_INIT_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_INIT_32_NO_CACHEABLE
    #undef STOP_VAR_INIT_32_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef START_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR

#endif

#ifdef STOP_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef STOP_VAR_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef START_VAR_CLEARED_UNSPECIFIED_AE_NO_CACHEABLE
    #undef START_VAR_CLEARED_UNSPECIFIED_AE_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_CLEARED_UNSPECIFIED_AE_NO_CACHEABLE
    #undef STOP_VAR_CLEARED_UNSPECIFIED_AE_NO_CACHEABLE
    #undef MEMMAP_ERROR

#endif

#ifdef START_VAR_INIT_UNSPECIFIED_AE_NO_CACHEABLE
    #undef START_VAR_INIT_UNSPECIFIED_AE_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_INIT_UNSPECIFIED_AE_NO_CACHEABLE
    #undef STOP_VAR_INIT_UNSPECIFIED_AE_NO_CACHEABLE
    #undef MEMMAP_ERROR

#endif

#ifdef START_VAR_SHARED_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef START_VAR_SHARED_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_SHARED_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef STOP_VAR_SHARED_INIT_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR

#endif

#ifdef START_VAR_SHARED_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef START_VAR_SHARED_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif

#ifdef STOP_VAR_SHARED_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef STOP_VAR_SHARED_CLEARED_UNSPECIFIED_NO_CACHEABLE
    #undef MEMMAP_ERROR
#endif
#endif
/********************************* ReGPIO error *******************************/
#ifdef MEMMAP_ERROR
    #error "MemMap.h, No valid section define found."
#endif
