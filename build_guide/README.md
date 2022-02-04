# Blockchain Node build guide


Summary
----------
> Build a BTC/ETH/DSH/QTUM/XVG/XRP/DOGE/...
> - hjkim, 2018.11.13


Environment
----------
> build all and tested on GNU/Linux

    GNU/Linux: Ubuntu 16.04_x64 LTS, 20.04_x64 LTS


Ethereum (ETH)
----------
    https://github.com/ethereum/
    https://github.com/ethereum/go-ethereum/releases

```sh
path: /nodes/eth_mainnet/

//(old version)
//$ wget https://dl.google.com/go/go1.10.3.linux-amd64.tar.gz
//$ tar xzvf go1.10.3.linux-amd64.tar.gz -C /usr/local/

$ wget https://golang.org/dl/go1.16.linux-amd64.tar.gz
$ tar -C /usr/local -xzf go1.16.linux-amd64.tar.gz
$ echo "export PATH=$PATH:/usr/local/go/bin" >> $HOME/.profile

// Unstable version
//$ git clone https://github.com/ethereum/go-ethereum.git

// Release version
//$ wget https://github.com/ethereum/go-ethereum/archive/v1.8.21.tar.gz
//$ wget https://github.com/ethereum/go-ethereum/archive/v1.8.26.tar.gz
//$ wget https://github.com/ethereum/go-ethereum/archive/refs/tags/v1.10.2.tar.gz
$ wget https://github.com/ethereum/go-ethereum/archive/refs/tags/v1.10.15.tar.gz

$ tar xzvf v1.10.15.tar.gz
$ cd go-ethereum-1.10.15
$ make all


// Run node
// v1.9.x ~ (with --allow-insecure-unlock)
///nodes/eth_mainnet# nohup ./geth --rpc --rpcport 8545 --rpccorsdomain "*" --datadir /nodes/eth_mainnet/sync_data --port 30304 --rpcapi "db,eth,net,web3,personal,txpool" --syncmode "fast" --cache 4096 --allow-insecure-unlock &

// go-ethereum-1.10.15
/nodes/eth_mainnet# nohup ./geth --http --http.port 8545 --http.corsdomain "*" --datadir /nodes/eth_mainnet/sync_data --port 30304 --http.api "db,eth,net,web3,personal,txpool,miner,admin" --syncmode "snap" --cache 4096 --allow-insecure-unlock &


// Client
/nodes/eth_mainnet# ./geth attach http://localhost:8545



--------------------------
Private Network
--------------------------
1. build Ethereum (go-ethereum v1.10.15)

$ mkdir /test/eth_test && cd /test/eth_test
$ wget https://dl.google.com/go/go1.15.5.linux-amd64.tar.gz
$ tar xzvf go1.15.5.linux-amd64.tar.gz -C /usr/local/

$ echo "export PATH=$PATH:/usr/local/go/bin" >> $HOME/.profile

$ git clone https://github.com/ethereum/go-ethereum.git -b v1.10.15
$ cd go-ethereum-1.10.15 && make all
$ cd .. && ln -s go-ethereum-1.10.15/build/bin/geth .


2. creates genesis.json

{
"alloc": {
},
"config": {
  "chainId": 1000,
  "homesteadBlock": 0,
  "byzantiumBlock": 0,
  "constantinopleBlock": 0,
  "petersburgBlock": 0,
  "eip150Block": 0,
  "eip155Block": 0,
  "eip158Block": 0
},
"nonce": "0x0000000000000033",
"timestamp": "0x0",
"parentHash": "0x0000000000000000000000000000000000000000000000000000000000000000",
"gasLimit": "0x8000000",
"difficulty": "0x10",
"mixhash": "0x0000000000000000000000000000000000000000000000000000000000000000",
"coinbase": "0x0000000000000000000000000000000000000000"
}


3. run

// node #1
$ mkdir /test/eth_test/sync_data
$ ./geth init --datadir /test/eth_test/sync_data genesis.json

// node #2
$ mkdir /test/eth_test/sync_data2
$ ./geth init --datadir /test/eth_test/sync_data2 genesis.json

// node #3
$ mkdir /test/eth_test/sync_data3
$ ./geth init --datadir /test/eth_test/sync_data3 genesis.json


// data dir: /test/eth_test/sync_data
static-nodes.json
[
"enode://<node2>...@ip:port",
"enode://<node3>...@ip:port"
]

// data dir: /test/eth_test/sync_data2
static-nodes.json
[
"enode://<node1>...@ip:port",
]

// data dir: /test/eth_test/sync_data3
static-nodes.json
[
"enode://<node1>...@ip:port",
]



// Run
// go-ethereum-1.10.15
//
// node1
$ ./geth --networkid 1000 --nodiscover --http --http.addr 0.0.0.0 --http.port 8544 --http.corsdomain "*" --datadir /test/eth_test/sync_data --port 30304 --http.api "db,eth,net,web3,personal,txpool,miner,admin" --syncmode "snap" --cache 4096 --allow-insecure-unlock

// node2
$ ./geth --networkid 1000 --nodiscover --http --http.addr 0.0.0.0 --http.port 8544 --http.corsdomain "*" --datadir /test/eth_test/sync_data2 --port 30305 --http.api "db,eth,net,web3,personal,txpool,miner,admin" --syncmode "snap" --cache 4096 --allow-insecure-unlock

// node3
$ ./geth --networkid 1000 --nodiscover --http --http.addr 0.0.0.0 --http.port 8544 --http.corsdomain "*" --datadir /test/eth_test/sync_data3 --port 30306 --http.api "db,eth,net,web3,personal,txpool,miner,admin" --syncmode "snap" --cache 4096 --allow-insecure-unlock


// Client
$ ./geth attach http://localhost:8544
> miner.start(1)
> miner.stop()
```



