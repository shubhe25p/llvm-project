if(LIBC_CONF_PRINTF_DISABLE_WIDE)
  list(PREPEND printf_core_copts "COMPILE_OPTIONS")
  list(APPEND printf_core_copts "-DLIBC_COPT_PRINTF_DISABLE_WIDE")
endif()

add_libc_unittest(
  parser_test
  SUITE
    libc_stdio_unittests
  SRCS
    parser_test.cpp
  LINK_LIBRARIES
    LibcPrintfHelpers
  DEPENDS
    libc.src.stdio.printf_core.parser
    libc.src.stdio.printf_core.core_structs
    libc.src.__support.CPP.string_view
    libc.src.__support.arg_list
    ${printf_core_copts}
)

add_libc_unittest(
  writer_test
  SUITE
    libc_stdio_unittests
  SRCS
    writer_test.cpp
  DEPENDS
    libc.src.stdio.printf_core.writer
    libc.src.string.memory_utils.inline_memcpy
    libc.src.__support.CPP.string_view
    ${printf_core_copts}
)

add_libc_unittest(
  converter_test
  SUITE
    libc_stdio_unittests
  SRCS
    converter_test.cpp
  DEPENDS
    libc.src.stdio.printf_core.converter
    libc.src.stdio.printf_core.writer
    libc.src.stdio.printf_core.core_structs
    ${printf_core_copts}
)
