#!/bin/sh
#
# -----------------------------------------------------------------
# Purpose: Ethereum ERC-1155 Token Auto-creation and deploy
# Author: Ho-Jung Kim (godmode2k@hotmail.com)
# Filename: new_token_erc1155.sh
# Date: Since January 15, 2022
#
#
# License:
#
# *
# * Copyright (C) 2020 Ho-Jung Kim (godmode2k@hotmail.com)
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# *      http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#
# -----------------------------------------------------------------
# Note:
# -----------------------------------------------------------------
# 1. nodejs
#     $ wget https://nodejs.org/dist/v16.13.2/node-v16.13.2-linux-x64.tar.xz
#     $ tar xJvf node-v16.13.2-linux-x64.tar.xz
#     $ export PATH=`pwd`/node-v16.13.2-linux-x64/bin:$PATH
#     $ echo export PATH=`pwd`/node-v16.13.2-linux-x64/bin:$PATH >> $HOME/.profile
#     $ echo export PATH=`pwd`/node-v16.13.2-linux-x64/bin:$PATH >> $HOME/.bashrc
#
# 2. private-key
#    // export private-key from keystore file
#    const Web3 = require("web3");
#    const web3 = new Web3();
#    const WalletProvider = require("truffle-wallet-provider");
#    const Wallet = require('ethereumjs-wallet');
#    //const thirdparty = require('ethereumjs-wallet/thirdparty');
#    //
#    // ethereum keystore file
#    const _input = '{"address": ...,"version":3}';
#    const _password = "<passphrase>";
#    //
#    const mywallet = Wallet.fromV3(_input, _password);
#    const privatekey = mywallet.getPrivateKey();
#    //
#    console.log( "private key = %j", mywallet.getPrivateKey() );
#    console.log( "private key = " + privatekey.toString("hex") );
#
# 3. run
#     $ yes "" | bash new_token_erc1155.sh [Token Name] [Token IDs names: A,B] [Token IDs: 0,1] [Token IDs Total Supply: 10**18,1] [Token IDs URL]
#     e.g., $ yes "" | bash new_token_erc1155.sh ABCToken A,B 0,1 10**18,1 https://127.0.0.1/api/token
#
# -----------------------------------------------------------------
#
# 4. 2024.07.25 updates
#
# USE:
#  - Node.js: Node v20.15.0 (https://nodejs.org/dist/v20.15.0/node-v20.15.0-linux-x64.tar.xz)
#  - Truffle (v5.11.5): $ npm install -g truffle
#  - Ethereum nodes: at least 2 nodes
#    USE old version for PoW
#    PoW: geth-1.11.6 (old: ~ 1.11.6(PoW), 1.12.0(PoS) ~)
#     - https://gethstore.blob.core.windows.net/builds/geth-alltools-linux-amd64-1.11.6-ea9e62ca.tar.gz
#    PoS: geth-1.14.7 (latest)
#     - https://gethstore.blob.core.windows.net/builds/geth-alltools-linux-amd64-1.14.7-aa55f5ea.tar.gz
#
# ---------------------------------------
# Error
# ---------------------------------------
# > Something went wrong while attempting to connect to the network at undefined. Check your network configuration.
# Error: Web3ProviderEngine does not support synchronous requests.
#     at Web3ProviderEngine.send (/eth_erc20/tokens/ABCToken/node_modules/web3-provider-engine/index.js:54:9)
#     ...
# ---------------------------------------
# FIX:
# ---------------------------------------
# file: ./node_modules/truffle-wallet-provider/index.js
#
# add: comment-out and add
#  - before: return this.engine.send.apply(this.engine, arguments);
#  - after: //return this.engine.send.apply(this.engine, arguments);
#           this.engine.sendAsync.apply(this.engine, arguments);
#
# ---------------------------------------
# Error
# ---------------------------------------
# Served eth_sendRawTransaction ...
# err="only replay-protected (EIP-155) transactions allowed over RPC"
# ---------------------------------------
# FIX:
# ---------------------------------------
# $ geth ... --rpc.allow-unprotected-txs
#
# ---------------------------------------
# Error
# ---------------------------------------
# Served eth_call ...
# err="invalid argument 0: json: cannot unmarshal hex number with leading zero digits into Go struct field TransactionArgs.gas of type hexutil.Uint64"
# ---------------------------------------
# FIX:
# ---------------------------------------
# Reference: https://ethereum.stackexchange.com/questions/154082/got-invalid-opcode-when-deploying-a-contract-to-ganache-test-network-from-truf
# This is because solidity 0.8.20 introduces the PUSH0(0x5f) opcode which is only supported on ETH mainnet and 
# not on any other chains. That's why other chains can't find the PUSH0(0x5f) opcode and throw this error.
# Consider using 0.8.19 for other chains.
#
# Reference: https://www.decipherclub.com/push0-opcode/
# PUSH0 opcode: A significant update in the latest solidity version 0.8.20
#
#
# // for solodity 0.8.19
# $ npm install @openzeppelin/contracts@4.9.6
#
# file: truffle-config.js
# module.exports = { compilers: { solc: { version: "0.8.19", } }, ...
#
#
#
# // private-key
# $ cat get_privkey.js
# // $ npm install web3
# // $ npm install truffle-wallet-provider
#
# // export private-key from keystore file
# //const Web3 = require("web3");
# const { Web3 } = require("web3");
# const web3 = new Web3();
# const WalletProvider = require("truffle-wallet-provider");
# const Wallet = require('ethereumjs-wallet');
# //const thirdparty = require('ethereumjs-wallet/thirdparty');
# //
# // ethereum keystore file
# const _input = '{"address": ...,"version":3}';
# const _password = "<passphrase>";
# //
# const mywallet = Wallet.fromV3(_input, _password);
# const privatekey = mywallet.getPrivateKey();
# //
# console.log( "private key = %j", mywallet.getPrivateKey() );
# console.log( "(USE THIS) private key = " + privatekey.toString("hex") ); // USE THIS
#
# $ npm install web3
# $ npm install truffle-wallet-provider
# $ node get_privkey.js
#
#
# // run
# $ yes "" | bash new_token_erc1155.sh [Token Name] [Token IDs names: A,B] [Token IDs: 0,1] [Token IDs Total Supply: 10**18,1] [Token IDs URL] [Network] [Network-Id]
# e.g., $ yes "" | bash new_token_erc1155.sh ABCToken A,B 0,1 10**18,1 https://127.0.0.1/api/token privatenet 11112
# -----------------------------------------------------------------
#



