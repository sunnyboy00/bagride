file(GLOB br_net_uv_SOURCES backends/libuv/*.c)
add_library (${BR_NET_UV_LIB} ${br_net_uv_SOURCES} )

add_subdirectory (samples)
