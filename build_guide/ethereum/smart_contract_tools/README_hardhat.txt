hardhat guide
- hjkim, 2025.02.21



hardhat
Hardhat is a development environment to compile, deploy, test, and debug your Ethereum software.

https://github.com/NomicFoundation/hardhat
https://hardhat.org/docs



----------------------------------------
Note
----------------------------------------
Hardhat v2.22.18 with Geth (a localhost node for a private network)
SEE [Error & Fix] below.



----------------------------------------
Installation
----------------------------------------
$ npm install hardhat
//$ npm install --save-dev hardhat



----------------------------------------
Initialization
----------------------------------------
$ mkdir <project-name> && cd <project-name>
$ npx hardhat init

Welcome to Hardhat v2.22.18

✔ What do you want to do? · <select TypeScript>
✔ Hardhat project root: · <enter: default: current path>
✔ Do you want to add a .gitignore? (Y/n) · <enter: default: y>
✔ Do you want to install this sample project's dependencies with npm (hardhat @nomicfoundation/hardhat-toolbox)? (Y/n) · <enter: default: y>


// OpenZeppelin
$ npm install @openzeppelin/contracts
//$ npm install --save-dev @openzeppelin/contracts

// for PUSH0(0x5f) opcode error:
// USE:
// - OpenZeppelin/openzeppelin-contracts@v4.9.6
// - solc version: "0.8.19",
// for solodity 0.8.19
// $ npm install @openzeppelin/contracts@4.9.6


// for TypeScript
// hardhat.config.ts ---------- {
// ADD: networks {}
$ cat hardhat.config.ts
import { HardhatUserConfig } from "hardhat/config";
import "@nomicfoundation/hardhat-toolbox";

const config: HardhatUserConfig = {
//  solidity: "0.8.28",

// for PUSH0(0x5f) opcode error:
// USE:
// - OpenZeppelin/openzeppelin-contracts@v4.9.6
// - solc version: "0.8.19"
  solidity: "0.8.19",

  networks: {
    defaultNetwork: {
      url: 'hardhat',
    },
    // HardhatConfig.networks.hardhat can't have a url
    hardhat: {
      url: 'hardhat',
    },
    privatenet: {
      // RPC-JSON
      url: "http://localhost:8544/",
      // Private-key
      accounts: ["0x2121283ab608aaa1a447c83751533087157208cf1d0a15a9cb0fbecab919c64d"],
      // chainId: optional
      chainId: 1111012345
    }
  }
};

export default config;
// hardhat.config.ts ---------- }



// for JavaScript
// hardhat.config.js ---------- {
// ADD: networks {}
$ cat hardhat.config.ts
require("@nomicfoundation/hardhat-toolbox");

/** @type import('hardhat/config').HardhatUserConfig */
module.exports = {
//  solidity: "0.8.28",

// for PUSH0(0x5f) opcode error:
// USE:
// - OpenZeppelin/openzeppelin-contracts@v4.9.6
// - solc version: "0.8.19"
  solidity: "0.8.19",

  networks: {
    privatenet: {
      // RPC-JSON
      url: "http://localhost:8544/",
      // Private-key
      accounts: ["0x2121283ab608aaa1a447c83751533087157208cf1d0a15a9cb0fbecab919c64d"],
      // chainId: optional
      chainId: 1111012345
    }
  }

};
// hardhat.config.js ---------- }



----------------------------------------
Create: solidity file
----------------------------------------
path:
 - contracts/ABCToken.sol
 - ignition/modules/ABCToken.ts


// ABCToken.sol ---------- {
$ cat contracts/ABCToken.sol
// ERC-20: v0.8.x
//pragma solidity ^0.8.0;
import "@openzeppelin/contracts/token/ERC20/ERC20.sol";

contract ABCToken is ERC20 {
    string public __name = "ABCToken"; 
    string public __symbol = "ABC1";
    uint public __decimals = 18;
    //uint public INITIAL_SUPPLY = 1000000 * (10 ** (uint256)decimals);
    uint public __INITIAL_SUPPLY = 10000 * (10 ** __decimals);

    constructor() ERC20(__name, __symbol) {
        _mint(msg.sender, __INITIAL_SUPPLY);
        emit Transfer(address(0), msg.sender, __INITIAL_SUPPLY);
    }
}
// ABCToken.sol ---------- }



// for TypeScript
// ABCToken.ts ---------- {
$ cat ignition/modules/ABCToken.ts
// This setup uses Hardhat Ignition to manage smart contract deployments.
// Learn more about it at https://hardhat.org/ignition