TOKEN_NAME=$1
#TOKEN_SYMBOL=$2
#TOKEN_DECIMALS=$3
TOKEN_IDS_NAMES=$2
TOKEN_IDS=$3
TOKEN_IDS_TOTAL_SUPPLY=$4
TOKEN_IDS_URL=$5
NETWORK=$6
NETWORK_ID=$7


if [ -z $TOKEN_NAME ] || [ -z $TOKEN_IDS_NAMES ] || [ -z $TOKEN_IDS ] || [ -z $TOKEN_IDS_TOTAL_SUPPLY ] || [ -z $TOKEN_IDS_URL ] \
    || [ -z $NETWORK ] || [ -z $NETWORK_ID ]; then
    echo "Usage: $ yes \"\" | bash $0 [Token Name] [Token IDs names: A,B] [Token IDs: 0,1] [Token IDs Total Supply: 10**18,1] [Token IDs URL] [Network] [Network-Id]"
    echo "--------------------------------------------------------------------------"
    echo "NOTE (internal): { \$OWNER_PRIVATE_KEY_*, \$NODE_HOST_*" }
    echo
    echo "Network: { privatenet, mainnet }"
    echo
    echo "e.g.,\n$ yes \"\" | bash $0 ABCToken A,B 0,1 10**18,1 https://127.0.0.1/api/token privatenet 11112"
    echo "--------------------------------------------------------------------------"
    exit
fi
#if [ -z $TOKEN_NAME ] || [ -z $TOKEN_SYMBOL ] || [ -z $TOKEN_DECIMALS ] || [ -z $TOKEN_TOTAL_SUPPLY ]; then
#   echo "Usage: $ yes \"\" | sh $0 [Token Name] [Token Symbol] [Token Decimals] [Token Total Supply]";
#   exit
#fi

