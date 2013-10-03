file(GLOB br_net_uv_SOURCES backends/libuv/*.c)
add_library (br_net_uv ${br_net_uv_SOURCES} )

add_subdirectory (samples)
