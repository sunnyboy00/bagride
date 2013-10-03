bagride
=======

C embeddable network library

# example 
br_net_sample.c

# depends 
http-parser, libuv

# http-parser
cd external_libs/libhttp-parser && ./buildit

# libuv
cd external_libs/libuv && ./autogen.sh && ./configure && make

# libbagride
./configure && make
