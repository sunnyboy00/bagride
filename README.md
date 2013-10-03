bagride
=======

C embeddable network library

# example 
br_net_sample.c

# depends 
http-parser, libuv

# http-parser
cd bagride/external_libs/libhttp-parser && ./buildit

# libuv
cd bagride/external_libs/libuv && ./autogen.sh && ./configure && make

# libbagride
cd bagride && ./configure && make
