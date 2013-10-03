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

set(DR_BIN ${CMAKE_CURRENT_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${DR_BIN})
set(EXECUTABLE_OUTPUT_PATH ${DR_BIN})

include(MacroUseUv)
macro_use_uv()

include(MacroUseHttpparser)
macro_use_httpparser()

include_directories (${PROJECT_SOURCE_DIR}/internal_libs/trace )
include_directories (${PROJECT_SOURCE_DIR}/internal_libs/net/include )

add_subdirectory (internal_libs)
add_subdirectory (components)








