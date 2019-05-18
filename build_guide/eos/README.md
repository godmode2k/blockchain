# EOS Build Guide


Summary
----------
> EOS Build Guide (NOT DONE YET)
> - hjkim, 2019.05.14


Environment
----------
> build all and tested on GNU/Linux

    GNU/Linux: Ubuntu 16.04_x64 LTS


Build
----------
```sh
https://developers.eos.io/eosio-home/docs
https://github.com/EOSIO/eos.git

// EOS seed list
https://eosnodes.privex.io/



// --------------------------------------------------------------
// Defaults
// --------------------------------------------------------------
eosio
 - base path: $HOME/.local/share/eosio/
 - config.ini: $HOME/.local/share/eosio/nodeos/config/config.ini
 - data: $HOME/.local/share/eosio/nodeos/data/

wallet
 - base path: $HOME/eosio-wallet
 - config.ini: $HOME/eosio-wallet/config.ini



// --------------------------------------------------------------
// Branch: master
// --------------------------------------------------------------
$ git clone https://github.com/EOSIO/eos.git
$ cd ./eos
$ git submodule update --init --recursive
$ ./scripts/eosio_build.sh



// --------------------------------------------------------------
// Branch: latest release (v1.7.3)
// --------------------------------------------------------------
$ mkdir ./eos-v1.7.3 && cd ./eos-v1.7.3
$ git clone -b v1.7.3 https://github.com/EOSIO/eos.git .
$ git submodule update --init --recursive
$ ./scripts/eosio_build.sh



// --------------------------------------------------------------
// Genesis info download
// --------------------------------------------------------------
$ wget https://eosnodes.privex.io/static/genesis.json



// --------------------------------------------------------------
// eos/scripts/eosio_build.sh
// --------------------------------------------------------------
// Minimum disk size
#export DISK_MIN=20
export DISK_MIN=0 # fake

// BOOST C++ Library version error
// Version check: https://dl.bintray.com/boostorg/release/
// e.g., v1.67.0
export BOOST_VERSION_MAJOR=1
export BOOST_VERSION_MINOR=67
export BOOST_VERSION_PATCH=0



// --------------------------------------------------------------
// config.ini: $HOME/.local/share/eosio/nodeos/config/config.ini
// --------------------------------------------------------------
# The public endpoint of a peer node to connect to. Use multiple p2p-peer-address options as needed to compose a network. (eosio::net_plugin)
# p2p-peer-address = 
p2p-peer-address = bp.antpool.com:443
p2p-peer-address = fullnode.eoslaomao.com:443
p2p-peer-address = mars.fnp2p.eosbixin.com:443
p2p-peer-address = p2p.eos.bitspace.no:9876
p2p-peer-address = p2p.genereos.io:9876
p2p-peer-address = peer.eosn.io:9876
p2p-peer-address = peer.main.alohaeos.com:9876
p2p-peer-address = peering.mainnet.eoscanada.com:9876 # Montreal, Canada
p2p-peer-address = publicnode.cypherglass.com:9876
```


RUN
----------
> 1. base directory
```sh
// EOS Bin path
/data/data/eos-v1.7.3/build/bin

$ sudo mkdir -p /data/data/eosio_mainnet/sync_data
$ cd /data/data/eosio_mainnet/sync_data

$ ln -s ../eos-v1.7.3/build/bin/nodeos .
$ ln -s ../eos-v1.7.3/build/bin/keosd .
or
$ ln -s ../eos-v1.7.3/build/bin/* .

$ cp -a -r ./base_dir/mainnet .
$ cp -a -r ./base_dir/testnet .
or
$ cp -a -r ./base_dir/* .
```

> 2. MongoDB
```sh
$ sh run_mongodb.sh
```

> 3. nodeos: Node
```sh
// Initialize (once, at first time)
// Note: SKIP when run the TESTNET
$ sh run_mainnet_init_genesis.sh

// Mainnet
$ sh run_mainnet.sh

// Testnet (local, doesn't required init genesis)
$ sh run_testnet.sh

// Recover
run with option: --replay-blockchain --hard-replay-blockchain
```

> 4. keosd: EOS Wallet
```sh
$ sh run_testnet_keosd.sh
```


Testnet (local)
----------
```sh
# Unix Domain Socket
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/testnet/keosd/keosd.sock [Subcommands]
#
# HTTP
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url http://127.0.0.1:8889 [Subcommands]
```

