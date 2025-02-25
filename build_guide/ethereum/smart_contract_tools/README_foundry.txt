foundry guide
- hjkim, 2025.02.21



foundry
Foundry is a blazing fast, portable and modular toolkit for Ethereum application development written in Rust.

https://github.com/foundry-rs/foundry
https://getfoundry.sh/
https://book.getfoundry.sh/



----------------------------------------
Installation
----------------------------------------
$ sudo apt-get install git

// Installer
$ curl -L https://foundry.paradigm.xyz | bash
...
Detected your preferred shell is bash and added foundryup to PATH.
Run 'source /root/.bashrc' or start a new terminal session to use foundryup.
Then, simply run 'foundryup' to install Foundry.
$ foundryup

or

// Prebuilt binary
// download: https://github.com/foundry-rs/foundry/releases/tag/stable
//
// x86_64
$ wget https://github.com/foundry-rs/foundry/releases/download/stable/foundry_stable_linux_amd64.tar.gz
// ARM64
$ wget https://github.com/foundry-rs/foundry/releases/download/stable/foundry_stable_linux_arm64.tar.gz 
// Win32
$ wget https://github.com/foundry-rs/foundry/releases/download/stable/foundry_stable_win32_amd64.zip
// Mac OS ARM64
$ wget https://github.com/foundry-rs/foundry/releases/download/stable/foundry_stable_darwin_arm64.tar.gz

or

// Docker
$ docker pull ghcr.io/foundry-rs/foundry:latest



----------------------------------------
Initialization

/lib
/scripts
/test
/src
----------------------------------------
// $ forge install <submodule>
// $ forge soldeer install <dependency>


$ forge init test --no-commit
$ cd test

// SEE: https://www.npmjs.com/package/@openzeppelin/contracts
//$ forge soldeer install @openzeppelin-contracts~5.0.2 --no-commit
//$ forge soldeer install "@openzeppelin-contracts~"
//select 'Using foundry.toml (recommended)'
//
$ forge install OpenZeppelin/openzeppelin-contracts --no-commit
// for PUSH0(0x5f) opcode error:
// USE:
// - OpenZeppelin/openzeppelin-contracts@v4.9.6
// - solc version: "0.8.19"
$ forge install OpenZeppelin/openzeppelin-contracts@v4.9.6 --no-commit
$ forge remappings > remappings.txt

Add: remappings.txt.
@openzeppelin/contracts/=lib/openzeppelin-contracts/contracts/



----------------------------------------
Create: solidity file
----------------------------------------
path: src/ABCToken.sol

// ABCToken.sol ---------- {
$ cat contracts/ABCToken.sol
// ERC-20: v0.8.x
//pragma solidity ^0.8.0;
pragma solidity ^0.8.28;
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



----------------------------------------
Build
----------------------------------------
$ forge build



----------------------------------------
Deploy (build & deploy)
----------------------------------------
$ forge create ./src/ABCToken.sol:ABCToken \
    --rpc-url http://localhost:8545 \
    --private-key "0x2121283ab608aaa1a447c83751533087157208cf1d0a15a9cb0fbecab919c64d"






================================================


$ forge create --use solc:0.8.19 \
    --broadcast \
    ./src/ABCToken.sol:ABCToken \
    --rpc-url http://localhost:8544 \
    --private-key "0x2121283ab608aaa1a447c83751533087157208cf1d0a15a9cb0fbecab919c64d"


[⠃] Compiling...
[⠒] Compiling 1 files with Solc 0.8.28
[⠢] Solc 0.8.28 finished in 88.66ms
Compiler run successful!
...
Deployer: 0xF8Dbf2cAF2e112278e7338589aa0eD0bA12f2Acb
Deployed to: 0x8aAa50DCA676c63aBBb2b25cC007a68CE689C32f
Transaction hash: 0x7801914e539f8352bd808c6a2601d27541e0aaf70e8b8be6b057c44aac6345ba





