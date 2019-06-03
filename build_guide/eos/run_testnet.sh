#!/bin/sh

# EOS testnet
# - hjkim, 2019.05.13



BIN=/data/data/eosio_mainnet/sync_data/nodeos



### TESTNET ###
BASE_DIR="/data/data/eosio_mainnet/sync_data/testnet"
DATA_DIR="--data-dir $BASE_DIR/nodeos/data"
CONFIG_DIR="--config-dir $BASE_DIR/nodeos/config"
#CHAIN_STATE_DB_SIZE="--chain-state-db-size-mb 1024"

# -e: enable-stale-production = true
#
# for testnset
# -p eosio: producer-name = eosio


### TESTNET ###
echo "### TESTNET ###"
echo "$BIN $DATA_DIR $CONFIG_DIR -e -p eosio --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console"
$BIN $DATA_DIR $CONFIG_DIR -e -p eosio --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console

# Recover
#echo "$BIN $DATA_DIR $CONFIG_DIR -e -p eosio --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console --replay-blockchain --hard-replay-blockchain"
#$BIN $DATA_DIR $CONFIG_DIR -e -p eosio --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console --replay-blockchain --hard-replay-blockchain


# Unix Domain Socket
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/testnet/keosd/keosd.sock [Subcommands]
#
# HTTP
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url http://127.0.0.1:8889 [Subcommands]

# Use wallet
# Unix Domain Socket
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/mainnet/keosd/keosd.sock wallet open # default
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/mainnet/keosd/keosd.sock wallet open -n <wallet name>
#
# HTTP
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url http://127.0.0.1:8889 wallet open # default
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url http://127.0.0.1:8889 wallet open -n <wallet name>
