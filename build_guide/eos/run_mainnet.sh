#!/bin/sh

# EOS mainnet
# - hjkim, 2019.05.13



BIN=/data/data/eosio_mainnet/sync_data/nodeos



### MAINNET ###
BASE_DIR="/data/data/eosio_mainnet/sync_data/mainnet"
DATA_DIR="--data-dir $BASE_DIR/nodeos/data"
CONFIG_DIR="--config-dir $BASE_DIR/nodeos/config"
CHAIN_STATE_DB_SIZE="--chain-state-db-size-mb 204800"

# -e: enable-stale-production = true
#
# for testnset
# -p eosio: producer-name = eosio


### MAINNET ###
echo "### MAINNET ###"
echo "$BIN $DATA_DIR $CONFIG_DIR --genesis-json genesis.json -e --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console $CHAIN_STATE_DB_SIZE"
$BIN $DATA_DIR $CONFIG_DIR --genesis-json genesis.json -e --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console $CHAIN_STATE_DB_SIZE

# Recover
#echo "$BIN $DATA_DIR $CONFIG_DIR -e --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console --replay-blockchain --hard-replay-blockchain"
#$BIN $DATA_DIR $CONFIG_DIR -e --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console --replay-blockchain --hard-replay-blockchain


# Unix Domain Socket
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/mainnet/keosd/keosd.sock [Subcommands]
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
