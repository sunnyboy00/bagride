MACRO(macro_use_httpparser)

set( CURRENT_HTTPARSER_DIR ${PROJECT_SOURCE_DIR}/external_libs/libhttp-parser )

set (HTTPARSER_A ${CURRENT_HTTPARSER_DIR}/libhttp-parser.a)

include_directories (${CURRENT_HTTPARSER_DIR}/)

set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE -D__WITH_HTTPARSER__" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GNU_SOURCE -D__WITH_HTTPARSER__" )


ENDMACRO(macro_use_httpparser)




