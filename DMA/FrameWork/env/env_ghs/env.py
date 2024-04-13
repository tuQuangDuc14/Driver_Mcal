LINKER_FILE = f'{PRO_DIR}/../env/env_{COMPILER}/linker/ThoNV_linker_ram_C0.ld'
LK_FILE = "C:/ghs/comp_201714/elxr.exe"
CC_FILE = "C:/ghs/comp_201714/ccarm.exe"
AC_FILE = "C:/ghs/comp_201714/asarm.exe"
VERDION_FILE = "C:/ghs/comp_201714/gversion.exe"
POST_COMPILE = "C:/ghs/comp_201714/dblink.exe"

BIN_COMPILE_OPTS= [
    '--bin',
]

HEX_COMPILE_OPTS = [
    '--ihex'
]

CC_OPTS = [
    '-c',
    '-cpu=cortexm4',
    '-thumb',
    '-Osize',
    '-Wall',
    '-ansi',
    '-G',
    '-preprocess_assembly_files',
    '--no_exceptions',
    '-dual_debug',
    '--prototype_errors',
    '-Wundef',
    '-noslashcomment',
    '-Wimplicit-int',
    '-Wshadow',
    '-Wtrigraphs',
    '--no_commons',
    '--incorrect_pragma_warnings',
    '-keeptempfiles',
    '--short_enum',
    '--gnu_asm',
    '--ghstd=last',
    '-Odebug'
]

LK_OPTS = [
    '-Reset_Handler', 
    '-keepmap', 
    '-LC:/ghs/comp_201714/lib/thumb2', 
    '-lmath_sf', 
    '-lstartup', 
    '-lsys', 
    '-larch', 
    '-lansi', 
    '-lutf8_s32', 
    '-Mn -delete', 
    '-v', 
    '-ignore_debug_references', 
    '-map', 
    '-keepmap', 
    '-physical_address_offset=0', 
    '-T', 
    f'{LINKER_FILE}'
]
AC_OPTS = [
    '-cpu=cortexm4',
    # '-preprocess_assembly_files',
    # '-c',
    '-list'
]