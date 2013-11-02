set( BR_NET_SAMPLE br_net_sample)

if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(BR_NET_SAMPLE "${BR_NET_SAMPLE}_d")
endif (CMAKE_BUILD_TYPE MATCHES Debug)

add_executable (${BR_NET_SAMPLE} br_net_sample.c)
target_link_libraries (${BR_NET_SAMPLE} ${BR_NET_UV_LIB} )
target_link_libraries (${BR_NET_SAMPLE} ${HTTPARSER_A} )
target_link_libraries (${BR_NET_SAMPLE} ${MMTRACE_A} )
target_link_libraries (${BR_NET_SAMPLE} ${UV_A} )

if(WIN32)
  target_link_libraries (${BR_NET_SAMPLE} ${MMWINCOMPAT_A} )
  target_link_libraries (${BR_NET_SAMPLE} ${LIBWS2_32_A} )
  target_link_libraries (${BR_NET_SAMPLE} ${LIBPSAPI_A} )
  target_link_libraries (${BR_NET_SAMPLE} ${LIBIPHLPAPI_A} )
endif(WIN32)

  
#target_link_libraries (${BR_NET_SAMPLE} -lpthread -lrt)


#add_subdirectory(boostrap)










