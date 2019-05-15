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
```

> 4. keosd: EOS Wallet
```sh
$ sh run_testnet_keosd.sh
```


Testnet (local)
----------
```sh
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/mainnet/keosd/keosd.sock [Subcommands]
```

```sh
# Creates wallet
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/mainnet/keosd/keosd.sock wallet create --to-console
# Use wallet
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/mainnet/keosd/keosd.sock wallet open # default
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/mainnet/keosd/keosd.sock wallet open -n <wallet name>
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
# Smart contract
# Contract: https://github.com/EOSIO/eos/tree/master/unittests/contracts/eosio.token
# -----------------------------------
# $ cleos create account <eosio> <eosio.token> <EOS...> <EOS...>
# $ mkdir contracts
# $ cleos set contract eosio.token ./contracts/eosio.token
# $ cleos push action eosio.token create '[eosio, "10000000000.0000 EOS"]' -p eosio.token
# $ cleos push action eosio.token issue '[eosio, "1000000000.0000 EOS"]' -p eosio
# $ cleos push action eosio.token transfer '["eosio", "to_account", "1.0000 EOS", "test_message"]' -p eosio
# $ cleos get currency balance eosio.token eosio EOS
```