echo "TOKEN NAME = $TOKEN_NAME"
#echo "TOKEN SYMBOL = $TOKEN_SYMBOL"
#echo "TOKEN DECIMALS = $TOKEN_DECIMALS"
# Token IDs Names: "A,B"
echo "TOKEN IDs NAMES = $TOKEN_IDS_NAMES"
# Token IDs: "0,1"
echo "TOKEN IDs = $TOKEN_IDS"
# Token IDs Total Supply: "10**18,1"
echo "TOKEN IDs TOTAL SUPPLY = $TOKEN_IDS_TOTAL_SUPPLY"
echo "TOKEN IDs URL = $TOKEN_IDS_URL"






_TOKEN_IDS_NAMES_VARS_ALL=()
_TOKEN_IDS_NAMES_VARS=()
_TOKEN_IDS_VARS=()
_TOKEN_IDS_TOTAL_SUPPLY_VARS=()
_TOKEN_IDS_MINT_VARS=()

for _TOKEN_IDS in $(echo $TOKEN_IDS | tr "," "\n")
do
    #echo $_TOKEN_IDS
    _TOKEN_IDS_VARS+=($_TOKEN_IDS)
done
#echo ${_TOKEN_IDS_VARS[@]}

for _TOKEN_IDS_NAMES in $(echo $TOKEN_IDS_NAMES | tr "," "\n")
do
    #echo $_TOKEN_IDS_NAMES
    _TOKEN_IDS_NAMES_VARS+=($_TOKEN_IDS_NAMES)
done
#echo ${_TOKEN_IDS_NAMES_VARS[@]}

for _TOKEN_IDS_TOTAL_SUPPLY in $(echo $TOKEN_IDS_TOTAL_SUPPLY | tr "," "\n")
do
    #echo $_TOKEN_IDS_TOTAL_SUPPLY
    _TOKEN_IDS_TOTAL_SUPPLY_VARS+=($_TOKEN_IDS_TOTAL_SUPPLY)
done
#echo ${_TOKEN_IDS_TOTAL_SUPPLY_VARS[@]}



