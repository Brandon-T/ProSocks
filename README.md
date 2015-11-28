ProSocks
========

A Powerful Cross-Platform Socket Library

- Compiles with a standard C and/or C++ compiler.
- Supports SSL/TLS.
- Supports Non-Blocking & Blocking.
- Supports Timeouts.
- Exports for Java.


Libraries to link to (in order):

  - user32
  - openssl
  - libcurl
  - libcrypto
  - ws2_32
  - gdi32
  - wldap32
  - libz
  
Define the following pre-processor arguments:
  - CURL_STATICLIB
  - CURL_SSL

To build the above libraries, use the following commands (in order):

Pre-Build Notes:

    #To compile as 32-bit:
    ./configure --build=i686-pc-windows "CFLAGS=-m32" "CXXFLAGS=-m32" "LDFLAGS=-m32"
    
    #To compile as 64-bit:
    ./configure --build=x86_64-w64-mingw32 "CFLAGS=-m64" "CXXFLAGS=-m64" "LDFLAGS=-m64"
    
    #To set the build paths:
    BINARY_PATH=/usr/local/bin \
    INCLUDE_PATH=/usr/local/include \
    LIBRARY_PATH=/usr/local/lib \
    ./configure



Building ZLIB: http://zlib.net/zlib-1.2.8.tar.gz

    BINARY_PATH=/usr/local/bin \
    INCLUDE_PATH=/usr/local/include \
    LIBRARY_PATH=/usr/local/lib \
    make -f win32/Makefile.gcc install


Building OpenSSL: https://www.openssl.org/source/openssl-1.0.2d.tar.gz

    ./configure mingw --no-shared --prefix=/usr/local
    make install


Building LIBCURL: http://curl.haxx.se/download/curl-7.45.0.tar.gz

    ./configure —-enable-static —-enable-shared —-enable-ipv6 —-with-ssl=/usr/local
    make install