import { buildModule } from "@nomicfoundation/hardhat-ignition/modules";


const TestTokenModule = buildModule("TestTokenModule", (m) => {
  const token = m.contract("ABCToken", [], {});
  return { token };
});

export default TestTokenModule;
// ABCToken.ts ---------- }



// for JavaScript
// ABCToken.js ---------- {
// This setup uses Hardhat Ignition to manage smart contract deployments.
// Learn more about it at https://hardhat.org/ignition

const { buildModule } = require("@nomicfoundation/hardhat-ignition/modules");

module.exports = buildModule("ABCTokenModule", (m) => {
  const token = m.contract("ABCToken", [], {});

  return { token };
});
// ABCToken.js ---------- }



----------------------------------------
Build
----------------------------------------
$ npx hardhat compile



----------------------------------------
Deploy
----------------------------------------
path: ignition/modules


// for TypeScript
$ npx hardhat ignition deploy ./ignition/modules/ABCToken.ts --network privatenet

// for JavaScript
$ npx hardhat ignition deploy ./ignition/modules/ABCToken.js --network privatenet



============================================


$ mkdir test_erc20 && cd test_erc20



$ npx hardhat init

Welcome to Hardhat v2.22.18

✔ What do you want to do? · <select TypeScript>
✔ Hardhat project root: · <enter: default: current path>
✔ Do you want to add a .gitignore? (Y/n) · <enter: default: y>
✔ Do you want to install this sample project's dependencies with npm (hardhat @nomicfoundation/hardhat-toolbox)? (Y/n) · <enter: default: y>



$ cat contracts/ABCToken.sol
// ERC-20: v0.8.x
//pragma solidity ^0.8.0;
import "@openzeppelin/contracts/token/ERC20/ERC20.sol";

contract ABCToken is ERC20 {
    string public __name = "ABCToken"; 
    string public __symbol = "ABC1";
    uint public __decimals = 18;
    //uint public INITIAL_SUPPLY = 1000000 * (10 ** (uint256)decimals);
    uint public __INITIAL_SUPPLY = 10000 * (10 ** __decimals);

    constructor() ERC20(__name, __symbol) {
        _mint(msg.sender, __INITIAL_SUPPLY);
        emit Transfer(address(0), msg.sender, __INITIAL_SUPPLY);
    }
}



$ npx hardhat compile
Warning: SPDX license identifier not provided in source file. Before publishing, consider adding a comment containing "SPDX-License-Identifier: <SPDX-License>" to each source file. Use "SPDX-License-Identifier: UNLICENSED" for non-open-source code. Please see https://spdx.org for more information.
--> contracts/ABCToken.sol


Warning: Source file does not specify required compiler version! Consider adding "pragma solidity ^0.8.28;"
--> contracts/ABCToken.sol


Generating typings for: 9 artifacts in dir: typechain-types for target: ethers-v6
Successfully generated 36 typings!
Compiled 7 Solidity files successfully (evm target: paris).



$ cat ignition/modules/ABCToken.ts
// This setup uses Hardhat Ignition to manage smart contract deployments.
// Learn more about it at https://hardhat.org/ignition

import { buildModule } from "@nomicfoundation/hardhat-ignition/modules";


const ABCTokenModule = buildModule("ABCTokenModule", (m) => {
  const token = m.contract("ABCToken", [], {});
  return { token };
});

export default ABCTokenModule;



$ npx hardhat ignition deploy ./ignition/modules/ABCToken.ts --network privatenet
✔ Confirm deploy to network privatenet (1111012345)? <enter: y, default: n)

Deploying [ ABCTokenModule ]

Batch #1
  Executing ABCTokenModule#ABCToken...

  hardhat-ignition:onchain-interaction-monitor Retrieving transaction for interaction ABCTokenModule#ABCToken/1 from mempool (attempt 1/10) +0ms
  hardhat-ignition:onchain-interaction-monitor Retrieving transaction for interaction ABCTokenModule#ABCToken/1 from mempool (attempt 1/10) +14s
Batch #1
  Executed ABCTokenModule#ABCToken

[ ABCTokenModule ] successfully deployed 🚀

Deployed Addresses

ABCTokenModule#ABCToken - 0x9719E1c46Daa3747E2526d9AF7103394C5c06b87
  hardhat:core:cli Killing Hardhat after successfully running task deploy +0ms



