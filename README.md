bagride
=======

C embeddable network library

# depends 
http-parser, libuv


# http-parser
cd bagride/external_libs/libhttp-parser && ./buildit

# libuv
cd bagride/external_libs/libuv && ./autogen.sh && ./configure && make