Bitcoin (BTC)
----------
    https://github.com/bitcoin/bitcoin

    download: released bitcoin-0.16.0{3}, 0.20.1, ...

```sh
path: /nodes/btc_mainnet/bitcoin-0.16.0{3}

// v0.21.0
$ wget https://github.com/bitcoin/bitcoin/archive/refs/rags/v0.21.0.tar.gz


// dependencies
$ sudo apt-get install build-essential libtool autotools-dev autoconf pkg-config libssl-dev
$ sudo apt-get install libboost-all-dev
$ sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler
$ sudo apt-get install libqrencode-dev autoconf openssl libssl-dev libevent-dev
$ sudo apt-get install libminiupnpc-dev

// db4
$ mkdir db4 && cd db4
$ wget http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz
$ tar xzvf db-4.8.30.NC.tar.gz && cd db-4.8.30.NC/build_unix
$ ../dist/configure --enable-cxx --disable-shared --with-pic --prefix=/nodes/btc_mainnet/bitcoin-0.16.0/db4/
$ make install


$ ./autogen.sh
$ ./configure LDFLAGS="-L/nodes/btc_mainnet/bitcoin-0.16.0/db4/lib/" CPPFLAGS="-I/nodes/btc_mainnet/bitcoin-0.16.0/db4/include/"
$ make -s -j6


// v0.21.0
$ ./autogen.sh
$ ./configure LDFLAGS="-L/nodes/btc_mainnet/bitcoin-0.21.0/db4/lib/" CPPFLAGS="-I/nodes/btc_mainnet/bitcoin-0.21.0/db4/include/" --enable-bitcore-rpc
$ make -s -j6



[bitcoin.conf]
rpcuser=
rpcpassword=
rpcport=8332
#rpcallowip=192.168.0.0/24
rpcallowip=127.0.0.1
#addnode=
server=1
daemon=1
listen=1


// Run node
/nodes/btc_mainnet# ./bitcoind -daemon -datadir=/nodes/btc_mainnet/sync_data

// Client
/nodes/btc_mainnet# ./bitcoin-cli -datadir=/nodes/btc_mainnet/sync_data -rpcwallet=<walletname>
```



DASH (DSH) old
----------
    https://github.com/dashpay/dash

    download: released dash-0.12.3.3