----------------------------------------
Error & Fix
----------------------------------------
Geth Localhost Private Network
Geth version: geth-alltools-linux-amd64-1.11.6-ea9e62ca/geth
Hardhat version: Hardhat v2.22.18

// Hardhat
hardhat:ignition ProviderError: hardhat_setLedgerOutputEnabled - Method not supported
  hardhat:ignition     at HttpProvider.request (/work/ethereum/smartcontract_tools/work_erc/_hardhat/test_erc20/node_modules/hardhat/src/internal/core/providers/http.ts:92:21)
  hardhat:ignition     at LocalAccountsProvider.request (/work/ethereum/smartcontract_tools/work_erc/_hardhat/test_erc20/node_modules/hardhat/src/internal/core/providers/accounts.ts:192:34)
  hardhat:ignition     at async SimpleTaskDefinition.action (/work/ethereum/smartcontract_tools/work_erc/_hardhat/test_erc20/node_modules/@nomicfoundation/hardhat-ignition/src/index.ts:285:11)
  hardhat:ignition     at async Environment._runTaskDefinition (/work/ethereum/smartcontract_tools/work_erc/_hardhat/test_erc20/node_modules/hardhat/src/internal/core/runtime-environment.ts:351:14)
  hardhat:ignition     at async Environment.run (/work/ethereum/smartcontract_tools/work_erc/_hardhat/test_erc20/node_modules/hardhat/src/internal/core/runtime-environment.ts:184:14)
  hardhat:ignition     at async main (/work/ethereum/smartcontract_tools/work_erc/_hardhat/test_erc20/node_modules/hardhat/src/internal/cli/cli.ts:324:7) +0ms
Hardhat Ignition 🚀
...

Deploying [ ABCTokenModule ]

An unexpected error occurred:

ProviderError: missing trie node 39928095541acdb7a426f36b579f49f7d58fc4aaee0450425ff6cb737f6eace0 (path ) <nil>
    at HttpProvider.request (/work/ethereum/smartcontract_tools/work_erc/_hardhat/test_erc20/node_modules/hardhat/src/internal/core/providers/http.ts:107:21)
    at processTicksAndRejections (node:internal/process/task_queues:95:5)
    at async EIP1193JsonRpcClient.getTransactionCount (/work/ethereum/smartcontract_tools/work_erc/_hardhat/test_erc20/node_modules/@nomicfoundation/ignition-core/src/internal/execution/jsonrpc-client.ts:475:22)
    at async getNonceSyncMessages (/work/ethereum/smartcontract_tools/work_erc/_hardhat/test_erc20/node_modules/@nomicfoundation/ignition-core/src/internal/execution/nonce-management/get-nonce-sync-messages.ts:92:11)
    at async ExecutionEngine._syncNonces (/work/ethereum/smartcontract_tools/work_erc/_hardhat/test_erc20/node_modules/@nomicfoundation/ignition-core/src/internal/execution/execution-engine.ts:221:31)
    at async ExecutionEngine.executeModule (/work/ethereum/smartcontract_tools/work_erc/_hardhat/test_erc20/node_modules/@nomicfoundation/ignition-core/src/internal/execution/execution-engine.ts:71:23)
    at async Deployer.deploy (/work/ethereum/smartcontract_tools/work_erc/_hardhat/test_erc20/node_modules/@nomicfoundation/ignition-core/src/internal/deployer.ts:196:25)
    at async SimpleTaskDefinition.action (/work/ethereum/smartcontract_tools/work_erc/_hardhat/test_erc20/node_modules/@nomicfoundation/hardhat-ignition/src/index.ts:314:24)
    at async Environment._runTaskDefinition (/work/ethereum/smartcontract_tools/work_erc/_hardhat/test_erc20/node_modules/hardhat/src/internal/core/runtime-environment.ts:351:14)
    at async Environment.run (/work/ethereum/smartcontract_tools/work_erc/_hardhat/test_erc20/node_modules/hardhat/src/internal/core/runtime-environment.ts:184:14)


// geth log
WARN [02-24|09:21:15.604] Served hardhat_getAutomine               conn=127.0.0.1:51960 reqid=3 duration=2.492341ms err="the method hardhat_getAutomine does not exist/is not available"
WARN [02-24|09:21:15.781] Served eth_getTransactionCount           conn=127.0.0.1:51972 reqid=7 duration=42.805249ms err="missing trie node 39928095541acdb7a426f36b579f49f7d58fc4aaee0450425ff6cb737f6eace0 (path ) <nil>"




ERROR:

