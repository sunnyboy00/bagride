set( BR_NET_SAMPLE br_net_sample)

if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(BR_NET_SAMPLE "${BR_NET_SAMPLE}_d")
endif (CMAKE_BUILD_TYPE MATCHES Debug)

add_executable (${BR_NET_SAMPLE} br_net_sample.c)
target_link_libraries (${BR_NET_SAMPLE} br_net_uv )
target_link_libraries (${BR_NET_SAMPLE} ${HTTPARSER_A} )
target_link_libraries (${BR_NET_SAMPLE} br_trace )
target_link_libraries (${BR_NET_SAMPLE} ${UV_A} )
target_link_libraries (${BR_NET_SAMPLE} -lpthread -lrt)


#add_subdirectory(boostrap)











