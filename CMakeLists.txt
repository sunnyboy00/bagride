#==============================================================================
# CMake version minimum requirement
# 
#==============================================================================
cmake_minimum_required (VERSION 2.8) 

#==============================================================================
# br
#==============================================================================
project (br) 

#==============================================================================
# Additional package ressource finders
#==============================================================================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/ressources/CMake/Modules")

#==============================================================================
# The macro below forces the build directory to be different from source directory
#==============================================================================
include(MacroOutOfSourceBuild)
macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")

include(MacroLogAll)
macro_logall()

include(MacroDefineCFlags)
macro_define_cflags()

include(MacroDefineCXXFlags)
macro_define_cxxflags()

set(BR_DIST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dist)
file(MAKE_DIRECTORY ${BR_DIST_DIR})
set(EXECUTABLE_OUTPUT_PATH ${BR_DIST_DIR})
set(LIBRARY_OUTPUT_PATH ${BR_DIST_DIR})

include(MacroUseUv)
macro_use_uv()

include(MacroUseHttpparser)
macro_use_httpparser()

#lib name definition
set( BR_TRACE_LIB br_trace)
set( BR_PARSE_LIB br_parse)
set( BR_NET_UV_LIB br_net_uv)

#debug release namming context
if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(BR_TRACE_LIB "${BR_TRACE_LIB}_d")
  set(BR_NET_UV_LIB "${BR_NET_UV_LIB}_d")
  set(BR_PARSE_LIB "${BR_PARSE_LIB}_d")
endif (CMAKE_BUILD_TYPE MATCHES Debug)


include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include )

add_subdirectory (src)









