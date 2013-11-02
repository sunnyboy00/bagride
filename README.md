bagride
=======

C embeddable network library built on top of libuv, libhttp-parser.

#build linux
./configure && make external_libs && make 

#build windows
./configure win && make external_libs && make

#usage 
see  https://github.com/manuel-m/bagride/blob/master/internal_libs/net/samples/br_net_sample.c 

# depends 
http-parser, libuv (provided)


