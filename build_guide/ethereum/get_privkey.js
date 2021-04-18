// export private-key from keystore file
const Web3 = require("web3");
const web3 = new Web3();
const WalletProvider = require("truffle-wallet-provider");
const Wallet = require('ethereumjs-wallet');
//const thirdparty = require('ethereumjs-wallet/thirdparty');
//
// ethereum keystore file
const _input = '{"address": ...,"version":3}';
const _password = "<passphrase>";
//
const mywallet = Wallet.fromV3(_input, _password);
const privatekey = mywallet.getPrivateKey();
//
console.log( "private key = %j", mywallet.getPrivateKey() );
console.log( "private key = " + privatekey.toString("hex") );

