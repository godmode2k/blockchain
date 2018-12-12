#!/bin/sh



BIN_GCC=/usr/bin/g++

OPTS="-Wall -O2 -std=c++11"
LIBS="-lcryptopp"
INCS="-I/usr/include/crypto++ -I./cryptopp-pem"
SRCS="./cryptopp-pem/pem-com.cpp ./cryptopp-pem/pem-rd.cpp ./cryptopp-pem/pem-wr.cpp"



echo "$BIN_GCC $OPTS -o crypto_test crypto_test.cpp $SRCS $INCS $LIBS"
$BIN_GCC $OPTS -o crypto_test crypto_test.cpp $SRCS $INCS $LIBS

