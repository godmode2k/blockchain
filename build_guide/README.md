# Blockchain Node build guide


Summary
----------
> Build a BTC/ETH/DSH/QTUM/XVG/...
> - hjkim, 2018.11.13


Environment
----------
> build all and tested on GNU/Linux

    GNU/Linux: Ubuntu 16.04_x64 LTS


Ethereum (ETH)
----------
    https://github.com/ethereum/
    https://github.com/ethereum/go-ethereum/releases

```sh
path: /nodes/eth_mainnet/

$ wget https://dl.google.com/go/go1.10.3.linux-amd64.tar.gz
$ tar xzvf go1.10.3.linux-amd64.tar.gz -C /usr/local/
$ echo "export PATH=$PATH:/usr/local/go/bin" >> $HOME/.profile

// Unstable version
//$ git clone https://github.com/ethereum/go-ethereum.git

// Release version
$ wget https://github.com/ethereum/go-ethereum/archive/v1.8.21.tar.gz
$ tar xzvf v1.8.21.tar.gz

$ cmake all


// Run node
/nodes/eth_mainnet# nohup ./geth --rpc --rpcport 8080 --rpccorsdomain "*" --datadir /nodes/eth_mainnet/sync_data --port 30304 --rpcapi "db,eth,net,web3,personal,txpool" --syncmode "fast" --cache 4096 &

// Client
/nodes/eth_mainnet# ./geth attach http://localhost:8080
```



Bitcoin (BTC)
----------
    https://github.com/bitcoin/bitcoin

    download: released bitcoin-0.16.0{3}

```sh
path: /nodes/btc_mainnet/bitcoin-0.16.0{3}

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
/nodes/btc_mainnet# ./bitcoin-cli -datadir=/nodes/btc_mainnet/sync_data
```



DASH (DSH)
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
/nodes/qtum_mainnet# ./qtum-cli -datadir=/nodes/qtum_mainnet/sync_data
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
