#!/bin/sh

# EOS mainnet genesis (init)
# - hjkim, 2019.05.13



BIN=/data/data/eosio_mainnet/sync_data/nodeos



BASE_DIR="/data/data/eosio_mainnet/sync_data/mainnet"
DATA_DIR="--data-dir $BASE_DIR/nodeos/data"
CONFIG_DIR="--config-dir $BASE_DIR/nodeos/config"

# -e: enable-stale-production = true
#
# for testnset
# -p eosio: producer-name = eosio


### MAINNET ###
echo "### MAINNET ###"
echo "init genesis..."
echo "Press 'Ctrl + C' after loaded..."
#$BIN $DATA_DIR $CONFIG_DIR --genesis-json=genesis.json
$BIN $DATA_DIR $CONFIG_DIR --genesis-json genesis.json

