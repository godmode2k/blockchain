#!/bin/sh

# EOS mainnet
# - hjkim, 2019.05.13



BIN=/data/data/eosio_mainnet/sync_data/keosd



### MAINNET ###
BASE_DIR="/data/data/eosio_mainnet/sync_data/mainnet"
DATA_DIR="--data-dir $BASE_DIR/keosd"
CONFIG_DIR="--config-dir $BASE_DIR/keosd"
# Doesn't work
WALLET_DIR="--wallet-dir $BASE_DIR/keosd"
#
#NODEOS_URL="-u http://127.0.0.1:8888"
#WALLET_URL="--wallet-url unix:////$BASE_DIR/keosd/keosd.sock"

# Doesn't work
# Change the default wallet-dir path
#$CONFIG_DIR/config.ini
## wallet-dir = "."
#wallet-dir = "/data/data/eosio_mainnet/sync_data/mainnet/keosd"


### MAINNET ###
echo "### MAINNET ###"
echo "$BIN $DATA_DIR $CONFIG_DIR $WALLET_DIR"
$BIN $DATA_DIR $CONFIG_DIR $WALLET_DIR


# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/mainnet/keosd/keosd.sock [Subcommands]
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