```sh
path: /nodes/dsh_mainnet/dash-0.12.3.3

// dependencies
$ sudo apt-get install build-essential libtool autotools-dev autoconf pkg-config libssl-dev
$ sudo apt-get install libboost-all-dev
$ sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler
$ sudo apt-get install libqrencode-dev autoconf openssl libssl-dev libevent-dev
$ sudo apt-get install libminiupnpc-dev

// db4
$ mkdir db4 && cd db4
$ wget http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz
$ tar xzvf db-4.8.30.NC.tar.gz && cd db-4.8.30.NC/build_unix
$ ../dist/configure --enable-cxx --disable-shared --with-pic --prefix=/nodes/dsh_mainnet/dash-0.12.3.3/db4/
$ make install


$ ./autogen.sh
$ ./configure LDFLAGS="-L/nodes/dsh_mainnet/dash-0.12.3.3/db4/lib/" CPPFLAGS="-I/nodes/dsh_mainnet/dash-0.12.3.3/db4/include/"
$ make -s -j6


[dash.conf]
rpcuser=
rpcpassword=
rpcport=29080
#rpcallowip=192.168.0.0/24
rpcallowip=127.0.0.1
#addnode=
server=1
daemon=1
listen=1


// Run node
/nodes/dsh_mainnet# ./dashd -daemon -datadir=/nodes/dsh_mainnet/sync_data

// Client
/nodes/dsh_mainnet# ./dash-cli -datadir=/nodes/dsh_mainnet/sync_data
```



DASH (DSH)
----------
    https://github.com/dashpay/dash

    download: released dash-0.13.3.0

```sh
path: /nodes/dsh_mainnet/dash-0.13.3.0

// dependencies
sudo apt-get install build-essential libtool autotools-dev autoconf pkg-config libssl-dev
sudo apt-get install libboost-all-dev
sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler
sudo apt-get install libqrencode-dev autoconf openssl libssl-dev libevent-dev
sudo apt-get install libminiupnpc-dev
sudo apt-get install cmake

// db4
$ mkdir db4 && cd db4
$ wget http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz
$ tar xzvf db-4.8.30.NC.tar.gz && cd db-4.8.30.NC/build_unix
$ ../dist/configure --enable-cxx --disable-shared --with-pic --prefix=/nodes/dsh_mainnet/dash-0.13.3.0/db4/
$ make install
$ cd ../../../

// bls-signatures
$ wget https://github.com/codablock/bls-signatures/archive/v20181101.tar.gz
$ mv v20181101.tar.gz bls-signatures-v20181101.tar.gz
$ tar xzvf bls-signatures-v20181101.tar.gz
$ cd bls-signatures-20181101
$ cmake .
$ make
$ cd ..

// Depends
$ cd depends
$ make -s -j6
$ cd ..

$ ./autogen.sh
$ ./configure LDFLAGS="-L/nodes/dsh_mainnet/dash-0.13.3.0/db4/lib/ -L/nodes/dsh_mainnet/dash-0.13.3.0/bls-signatures-20181101/ -L/nodes/dsh_mainnet/dash-0.13.3.0/depends/x86_64-pc-linux-gnu/lib/" CPPFLAGS="-I/nodes/dsh_mainnet/dash-0.13.3.0/db4/include/ -I/nodes/dsh_mainnet/dash-0.13.3.0/depends/x86_64-pc-linux-gnu/include/" --with-boost-libdir=/nodes/dsh_mainnet/dash-0.13.3.0/depends/x86_64-pc-linux-gnu/lib/ --without-gui
$ make -s -j6


[dash.conf]
rpcuser=
rpcpassword=
rpcport=29080
#rpcallowip=192.168.0.0/24
rpcallowip=127.0.0.1
#addnode=
server=1
daemon=1
listen=1


// Run node
/nodes/dsh_mainnet# ./dashd -daemon -datadir=/nodes/dsh_mainnet/sync_data

// Client
/nodes/dsh_mainnet# ./dash-cli -datadir=/nodes/dsh_mainnet/sync_data
```



QTUM (QTUM)
----------
    https://github.com/qtumproject/qtum

```sh
path: /nodes/qtum_mainnet/qtum

$ git clone --recursive https://github.com/qtumproject/qtum.git
$ git submodule update --init --recursive

// db4
$ mkdir db4 && cd db4
$ wget http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz
$ tar xzvf db-4.8.30.NC.tar.gz && cd db-4.8.30.NC/build_unix
$ ../dist/configure --enable-cxx --disable-shared --with-pic --prefix=/nodes/qtum_mainnet/qtum/db4/
$ make install


$ ./autogen.sh
$ ./configure LDFLAGS="-L/nodes/qtum_mainnet/qtum/db4/lib/" CPPFLAGS="-I/nodes/qtum_mainnet/qtum/db4/include/"
$ make -s -j6


[qtum.conf]
rpcuser=
rpcpassword=
rpcport=3889
#rpcallowip=192.168.0.0/24
rpcallowip=127.0.0.1
#addnode=
server=1
daemon=1
listen=1


// Run node
/nodes/qtum_mainnet# ./qtumd -daemon -datadir=/nodes/qtum_mainnet/sync_data

// Client
/nodes/qtum_mainnet# ./qtum-cli -datadir=/nodes/qtum_mainnet/sync_data -rpcwallet=<walletname>
```