for ((i = 0; i < ${#_TOKEN_IDS_VARS[@]}; i++))
do
    #echo $i
    _TOKEN_IDS_NAMES_VARS_ALL+=('uint256 public constant '${_TOKEN_IDS_NAMES_VARS[$i]}' = '${_TOKEN_IDS_VARS[$i]}';\n')
    _TOKEN_IDS_MINT_VARS+=('_mint(msg.sender, '${_TOKEN_IDS_NAMES_VARS[$i]}', '${_TOKEN_IDS_TOTAL_SUPPLY_VARS[$i]}', "");\n')
done
#echo ${_TOKEN_IDS_NAMES_VARS_ALL[@]}
#echo ${_TOKEN_IDS_MINT_VARS[@]}


_TOKEN_IDS_URL_VAR='constructor() public ERC1155("'$TOKEN_IDS_URL'/{id}.json")'



#TOKEN_NAME="TestTestA"
#TOKEN_SYMBOL="TTA"
#TOKEN_DECIMALS="18"
#TOKEN_TOTAL_SUPPLY="1000000"
OWNER_PRIVATE_KEY_MAINNET="2121283ab608aaa1a447c83751533087157208cf1d0a15a9cb0fbecab919c64d"
OWNER_PRIVATE_KEY_PRIVATENET="2121283ab608aaa1a447c83751533087157208cf1d0a15a9cb0fbecab919c64d"
NODE_HOST_MAINNET="http://localhost:8545/"
NODE_HOST_PRIVATENET="http://localhost:8544/"
WORK_DIR="/eth_erc1155"
TOKEN_DIR="tokens/$TOKEN_NAME"


if [ ! -d "$WORK_DIR" ]; then
    echo "$WORK_DIR doesn't existed"
    exit
fi

#if [ ! -d "$WORK_DIR/tokens" ]; then
#   echo "create $WORK_DIR/token"
#   mkdir -p "$WORK_DIR/tokens"
#fi

cd $WORK_DIR
if [ -d "$TOKEN_DIR" ]; then
    echo "existed token"
    exit
fi

#export PATH=/work/node-v10.16.2-linux-x64/bin:$PATH
#export PATH=/work/node-v16.13.2-linux-x6/bin:$PATH

mkdir -p "$TOKEN_DIR" &&
cd "$TOKEN_DIR" &&


# No install 'truffle' always
#npm install --unsafe-perm=true --allow-root -g truffle@4.1.15 &&
#npm install --unsafe-perm=true --allow-root -g truffle &&
#npm install --unsafe-perm=true --allow-root -g truffle@5.3.0 && --save
#
# npm uninstall -g truffle
# npm install -g truffle
#
#
# Error:  *** Deployment Failed ***
# "Migrations" -- Web3ProviderEngine does not support synchronous requests..
#
# USE THIS (2022.02.02 currently) if errors occur like above.
# npm install --unsafe-perm=true --allow-root -g truffle@5.3.0
#
truffle init --yes &&
npm init &&
#npm install zeppelin-solidity &&
#npm install openzeppelin-solidity &&
#
# latest
#npm install @openzeppelin/contracts &&
#
# for solodity 0.8.19
npm install @openzeppelin/contracts@4.9.6 &&
#npm install @openzeppelin/contracts@4.8.0 &&

npm install --unsafe-perm=true --allow-root truffle-wallet-provider ethereumjs-wallet@0.6.4 &&
npm install --unsafe-perm=true --allow-root web3 &&


echo ">>> contracts/$TOKEN_NAME.sol"
cat << EOF >> contracts/$TOKEN_NAME.sol &&
// contracts/GameItems.sol
// SPDX-License-Identifier: MIT
//pragma solidity ^0.6.0;
pragma solidity ^0.8.0;

//import "openzeppelin-solidity/contracts/token/ERC1155/ERC1155.sol";
import "@openzeppelin/contracts/token/ERC1155/ERC1155.sol";
//import "https://github.com/OpenZeppelin/openzeppelin-contracts/blob/v3.2.0/contracts/token/ERC1155/ERC1155.sol";

contract $TOKEN_NAME is ERC1155 {
    //uint256 public constant A = 0;
    //uint256 public constant B = 1;
    $(echo -en ${_TOKEN_IDS_NAMES_VARS_ALL[@]})

    //constructor() public ERC1155("https://localhost/api/token/{id}.json")
    $_TOKEN_IDS_URL_VAR
    {
        //_mint(msg.sender, A, 10**18, ""); // FT
        //_mint(msg.sender, B, 1, ""); // NFT
        $(echo -en ${_TOKEN_IDS_MINT_VARS[@]})
    }
}
EOF

<<COMMENT
/*
// ERC-20: v0.4.x
pragma solidity ^0.4.18;
import "zeppelin-solidity/contracts/token/ERC20/StandardToken.sol";
import "zeppelin-solidity/contracts/ownership/Ownable.sol";

contract $TOKEN_NAME is StandardToken, Ownable {
    string public name = "$TOKEN_NAME"; 
    string public symbol = "$TOKEN_SYMBOL";
    uint public decimals = $TOKEN_DECIMALS;
    //uint public INITIAL_SUPPLY = 1000000 * (10 ** (uint256)decimals);
    uint public INITIAL_SUPPLY = $TOKEN_TOTAL_SUPPLY * (10 ** decimals);

    function $TOKEN_NAME() public {
        totalSupply_ = INITIAL_SUPPLY;
        owner = msg.sender;
        balances[msg.sender] = INITIAL_SUPPLY;
        emit Transfer(address(0), msg.sender, INITIAL_SUPPLY);
    }
}
*/

// ERC-20: v0.8.x
pragma solidity ^0.8.0;
import "@openzeppelin/contracts/token/ERC20/ERC20.sol";

contract ABCToken is ERC20 {
    string public __name = "$TOKEN_NAME"; 
    string public __symbol = "$TOKEN_SYMBOL";
    uint public __decimals = $TOKEN_DECIMALS;
    //uint public INITIAL_SUPPLY = 1000000 * (10 ** (uint256)decimals);
    uint public __INITIAL_SUPPLY = $TOKEN_TOTAL_SUPPLY * (10 ** __decimals);

    constructor() ERC20(__name, __symbol) {
        _mint(msg.sender, __INITIAL_SUPPLY);
        emit Transfer(address(0), msg.sender, __INITIAL_SUPPLY);
    }
}



// Source:
// - https://docs.openzeppelin.com/contracts/3.x/erc1155#constructing_an_erc1155_token_contract
// - https://forum.openzeppelin.com/t/create-an-erc1155/4433
//
// ERC-1155
// contracts/GameItems.sol
// SPDX-License-Identifier: MIT
pragma solidity ^0.6.0;

import "@openzeppelin-solidity/contracts/token/ERC1155/ERC1155.sol";
//import "@openzeppelin/contracts/token/ERC1155/ERC1155.sol";
//import "https://github.com/OpenZeppelin/openzeppelin-contracts/blob/v3.2.0/contracts/token/ERC1155/ERC1155.sol";

contract GameItems is ERC1155 {
    uint256 public constant GOLD = 0;
    uint256 public constant SILVER = 1;
    uint256 public constant THORS_HAMMER = 2;
    uint256 public constant SWORD = 3;
    uint256 public constant SHIELD = 4;

    // The uri can include the string {id} which clients must replace with the actual token ID,
    // in lowercase hexadecimal (with no 0x prefix) and leading zero padded to 64 hex characters.
    // https://abcoathup.github.io/SampleERC1155/api/token/0000000000000000000000000000000000000000000000000000000000000000.json
    constructor() public ERC1155("https://abcoathup.github.io/SampleERC1155/api/token/{id}.json") {
        _mint(msg.sender, GOLD, 10**18, "");
        _mint(msg.sender, SILVER, 10**27, "");
        _mint(msg.sender, THORS_HAMMER, 1, "");
        _mint(msg.sender, SWORD, 10**9, "");
        _mint(msg.sender, SHIELD, 10**9, "");
    }
}
COMMENT


echo ">>> migrations/2_deploy_$TOKEN_NAME.js"
cat << EOF >> migrations/2_deploy_$TOKEN_NAME.js &&
var $TOKEN_NAME = artifacts.require("./$TOKEN_NAME.sol");
module.exports = function(deployer) {
    deployer.deploy($TOKEN_NAME);
};
EOF


echo ">>> truffle.js"
cat << EOF >> truffle.js &&
// $ npm install web3
// $ npm install truffle-wallet-provider

//const Web3 = require("web3");
const { Web3 } = require("web3");
const web3 = new Web3();
const WalletProvider = require("truffle-wallet-provider");
const Wallet = require('ethereumjs-wallet');


/*
// get private-key from keystore file
//const Web3 = require("web3");
const { Web3 } = require("web3");
const web3 = new Web3();
const WalletProvider = require("truffle-wallet-provider");
const Wallet = require('ethereumjs-wallet');
//const thirdparty = require('ethereumjs-wallet/thirdparty');

const _input = '{"address":"","crypto":""...,"version":3}';
const _password = "12345678";

const mywallet = Wallet.fromV3(_input, _password);
const privatekey = mywallet.getPrivateKey();

console.log( "private key = %j", mywallet.getPrivateKey() );
console.log( "private key = " + privatekey.toString("hex") );
*/


// Private network
const PRIVATENET_PRIVATE_KEY = "$OWNER_PRIVATE_KEY_PRIVATENET";
var privatenet_privateKey = new Buffer(PRIVATENET_PRIVATE_KEY, "hex");
var privatenet_wallet = Wallet.fromPrivateKey(privatenet_privateKey);
var privatenet_provider = new WalletProvider(privatenet_wallet, "$NODE_HOST_PRIVATENET");


// Mainnet
const MAINNET_PRIVATE_KEY = "$OWNER_PRIVATE_KEY_MAINNET";
var mainnet_privateKey = new Buffer(MAINNET_PRIVATE_KEY, "hex");
var mainnet_wallet = Wallet.fromPrivateKey(mainnet_privateKey);
var mainnet_provider = new WalletProvider(mainnet_wallet, "$NODE_HOST_MAINNET");



module.exports = {
    compilers: {
        solc: {
        //version: "0.8.2",
        //version: "0.8.20",
        version: "0.8.19",
        }
    },

    networks: {
        development: {
            host: "localhost",
            port: 8545,
            network_id: "*" // Match any network id
        },
        privatenet: {
            provider: privatenet_provider,
            //from: "0x...",
            gas: 4600000,

            // web3 version < v1.0.0; v0.18.3 here
            //gasPrice: web3.toWei("20", "gwei"),

            // web3 version > v1.0.0
            gasPrice: web3.utils.toWei("20", "gwei"),

            //network_id: "*",
            //network_id: "1000998877",
            //network_id: "11112",
            network_id: "$NETWORK_ID",
        },
        mainnet: {
            provider: mainnet_provider,
            gas: 4600000,
            gasPrice: web3.utils.toWei("20", "gwei"),
            network_id: "1",
        }
    }
};
EOF



#
# 2024.07.25 (truffle: v5.11.5)
#
# USE:
#  - Node.js: Node v20.15.0 (https://nodejs.org/dist/v20.15.0/node-v20.15.0-linux-x64.tar.xz)
#  - Truffle (v5.11.5): $ npm install -g truffle
#  - Ethereum nodes: at least 2 nodes
#
#
# ---------------------------------------
# Error
# ---------------------------------------
# > Something went wrong while attempting to connect to the network at undefined. Check your network configuration.
# Error: Web3ProviderEngine does not support synchronous requests.
#     at Web3ProviderEngine.send (/eth_erc20/tokens/ABCToken/node_modules/web3-provider-engine/index.js:54:9)
#     ...
# ---------------------------------------
# FIX:
# ---------------------------------------
# file: ./node_modules/truffle-wallet-provider/index.js
#
# add: comment-out and add
#  - before: return this.engine.send.apply(this.engine, arguments);
#  - after: //return this.engine.send.apply(this.engine, arguments);
#           this.engine.sendAsync.apply(this.engine, arguments);
#
#sed -i -e 's/
#return\ this.engine.send.apply(this.engine,\ arguments);
#/\/\/&/' ./node_modules/truffle-wallet-provider/index.js
sed -i -e 's/return\ this.engine.send.apply(this.engine,\ arguments);/\/\/&/' ./node_modules/truffle-wallet-provider/index.js
#
#
# add: this.engine.sendAsync.apply(this.engine, arguments);
#
#sed -i -e '0,/
#return\ this.engine.send.apply(this.engine,\ arguments);
#/!b;//a\
#\ \ this.engine.sendAsync.apply(this.engine,\ arguments);
#' ./node_modules/truffle-wallet-provider/index.js
sed -i -e '0,/return\ this.engine.send.apply(this.engine,\ arguments);/!b;//a\\ \ this.engine.sendAsync.apply(this.engine,\ arguments);' ./node_modules/truffle-wallet-provider/index.js
#
#
#
# ---------------------------------------
# Error
# ---------------------------------------
# Served eth_sendRawTransaction ...
# err="only replay-protected (EIP-155) transactions allowed over RPC"
# ---------------------------------------
# FIX:
# ---------------------------------------
# $ geth ... --rpc.allow-unprotected-txs
#
#
#
# ---------------------------------------
# Error
# ---------------------------------------
# Served eth_call ...
# err="invalid argument 0: json: cannot unmarshal hex number with leading zero digits into Go struct field TransactionArgs.gas of type hexutil.Uint64"
# ---------------------------------------
# FIX:
# ---------------------------------------
# Reference: https://ethereum.stackexchange.com/questions/154082/got-invalid-opcode-when-deploying-a-contract-to-ganache-test-network-from-truf
# This is because solidity 0.8.20 introduces the PUSH0(0x5f) opcode which is only supported on ETH mainnet and 
# not on any other chains. That's why other chains can't find the PUSH0(0x5f) opcode and throw this error.
# Consider using 0.8.19 for other chains.
#
# Reference: https://www.decipherclub.com/push0-opcode/
# PUSH0 opcode: A significant update in the latest solidity version 0.8.20
#
#
# // for solodity 0.8.19
# $ npm install @openzeppelin/contracts@4.9.6
#
# // for solodity > 0.8.19
# $ npm install @openzeppelin/contracts
#
# file: truffle-config.js
# module.exports = { compilers: { solc: { version: "0.8.19", } }, ...
#



mv truffle-config.js truffle-config.js.orig &&
truffle compile &&
#truffle deploy --network privatenet
truffle deploy --network $NETWORK

echo "finished..."
