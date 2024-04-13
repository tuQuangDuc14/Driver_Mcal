TEST_NAME_DESCRIPTION = "Test "
LIST_TC_OF_TS = ['Mcl_TC_001']
LIST_TC_DESCRIPTION = ['test varible DMA Mem to Mem']

LIST_MODULE_RELATED = ['Gpio']

SRC_DIRS =[
    f'{PRO_DIR}/../drivers/{MODULE}/generic/src',
    f'{PRO_DIR}/../drivers/{MODULE}/ip/IP_HULA/source',
    f'{PRO_DIR}/../drivers/{MODULE}/specific/STM32/src',
    f'{PRO_DIR}/../env/env_{COMPILER}/source',
    f'{TEST_DIR}/{TEST_NAME}/src'
]

for MODULE_RELATED in LIST_MODULE_RELATED:
    SRC_DIRS.append(f'{PRO_DIR}/../drivers/{MODULE_RELATED}/generic/src')
    SRC_DIRS.append(f'{PRO_DIR}/../drivers/{MODULE_RELATED}/ip/IP_HULA/source')
    SRC_DIRS.append(f'{PRO_DIR}/../drivers/{MODULE_RELATED}/specific/STM32/src')

for TC in LIST_TC_OF_TS:
    SRC_DIRS.append(f'{TEST_DIR}/{TEST_NAME}/{TC}/src')

INCLUDE_DIRS = [
    f'{PRO_DIR}/../drivers/{MODULE}/generic/include',
    f'{PRO_DIR}/../drivers/{MODULE}/ip/IP_HULA/include',
    f'{PRO_DIR}/../drivers/{MODULE}/specific/STM32/include',
    f'{PRO_DIR}/../env/env_{COMPILER}/include',
    f'{TEST_DIR}/{TEST_NAME}/include'
]

for MODULE_RELATED in LIST_MODULE_RELATED:
    INCLUDE_DIRS.append(f'{PRO_DIR}/../drivers/{MODULE_RELATED}/generic/include')
    INCLUDE_DIRS.append(f'{PRO_DIR}/../drivers/{MODULE_RELATED}/ip/IP_HULA/include')
    INCLUDE_DIRS.append(f'{PRO_DIR}/../drivers/{MODULE_RELATED}/specific/STM32/include')

INCLUDE_DIRS.append(f'{PRO_DIR}/../env/memmap')

for TC in LIST_TC_OF_TS:
    INCLUDE_DIRS.append(f'{TEST_DIR}/{TEST_NAME}/{TC}/include')

XDM_FILES = [
    f'{TEST_DIR}/{TEST_NAME}/config/Gpio.xdm',
    f'{TEST_DIR}/{TEST_NAME}/config/EcuC.xdm',
    f'{TEST_DIR}/{TEST_NAME}/config/Resource.xdm',
    f'{TEST_DIR}/{TEST_NAME}/config/Mcl.xdm'
]
