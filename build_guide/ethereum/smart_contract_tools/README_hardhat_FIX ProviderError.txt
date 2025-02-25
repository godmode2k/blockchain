
Hardhat v2.22.18 + Geth (a localhost node for a private network) Errors.


Errors:
 - hardhat_setLedgerOutputEnabled - Method not supported
 - ProviderError: missing trie node ...  (path ) <nil>


Environment

Geth (a localhost node for a private network)
Geth version: geth-alltools-linux-amd64-1.11.6-ea9e62ca/geth
Hardhat version: Hardhat v2.22.18

Test: Deploy ERC-20 simple token


Error logs

// Hardhat log
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


// Geth log
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

Repo: https://github.com/NomicFoundation/hardhat-ignition/blob/development/packages/core/src/internal/execution/jsonrpc-client.ts: 466
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


now, it works good for me.



