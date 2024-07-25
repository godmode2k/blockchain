
// $ npm install web3
// $ npm install truffle-wallet-provider


// export private-key from keystore file
//const Web3 = require("web3");
const { Web3 } = require("web3");
const web3 = new Web3();
const WalletProvider = require("truffle-wallet-provider");
const Wallet = require('ethereumjs-wallet');
//const thirdparty = require('ethereumjs-wallet/thirdparty');
const fs = require('fs');


// ethereum keystore file
const path = "../sync_data_node1/keystore/UTC--2024-07-23T14-28-23.690821220Z--f8dbf2caf2e112278e7338589aa0ed0ba12f2acb";
const _input = JSON.parse( fs.readFileSync(path) );
const _password = "1234";
//
//const _input = '{"address": ...,"version":3}';
//const _password = "<passphrase>";
//
const mywallet = Wallet.fromV3( _input, _password );
const privatekey = mywallet.getPrivateKey();
//
console.log( "private key = %j", mywallet.getPrivateKey() );
console.log( "(USE THIS) private key = " + privatekey.toString("hex") );

