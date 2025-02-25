# Ethereum Token create & deploy test

SEE
----------
> ERC-20: new_token_erc20.sh (old: erc20_deploy_tutorial.txt) </br>
> ERC-1155: new_token_erc1155.sh (old: erc20_deploy_tutorial.txt)


Ethereum Smart Contract Tools Guide
----------
[Ethereum Smart Contract Tools Guide](smart_contract_tools/README.md)


Environment
----------
> build all and tested on GNU/Linux

    GNU/Linux: Ubuntu 20.04_x64 LTS
    Ethereum: Geth/v1.10.15-stable/linux-amd64/go1.10.15
    Golang: go1.15.5 linux/amd64
    Node.js: node-v16.13.2
    Network: Ethereum Local Private Network


Tools installation
----------
```sh
Golang
$ wget https://dl.google.com/go/go1.15.5.linux-amd64.tar.gz
$ tar xzvf go1.15.5.linux-amd64.tar.gz -C /usr/local/
$ echo "export PATH=$PATH:/usr/local/go/bin" >> $HOME/.profile

Ethereum
$ git clone https://github.com/ethereum/go-ethereum.git -b v1.10.15
$ cd go-ethereum-1.10.15 && make all
$ cd .. && ln -s go-ethereum-1.10.15/build/bin/geth .


-----------------------------
(updated, 2024.07.25)
-----------------------------
USE old version for PoW
PoW: geth-1.11.6 (old: ~ 1.11.6(PoW), 1.12.0(PoS) ~)
 - https://gethstore.blob.core.windows.net/builds/geth-alltools-linux-amd64-1.11.6-ea9e62ca.tar.gz
PoS: geth-1.14.7 (latest)

USE Dockerfile_ethereum
$ sudo docker build -f Dockerfile_ethereum -t ethereum_test:1.0 .
$ sudo docker run --rm -it --name ethereum_test ethereum_test:1.0

$ sudo docker cp get_privkey.js <container_id>:/work
$ sudo docker cp new_token_erc20.sh <container_id>:/work
$ sudo docker cp new_token_erc1155.sh <container_id>:/work

$ sudo docker exec -it <container_id> bash
(container)# cd /work
(container)# npm install web3
(container)# npm install truffle-wallet-provider
(container)# sh run_attach_node1.sh
> miner.start(1)  # stop: miner.stop()
^D
(container)# tail -f nohup.out.node1.2024-xx-xx-xx-xx-xx
...
Generating DAG in progress               epoch=0 percentage=100
Successfully sealed new block            number=1 ...
mined potential block ...
```


Run
----------
```sh
// working directory
 - /eth_erc20
 - /eth_erc1155


// doesn't required if you already installed
// or using docker image from <Dockerfile_ethereum>
$ npm install -g truffle


$ npm install web3
$ npm install truffle-wallet-provider

(EDIT)
$ vim get_privkey.js
const path = "./sync_data_node1/keystore/<keystore filename>";

$ node get_privkey.js
private key = {"type":"Buffer"...
(USE THIS) private key = ...


(EDIT)
$ vim new_token_erc20.sh
OWNER_PRIVATE_KEY_MAINNET=""
OWNER_PRIVATE_KEY_PRIVATENET=""

(EDIT)
$ vim new_token_erc20.sh
OWNER_PRIVATE_KEY_MAINNET=""
OWNER_PRIVATE_KEY_PRIVATENET=""



ERC-20
$ yes "" | sh ./new_token_erc20.sh [Token Name] [Token Symbol] [Token Decimals] [Token Total Supply] [Network] [Network-Id]
e.g.,
$ yes "" | sh new_token_erc20.sh ABCToken ABC 18 10000 privatenet 11112

ERC-1155
$ yes "" | bash new_token_erc1155.sh [Token Name] [Token IDs names: A,B] [Token IDs: 0,1] [Token IDs Total Supply: 10**18,1] [Token IDs URL] [Network] [Network-Id]
e.g.,
$ yes "" | bash new_token_erc1155.sh ABCToken A,B 0,1 10**18,1 https://127.0.0.1/api/token privatenet 11112
```

