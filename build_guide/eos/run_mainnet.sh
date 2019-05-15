#!/bin/sh

# EOS mainnet
# - hjkim, 2019.05.13



BIN=/data/data/eosio_mainnet/sync_data/nodeos



### MAINNET ###
BASE_DIR="/data/data/eosio_mainnet/sync_data/mainnet"
DATA_DIR="--data-dir $BASE_DIR/nodeos/data"
CONFIG_DIR="--config-dir $BASE_DIR/nodeos/config"

# -e: enable-stale-production = true
#
# for testnset
# -p eosio: producer-name = eosio


### MAINNET ###
echo "### MAINNET ###"
echo "$BIN $DATA_DIR $CONFIG_DIR -e --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console"
$BIN $DATA_DIR $CONFIG_DIR -e --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console

# Recover
#echo "$BIN $DATA_DIR $CONFIG_DIR -e --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console --replay-blockchain --hard-replay-blockchain"
#$BIN $DATA_DIR $CONFIG_DIR -e --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console --replay-blockchain --hard-replay-blockchain


# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/mainnet/keosd/keosd.sock [Subcommands]

# Use wallet
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/mainnet/keosd/keosd.sock wallet open # default
# $ /data/data/eosio_mainnet/sync_data/cleos -u http://127.0.0.1:8888 --wallet-url unix:////data/data/eosio_mainnet/sync_data/mainnet/keosd/keosd.sock wallet open -n <wallet name>
