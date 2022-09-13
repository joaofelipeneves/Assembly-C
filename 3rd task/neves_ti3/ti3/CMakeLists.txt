cmake_minimum_required(VERSION 3.20)
project(caoss C)

set (DEBUG true)

set(CMAKE_C_STANDARD 11)

###########
# Software Dependencies
###########

find_package(BISON)
if (NOT BISON_FOUND)
    message(FATAL_ERROR "Install the bison parser generator")
endif()

find_package(FLEX)
if (NOT FLEX_FOUND)
    message(FATAL_ERROR "Install the flex lexical analyser")
endif()

BISON_TARGET(caas_parser
        ${CMAKE_CURRENT_SOURCE_DIR}/caas/caas.y
        ${CMAKE_CURRENT_BINARY_DIR}/caas_parser.c
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/caas_parser.h)

FLEX_TARGET(caas_lexer
        ${CMAKE_CURRENT_SOURCE_DIR}/caas/caas.l
        ${CMAKE_CURRENT_BINARY_DIR}/caas_lexer.c
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/caas_lexer.h)

ADD_FLEX_BISON_DEPENDENCY(caas_lexer caas_parser)

###########
# CAAS
###########

include_directories(include)

add_executable(caas
        ${CMAKE_CURRENT_SOURCE_DIR}/caas/caas.c
        ${CMAKE_CURRENT_SOURCE_DIR}/caas/opcodes.c
        ${CMAKE_CURRENT_SOURCE_DIR}/caoss/utils.c
        ${BISON_caas_parser_OUTPUTS}
        ${FLEX_caas_lexer_OUTPUTS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

if (DEBUG)
    target_compile_definitions(caas PRIVATE -DDEBUG)
endif()

###########
# CAOSS
###########

add_executable(caoss
        ${CMAKE_CURRENT_SOURCE_DIR}/caoss/caoss.c
        ${CMAKE_CURRENT_SOURCE_DIR}/caoss/memory.c
        ${CMAKE_CURRENT_SOURCE_DIR}/caoss/cpu.c
        ${CMAKE_CURRENT_SOURCE_DIR}/caoss/alu.c
        ${CMAKE_CURRENT_SOURCE_DIR}/caoss/os.c
        ${CMAKE_CURRENT_SOURCE_DIR}/caoss/utils.c
        )
if (DEBUG)
    target_compile_definitions(caoss PRIVATE -DDEBUG)
endif()