```sh
# Creates wallet
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/testnet/keosd/keosd.sock wallet create --to-console
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url http://127.0.0.1:8889 wallet create --to-console
#
# Use wallet
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/testnet/keosd/keosd.sock wallet open # default
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/testnet/keosd/keosd.sock wallet open -n <wallet name>
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url http://127.0.0.1:8889 wallet open # default
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url http://127.0.0.1:8889 wallet open -n <wallet name>
#
# e.g.,
# -----------------------------------
# Creates wallet
# -----------------------------------
# $ cleos wallet create --to-console    # default
# $ cleos wallet create -n <wallet_name> --to-console
# Creating wallet: default
# Save password to use in the future to unlock this wallet.
# Without password imported keys will not be retrievable.
# "..."
#
# Creating wallet: <wallet_name>
# Save password to use in the future to unlock this wallet.
# Without password imported keys will not be retrievable.
# "..."
#
#
# -----------------------------------
# Wallet list
# -----------------------------------
# $ cleos wallet open    # default
# $ cleos wallet open -n <wallet name>
# Opened: default
# Opened: <wallet name>
#
# $ cleos wallet list
# Wallets:
# [
# "default *",
# "<wallet_name> *"
# ]
#
#
# -----------------------------------
# Lock / Unlock
# -----------------------------------
# $ cleos wallet lock    # default
# $ cleos wallet lock -n <wallet_name>
# Locked: <wallet_name>
#
# $ cleos wallet unlock    # default
# $ cleos wallet unlock -n <wallet_name>
# $ cleos wallet unlock -n <wallet_name> --password <password>
# Unlocked: <wallet_name>
#
#
# -----------------------------------
# Creates key: two pairs of keys for the Owner and Active
# -----------------------------------
# # Owner
# $ cleos create key --to-console
# Prvate key: ...
# Public key: EOS...
#
# # Active
# $ cleos create key --to-console
# Prvate key: ...
# Public key: EOS...
#
#
# -----------------------------------
# Import key: two pairs of keys for the Owner and Active
#  - use generated key (public, private) by 'cleos create key'
# -----------------------------------
# # 'eosio' account (testnet) for creates another accounts
# #  - private key: 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3
# #  - public key: EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
# $ cleos wallet import --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3
# imported private key for: EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
#
# # Owner
# $ cleos wallet import --private-key <private key>    # default
# $ cleos wallet import --private-key <private key> -n <wallet_name>
# imported private key for: EOS...
#
# # Active
# $ cleos wallet import --private-key <private key>    # default
# $ cleos wallet import --private-key <private key> -n <wallet_name>
# imported private key for: EOS...
#
#
# -----------------------------------
# Wallet Key list
# -----------------------------------
# $ cleos wallet keys
# [
# "EOS...",
# "EOS..."
# ]
#
#
# -----------------------------------
# Wallet Key (private, public keys) list
# -----------------------------------
# $ cleos wallet private_keys
# $ cleos wallet private_keys -n <wallet name>
#   [[
#    "EOS...",
#    "..."
#   ],[
#     "EOS...",
#    "..."
#   ]
# ]
#
#
# -----------------------------------
# Creates account
#
# First, Generates two pairs of keys for the Owner and Active, and import private keys to wallet
# - Owner: $ cleos create key -> $ cleos wallet import <private key>
# - Active: $ cleos create key -> $ cleos wallet import <private key>
# -----------------------------------
# $ cleos create account <creator(account)> <new_account> <owner_public_key> <active_public_key>
# $ cleos create account <eosio> <test1...(12 length; [.1-5a-z])> <EOS...> <EOS...>
# executed transaction: ...  ??? bytes  ??? us
# #         eosio <= eosio::newaccount            {"creator":"eosio","name":"test1...","owner":{"threshold":1,"keys":[{"key":"EOS...
# warning: transaction executed locally, but may not be confirmed by the network yet   ]
#
#
# # Mainnet
# $ cleos system newaccount <creator(account)> <aaaabbbbcccc> <EOS...> <EOS...> --stake-net "0.1 EOS" --stake-cpu "0.1 EOS" --buy-ram-kbytes 3
#
#
# $ cleos get accounts <public key>
# $ cleos get account <account>
# $ cleos get account <test1...>
# permissions:
# ...
#
#
# -----------------------------------
# Contract
#  - System (eosio.system)
#  - Contract: https://github.com/EOSIO/eos/tree/master/unittests/contracts/eosio.system
#
# Error:
# eading WASM from ./contracts/eosio.system/eosio.system.wasm...
# Publishing contract...
# Error 3080006: Transaction took too long
# Error Details:
# deadline exceeded
#
# USE '$ nodeos --max-transaction-time=1000 --resync' then retry
# or
# retry with option '-x' for max transaction time
# ./cleos set contract eosio ./contracts/eosio.system/ -x 1000
# -----------------------------------
# $ mkdir contracts && cd contracts && cp -a -r /path/to/eos/build/unittests/contracts/eosio.system .
#
# ./cleos set contract eosio ./contracts/eosio.system/
# Reading WASM from ./contracts/eosio.system/eosio.system.wasm...
# Publishing contract...
# executed transaction: dda74f0a242ea879104fbd2dd100f12521fb5f49046fda1f2a8f8b39bfaeff62  66920 bytes  8464 us
# #         eosio <= eosio::setcode               {"account":"eosio","vmtype":0,"vmversion":0,"code":"0061736d01000000018a033960027f7f0060057f7f7f7f7f...
# #         eosio <= eosio::setabi                {"account":"eosio","abi":"0e656f73696f3a3a6162692f312e30004c086162695f686173680002056f776e6572046e61...
# >> WGM : 1
# warning: transaction executed locally, but may not be confirmed by the network yet         ]
#
#
# -----------------------------------
# Smart contract
# Contract: https://github.com/EOSIO/eos/tree/master/unittests/contracts/eosio.token
#  - Creates Token and Transfer
# -----------------------------------
# $ cleos create account <eosio> <eosio.token> <EOS...> <EOS...>
# $ mkdir contracts && cd contracts && cp -a -r /path/to/eos/build/unittests/contracts/eosio.token .
#
# $ cleos set contract eosio.token ./contracts/eosio.token
# Reading WASM from /path/to/eos/build/unittests/contracts/eosio.token/eosio.token.wasm...
# Publishing contract...
# executed transaction: ...   ??? bytes  ??? us
# #         eosio <= eosio::setcode               {"account":"eosio.token","vmtype":0,"vmversion":0,"code":"...
# #         eosio <= eosio::setabi                {"account":"eosio.token","abi":"...
# warning: transaction executed locally, but may not be confirmed by the network yet         ]
#
# $ cleos push action eosio.token create '[eosio, "10000000000.0000 EOS"]' -p eosio.token
# executed transaction: ...   ??? bytes  ??? us
# #  eosio.token <= eosio.token::create         {"issuer":"eosio","maximum_supply":"10000000000.0000 EOS"}
# warning: transaction executed locally, but may not be confirmed by the network yet         ]
#
# $ cleos push action eosio.token issue '[eosio, "1000000000.0000 EOS", "test_memo"]' -p eosio
# executed transaction: 55b1c549cc695813c2ddceab337de655962b2cc5c09abf9b812c874a6757c5ed  128 bytes  562 us
# #  eosio.token <= eosio.token::issue          {"to":"eosio","quantity":"1000000000.0000 EOS","memo":"test_memo"}
# warning: transaction executed locally, but may not be confirmed by the network yet         ]
#
# $ cleos get currency balance eosio.token eosio EOS
# 1000000000.0000 EOS
#
# $ cleos push action eosio.token transfer '["eosio", "<to_account>", "1.0000 EOS", "test_message"]' -p eosio
# executed transaction: ...   ??? bytes  ??? us
# #  eosio.token <= eosio.token::transfer       {"from":"eosio","to":"<to_account>","quantity":"1.0000 EOS","memo":"test_message"}
# #         eosio <= eosio.token::transfer       {"from":"eosio","to":"<to_account>","quantity":"1.0000 EOS","memo":"test_message"}
# #  <to_account> <= eosio.token::transfer       {"from":"eosio","to":"<to_account>","quantity":"1.0000 EOS","memo":"test_message"}
# warning: transaction executed locally, but may not be confirmed by the network yet         ]
#
# $ cleos get currency balance eosio.token <to_account> EOS
# 1.0000 EOS
#
# $ cleos get currency stats eosio.token EOS
# {
#   "EOS": {
#     "supply": "1000000000.0000 EOS",
#     "max_supply": "10000000000.0000 EOS",
#     "issuer": "eosio"
#   }
# }
#
```
