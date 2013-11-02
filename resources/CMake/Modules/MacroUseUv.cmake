
MACRO(macro_use_uv)

set( CURRENT_UV_DIR ${PROJECT_SOURCE_DIR}/external_libs/libuv )

if(WIN32)
  set (UV_A ${CURRENT_UV_DIR}/libuv.a)
else(WIN32)
  set (UV_A ${CURRENT_UV_DIR}/.libs/libuv.a)
endif(WIN32)

include_directories (${CURRENT_UV_DIR}/include)

set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE -D__WITH_UV__" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GNU_SOURCE -D__WITH_UV__" )


ENDMACRO(macro_use_uv)




