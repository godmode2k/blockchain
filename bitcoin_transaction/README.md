# Bitcoin raw transaction


Summary
----------
> The sources show you how to make a Bitcoin raw transaction in C/C++.
>
> (But not done yet.)
>
> This is a test version. so, USE AT YOUR OWN RISK.

    Source article:
    (Python version)
    http://www.righto.com/2014/02/bitcoins-hard-way-using-raw-bitcoin.html


Environment
----------
> build all and tested on GNU/Linux

    GNU/Linux: Ubuntu 16.04_x64 LTS


Raw transaction (C/C++) example
----------
    [Dependency]
     - bitcoin core source code
    $ git clone https://github.com/bitcoin/bitcoin.git

    [Build]
    $ g++ -o make_transaction make_transaction.cpp \
        ./bitcoin-master/src/base58.cpp \
        ./bitcoin-master/src/crypto/sha256.cpp \
        -Wall -O2 -std=c++11 \
        -I./bitcoin-master/src