VERGE (XVG)
----------
    https://github.com/vergecurrency/VERGE

```sh
path: /nodes/xvg_mainnet/VERGE

$ cd /etc/apt/sources.list.d/
$ sudo touch tor.list
$ sudo echo 'deb http://deb.torproject.org/torproject.org xenial main' >> tor.list
$ sudo echo 'deb-src http://deb.torproject.org/torproject.org xenial main' >> tor.list
$ sudo gpg --keyserver keys.gnupg.net --recv 886DDD89
$ sudo gpg --export A3C4F0F979CAA22CDBA8F512EE8CBC9E886DDD89 | apt-key add -
$ sudo apt-get update
$ sudo apt-get install tor deb.torproject.org-keyring

$ sudo apt-get -y install git build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils libboost-all-dev libminiupnpc-dev libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev libseccomp-dev libcap-dev

$ sudo apt-get -y install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils libboost-all-dev libminiupnpc-dev libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev libseccomp-dev libcap-dev


$ git clone --recurse-submodules https://github.com/vergecurrency/VERGE


// db4
$ mkdir db4 && cd db4
$ wget http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz
$ tar xzvf db-4.8.30.NC.tar.gz && cd db-4.8.30.NC/build_unix
$ ../dist/configure --enable-cxx --disable-shared --with-pic --prefix=/nodes/xvg_mainnet/VERGE/db4/
$ make install


$ ./autogen.sh
$ ./configure LDFLAGS="-L/nodes/xvg_mainnet/VERGE/db4/lib/" CPPFLAGS="-I/nodes/xvg_mainnet/VERGE/db4/include/" --with-gui=qt5
$ make -s -j6


[VERGE.conf]
rpcuser=
rpcpassword=
rpcport=20102
#port=21102
daemon=1
algo=groestl


// Run node
/nodes/xvg_mainnet# ./VERGEd -datadir=/nodes/xvg_mainnet/sync_data -tor=127.0.0.1:9050

// Client
// USE bitcoin-cli or web interface
```



Ripple (XRP)
----------
    https://github.com/ripple/rippled

```sh
path: $HOME/rippled-1.4.0

// Dependencies
$ sudo apt-get -y install git pkg-config protobuf-compiler libprotobuf-dev libssl-dev wget

// Ubuntu 16.04 LTS
// GCC 7.4, G++ 7.4
$ sudo apt-get install -y software-properties-common
$ sudo add-apt-repository ppa:ubuntu-toolchain-r/test
$ sudo apt-get update
$ sudo apt-get install gcc-7 g++-7


$ cd $HOME

// CMake
$ wget https://github.com/Kitware/CMake/releases/download/v3.13.3/cmake-3.13.3-Linux-x86_64.sh
$ sudo sh cmake-3.13.3-Linux-x86_64.sh --prefix=/usr/local --exclude-subdir

or

$ wget https://github.com/Kitware/CMake/releases/download/v3.14.4/cmake-3.14.4.tar.gz
$ ./bootstrap
$ make
$ sudo make install


// BOOST 1.71.0
$ wget https://dl.bintray.com/boostorg/release/1.71.0/source/boost_1_71_0.tar.gz
$ tar xvzf boost_1_71_0.tar.gz
$ cd boost_1_71_0
$ ./bootstrap.sh

// replace default by custom compiler (GCC, G++ 7.4)
file: project-config.jam
#using gcc ; 
using gcc : 7.4.0 : g++-7 ;

$ ./b2 -j 4

// ADD to $HOME/.profile
export BOOST_ROOT=$HOME/boost_1_71_0
export BOOST_LIBRARYDIR=$HOME/boost_1_71_0/stage/lib


// Rippled v1.4.0
$ wget https://github.com/ripple/rippled/archive/1.4.0.tar.gz
$ tar xzvf 1.4.0.tar.gz
$ cd rippled-1.4.0
$ mkdir my_build
$ cd my_build
$ cmake -D CMAKE_C_COMPILER=/usr/bin/gcc-7 -D CMAKE_CXX_COMPILER=/usr/bin/g++-7 -DBOOST_DEBUG=ON ..
$ cmake --build .


$ cd $HOME
$ mkdir sync_data_xrp
$ ln -s ./rippled-1.4.0/my_build/rippled .
$ cp ./rippled-1.4.0/cfg/rippled-example.cfg ./sync_data_xrp/rippled.cfg
$ cp ./rippled-1.4.0/cfg/validators-example.txt ./sync_data_xrp/validators.txt


// mainnet
// rippled.cfg: change host, db, log path
// validators.txt: change info

// testnet
// rippled-testnet.cfg: change host, db, log path
// validators.txt: change info

// local test (standalone)
// rippled-test.cfg: change host, db, log path



// Run node (mainnet)
$ ./rippled --conf $HOME/sync_data_xrp/rippled.cfg

// Client
$ ./rippled --conf $HOME/sync_data_xrp/rippled.cfg [command] [option]


// Run node (local test; standalone)
$ ./rippled --conf $HOME/sync_data_xrp/rippled-test.cfg -a -v --start
// like creates block
$ ./rippled --conf $HOME/sync_data_xrp/rippled-test.cfg accept_ledger
```



