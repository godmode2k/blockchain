# Truffle


Installation
----------
```sh
truffle
Truffle is a development environment, testing framework, and asset pipeline for Ethereum, aiming to make life as an Ethereum developer easier.

https://github.com/trufflesuite/truffle



----------------------------------------
Installation
----------------------------------------
The Truffle Suite is being sunset.
This repository has been archived by the owner on Feb 27, 2024. It is now read-only.

Last version: v5.11.5
$ npm install -g truffle



----------------------------------------
Initialization
----------------------------------------
$ mkdir <project-name>
$ truffle init --yes
$ npm init

$ npm install truffle-wallet-provider ethereumjs-wallet@0.6.4
$ npm install web3

(Docker container, as root, USE --unsafe-perm=true --allow-root)
$ npm install --unsafe-perm=true --allow-root truffle-wallet-provider ethereumjs-wallet@0.6.4
$ npm install --unsafe-perm=true --allow-root web3


---------------------------------------
Error: truffle-wallet-provider
---------------------------------------
> Something went wrong while attempting to connect to the network at undefined. Check your network configuration.
Error: Web3ProviderEngine does not support synchronous requests.
    at Web3ProviderEngine.send (/eth_erc20/tokens/ABCToken/node_modules/web3-provider-engine/index.js:54:9)
    ...
---------------------------------------
Fix: truffle-wallet-provider
---------------------------------------
file: ./node_modules/truffle-wallet-provider/index.js

add: comment-out and add
before:
    return this.engine.send.apply(this.engine, arguments);
after:
    //return this.engine.send.apply(this.engine, arguments);
    return this.engine.sendAsync.apply(this.engine, arguments);

#sed -i -e 's/
#return\ this.engine.send.apply(this.engine,\ arguments);
#/\/\/&/' ./node_modules/truffle-wallet-provider/index.js
$ sed -i -e 's/return\ this.engine.send.apply(this.engine,\ arguments);/\/\/&/' ./node_modules/truffle-wallet-provider/index.js


add: this.engine.sendAsync.apply(this.engine, arguments);

#sed -i -e '0,/
#return\ this.engine.send.apply(this.engine,\ arguments);
#/!b;//a\
#\ \ this.engine.sendAsync.apply(this.engine,\ arguments);
#' ./node_modules/truffle-wallet-provider/index.js
$ sed -i -e '0,/return\ this.engine.send.apply(this.engine,\ arguments);/!b;//a\\ \ this.engine.sendAsync.apply(this.engine,\ arguments);' ./node_modules/truffle-wallet-provider/index.js


---------------------------------------
Error
---------------------------------------
Served eth_call ...
err="invalid argument 0: json: cannot unmarshal hex number with leading zero digits into Go struct field TransactionArgs.gas of type hexutil.Uint64"
---------------------------------------
Fix:
---------------------------------------
Reference: https://ethereum.stackexchange.com/questions/154082/got-invalid-opcode-when-deploying-a-contract-to-ganache-test-network-from-truf
This is because solidity 0.8.20 introduces the PUSH0(0x5f) opcode which is only supported on ETH mainnet and 
not on any other chains. That's why other chains can't find the PUSH0(0x5f) opcode and throw this error.
Consider using 0.8.19 for other chains.

Reference: https://www.decipherclub.com/push0-opcode/
PUSH0 opcode: A significant update in the latest solidity version 0.8.20

// USE this: for solodity 0.8.19
$ npm install @openzeppelin/contracts@4.9.6

// for solodity > 0.8.19
$ npm install @openzeppelin/contracts

file: truffle-config.js
module.exports = { compilers: { solc: { version: "0.8.19", } }, ...



----------------------------------------
Private-key from keystore file
----------------------------------------
$ cat private-key.js

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

$ npm private-key.js



----------------------------------------
truffle.js
----------------------------------------
$ mv truffle-config.js truffle-config.js.orig

$ cat truffle.js

const { Web3 } = require("web3");
const web3 = new Web3();
const WalletProvider = require("truffle-wallet-provider");
const Wallet = require('ethereumjs-wallet');

const NODE_HOST_MAINNET="http://localhost:8545/";
const NODE_HOST_PRIVATENET="http://localhost:8544/";

// without prefix '0x'
const OWNER_PRIVATE_KEY_MAINNET = "…”;
// without prefix '0x': get a private-key from private-key.js above.
const OWNER_PRIVATE_KEY_PRIVATENET = "…”;

// Private network
const PRIVATENET_PRIVATE_KEY = OWNER_PRIVATE_KEY_PRIVATENET;
var privatenet_privateKey = new Buffer(PRIVATENET_PRIVATE_KEY, "hex");
var privatenet_wallet = Wallet.fromPrivateKey(privatenet_privateKey);
var privatenet_provider = new WalletProvider(privatenet_wallet, NODE_HOST_PRIVATENET);

// Mainnet
const MAINNET_PRIVATE_KEY = OWNER_PRIVATE_KEY_MAINNET;
var mainnet_privateKey = new Buffer(MAINNET_PRIVATE_KEY, "hex");
var mainnet_wallet = Wallet.fromPrivateKey(mainnet_privateKey);
var mainnet_provider = new WalletProvider(mainnet_wallet, NODE_HOST_MAINNET);

module.exports = {
    compilers: {
        solc: {
            version: "0.8.19",    // solc v0.8.19
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
            gas: 4600000,
            // web3 version < v1.0.0; v0.18.3 here
            //gasPrice: web3.toWei("20", "gwei"),
            // web3 version > v1.0.0
            gasPrice: web3.utils.toWei("20", "gwei"),
            network_id: "1111012345",    // Ethereum Chain Id
},
        mainnet: {
            provider: mainnet_provider,
            gas: 4600000,
            gasPrice: web3.utils.toWei("20", "gwei"),
            network_id: "1",
        }
    }
};



----------------------------------------
Create: solidity, deploy file
----------------------------------------
// USE this: for solodity 0.8.19
$ npm install @openzeppelin/contracts@4.9.6

$ cat ./contracts/ABCToken.sol

pragma solidity ^0.8.19;
import "@openzeppelin/contracts/token/ERC20/ERC20.sol";

contract ABCToken is ERC20 {
    string public __name = "ABCToken"; 
    string public __symbol = "ABC1";
    uint public __decimals = 18;
    //uint public INITIAL_SUPPLY = 10000 * (10 ** (uint256)decimals);
    uint public __INITIAL_SUPPLY = 10000 * (10 ** __decimals);

    constructor() ERC20(__name, __symbol) {
        _mint(msg.sender, __INITIAL_SUPPLY);
        emit Transfer(address(0), msg.sender, __INITIAL_SUPPLY);
    }
}


$ cat migrations/2_deploy_ABCToken.js

var ABCToken = artifacts.require("./ABCToken.sol");
module.exports = function(deployer) { deployer.deploy(ABCToken); }



----------------------------------------
Build
----------------------------------------
$ truffle compile



----------------------------------------
Deploy
----------------------------------------
$ truffle deploy --network privatenet



----------------------------------------
Result
----------------------------------------
Compiling your contracts...
===========================
> Compiling ./contracts/ABCToken.sol
> Compiling @openzeppelin/contracts/token/ERC20/ERC20.sol
> Compiling @openzeppelin/contracts/token/ERC20/IERC20.sol
> Compiling @openzeppelin/contracts/token/ERC20/extensions/IERC20Metadata.sol
> Compiling @openzeppelin/contracts/utils/Context.sol
> Compilation warnings encountered:

    Warning: SPDX license identifier not provided in source file. Before publishing, consider adding a comment containing "SPDX-License-Identifier: <SPDX-License>" to each source file. Use "SPDX-License-Identifier: UNLICENSED" for non-open-source code. Please see https://spdx.org for more information.
--> project:/contracts/ABCToken.sol


> Artifacts written to /eth_erc20/tokens/ABCToken/build/contracts
> Compiled successfully using:
   - solc: 0.8.19+commit.7dd6d404.Emscripten.clang

Compiling your contracts...
===========================
> Everything is up to date, there is nothing to compile.


Starting migrations...
======================
> Network name:    'privatenet'
> Network id:      1111012345
> Block gas limit: 133172740 (0x7f00e04)


2_deploy_ABCToken.js
====================

   Deploying 'ABCToken'
   --------------------
   > transaction hash:    0x2bdbbca8314f676d284fc91ff6dad6d2687a7738368ddae14a65a9e217d269ce
   > Blocks: 1            Seconds: 108
   > contract address:    0x294b89a5ac8E24F8870594c88dcf334614b5bF0B
   > block number:        9
   > block timestamp:     1729660121
   > account:             0xF8Dbf2cAF2e112278e7338589aa0eD0bA12f2Acb
   > balance:             18.999583923274321936
   > gas used:            1383888 (0x151dd0)
   > gas price:           20 gwei
   > value sent:          0 ETH
   > total cost:          0.02767776 ETH

   > Saving artifacts
   -------------------------------------
   > Total cost:          0.02767776 ETH

Summary
=======
> Total deployments:   1
> Final cost:          0.02767776 ETH
```