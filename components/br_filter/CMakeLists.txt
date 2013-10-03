set(MYMAIN br_filter)

if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(MYMAIN "${MYMAIN}_d")
endif (CMAKE_BUILD_TYPE MATCHES Debug)

add_executable (${MYMAIN} main)





