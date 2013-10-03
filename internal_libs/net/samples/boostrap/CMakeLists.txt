set( BR_TCP0 br_tcp0)
set( BR_UDP0 br_udp0)
set( BR_HTTP0 br_http0)

if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(BR_TCP0 "${BR_TCP0}_d")
  set(BR_UDP0 "${BR_UDP0}_d")
  set(BR_HTTP0 "${BR_HTTP0}_d")
endif (CMAKE_BUILD_TYPE MATCHES Debug)

add_executable (${BR_TCP0} br_uv_tcp0.c)
target_link_libraries (${BR_TCP0} br_trace )
target_link_libraries (${BR_TCP0} ${UV_A} )
target_link_libraries (${BR_TCP0} -lpthread )

add_executable (${BR_UDP0} br_uv_udp0.c)
target_link_libraries (${BR_UDP0} br_trace )
target_link_libraries (${BR_UDP0} ${UV_A} )
target_link_libraries (${BR_UDP0} -lpthread )

add_executable (${BR_HTTP0} br_uv_http0.c)
target_link_libraries (${BR_HTTP0} br_net_uv )
target_link_libraries (${BR_HTTP0} br_trace )
target_link_libraries (${BR_HTTP0} ${UV_A} )
target_link_libraries (${BR_HTTP0} ${HTTPARSER_A} )
target_link_libraries (${BR_HTTP0} -lpthread )