1. hardhat:ignition ProviderError: hardhat_setLedgerOutputEnabled - Method not supported
    (https://github.com/NomicFoundation/hardhat)
2. ProviderError: missing trie node ...  (path ) <nil>
    (https://github.com/NomicFoundation/hardhat-ignition)


FIX 1/2:
hardhat:ignition ProviderError: hardhat_setLedgerOutputEnabled - Method not supported

hardhat_setLedgerOutputEnabled is an internal feature of Hardhat and is not intended for other uses.
So, I think if you're running a localhost Geth node for a private network instead of Hardhat's, you'll need to pass that function call.


Fix it as shown below.

Repo: https://github.com/NomicFoundation/hardhat/blob/main/packages/hardhat-ignition/src/index.ts: 285, 338
Local: node_modules/@nomicfoundation/hardhat-ignition/dist/src/index.js: 200, 234

...
try {
...
before:
	await hre.network.provider.send("hardhat_setLedgerOutputEnabled", [false,]);
after:
	if (hre.network.name === "hardhat") { // for Hardhat Network
		await hre.network.provider.send("hardhat_setLedgerOutputEnabled", [false,]);
	}

...

// Exception error here...
const result = await deploy({ ... });

...

try {
...
before:
	await hre.network.provider.send("hardhat_setLedgerOutputEnabled", [true,]);
after:
	if (hre.network.name === "hardhat") { // for Hardhat Network
		await hre.network.provider.send("hardhat_setLedgerOutputEnabled", [true,]);
	}
...


FIX 2/2:
ProviderError: missing trie node ...  (path ) <nil>

In Geth, it returns NULL (or nil) if the transaction count (eth.getTransactionCount(..)) is 0, otherwise, it returns an unsigned integer (value > 0).
You can also view the logs in Geth's log output.

In the Geth console, even if the transaction count is 0, you might encounter an exception error instead of 0, as shown below.

> eth.getTransactionCount(eth.accounts[0], 35)
Error: missing trie node 39928095541acdb7a426f36b579f49f7d58fc4aaee0450425ff6cb737f6eace0 (path ) <nil>
        at web3.js:6365:9(39)
        at send (web3.js:5099:62(29))
        at <eval>:1:24(7)

Hardhat doesn't handle this exceptions.


Fix it as shown below.

Repo: https://github.com/NomicFoundation/hardhat-ignition
Local: node_modules/@nomicfoundation/ignition-core/dist/src/internal/execution/jsonrpc-client.js: 197

async getTransactionCount(address, blockTag) {
...

before:
        const response = await this._provider.request({
            method: "eth_getTransactionCount",
            params: [address, encodedBlockTag],
        });

after:
    try {
        const response = await this._provider.request({
            method: "eth_getTransactionCount",
            params: [address, encodedBlockTag],
        });
    } catch (err) {
        // In Geth (for a private network)
        // Error: missing trie node ...  (path ) <nil>
        // real error or transaction count is 0 (0x0).
        return jsonRpcQuantityToNumber("0x0");
    }


    assertResponseType("eth_getTransactionCount", response, typeof response === "string");
    return jsonRpcQuantityToNumber(response);
}


=== Call Stack (reversed) === {
node_modules/@nomicfoundation/ignition-core/dist/src/deploy.js
async function deploy(...) {
...
    return deployer.deploy(...)
...
}

node_modules/@nomicfoundation/ignition-core/dist/src/internal/deployer.js
async deploy(...) {
...
    deploymentState = await executionEngine.executeModule(...);
...
}

node_modules/@nomicfoundation/ignition-core/dist/src/internal/execution/execution-engine.js
async _syncNonces(...) {
...
    const nonceSyncMessages = await (0, get_nonce_sync_messages_1.getNonceSyncMessages)(...);
...
}

node_modules/@nomicfoundation/ignition-core/dist/src/internal/execution/nonce-management/get-nonc
e-sync-messages.js
async function getNonceSyncMessages(...) {
...
    const safeConfirmationsCount = confirmedBlockNumber !== undefined
    ? await jsonRpcClient.getTransactionCount(sender, confirmedBlockNumber)
    : undefined;
...
}

node_modules/@nomicfoundation/ignition-core/dist/src/internal/execution/jsonrpc-client.js: 197
async getTransactionCount(address, blockTag) {
...
        const response = await this._provider.request({
            method: "eth_getTransactionCount",
            params: [address, encodedBlockTag],
        });
...
}
=== Call Stack (reversed) === }
