#!/bin/sh

# MongoDB for EOS build guide
# - hjkim, 2019.05.13



MONGODB_PATH=/data/data/mongodb-3.6.3
BIN=$MONGODB_PATH/bin/mongod


$BIN -f $MONGODB_PATH/mongod.conf &
