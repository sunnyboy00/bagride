cmake_minimum_required(VERSION 2.8)
file(GLOB http-parser_SOURCES *.c)
add_library (http-parser ${http-parser_SOURCES} )

