
MACRO(macro_use_lua)

set( CURRENT_LUA_VERSION lua-5.2.2 )
set( CURRENT_LUA_DIR ${PROJECT_SOURCE_DIR}/external_libs/lua/${CURRENT_LUA_VERSION} )

set (LUA_A ${CURRENT_LUA_DIR}/lib/liblua.a)

include_directories (${CURRENT_LUA_DIR}/src)

set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__WITH_LUA__" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__WITH_LUA__" )

ENDMACRO(macro_use_lua)