Dogecoin (DOGE)
----------
    https://github.com/dogecoin/dogecoin

```sh

$ cd $HOME

// Dependency
$ sudo apt-get install build-essential libtool autotools-dev autoconf pkg-config libssl-dev
$ sudo apt-get install libprotobuf-dev protobuf-compiler
$ sudo apt-get install libqrencode-dev openssl libevent-dev
$ sudo apt-get install libminiupnpc-dev


// Berkeley DB 5.1.29
$ wget http://download.oracle.com/berkeley-db/db-5.1.29.NC.tar.gz
$ tar xzvf db-5.1.29.NC.tar.gz
$ cd db-5.1.29.NC/build_unix
$ ../dist/configure prefix=$HOME/db5 --enable-cxx
$ make


Error:
../src/dbinc/atomic.h:179:19: error: definition of ‘int __atomic_compare_exchange(db_atomic_t*, atomic_value_t, atomic_value_t)’ ambiguates built-in declaration ‘bool __atomic_compare_exchange(long unsigned int, volatile void*, void*, void*, int, int)’
  179 | static inline int __atomic_compare_exchange(
      |                   ^~~~~~~~~~~~~~~~~~~~~~~~~
make: *** [Makefile:2283: cxx_db.lo] Error 1


FIX: db-5.1.29.NC/src/dbinc/atomic.h

Line 147: replace

(before)
__atomic_compare_exchange((p), (o), (n))

(after)
__atomic_compare_exchange_new((p), (o), (n))


Line 179: replace

(before)
static inline int __atomic_compare_exchange(

(after)
static inline int __atomic_compare_exchange_new(


$ make
$ make install



// Boost library
$ sudo apt-get install libboost-all-dev

or

build source code

// GCC 7.4, G++ 7.4
$ sudo apt-get install -y software-properties-common
$ sudo add-apt-repository ppa:ubuntu-toolchain-r/test
$ sudo apt-get update
$ sudo apt-get install gcc-7 g++-7

$ cd $HOME

// BOOST 1.71.0
$ wget https://dl.bintray.com/boostorg/release/1.71.0/source/boost_1_71_0.tar.gz
$ tar xvzf boost_1_71_0.tar.gz
$ cd boost_1_71_0
$ ./bootstrap.sh

// replace default by custom compiler (GCC, G++ 7.4)
file: project-config.jam
#using gcc ; 
using gcc : 7.4.0 : g++-7 ;

$ ./b2 -j 4

// ADD to $HOME/.profile
export BOOST_ROOT=$HOME/boost_1_71_0
export BOOST_LIBRARYDIR=$HOME/boost_1_71_0/stage/lib



// Dogecoin build
$ wget https://github.com/dogecoin/dogecoin/archive/refs/tags/v1.14.3.tar.gz
$ cd dogecoin-1.14.3
$ ./autogen.sh

// with boost v1.71.0, Berkeley-DB 5.1.29 NC
$ ./configure LDFLAGS="-L$HOME/db5/lib" CPPFLAGS="-I$HOME/db5/include/ -I$HOME/boost_1_71_0" --with-boost-libdir=$HOME/boost_1_71_0/stage/lib/

$ make -s -j5

or

$ make -s -j<number of jobs>
```


