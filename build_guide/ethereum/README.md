# Ethereum Token create & deploy test

SEE
----------
> ERC-20: erc20_deploy_tutorial.txt and new_token.sh </br>
> ERC-1155: erc20_deploy_tutorial.txt and new_token_erc1155.sh


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
```


Run
----------
```sh
ERC-20
$ yes "" | sh ./new_token.sh [Token Name] [Token Symbol] [Token Decimals] [Token Total Supply]
e.g., yes "" | sh new_token.sh ABCToken ABC 18 10000

ERC-1155
$ yes "" | bash new_token_erc1155.sh [Token Name] [Token IDs names: ] [Token IDs: 0,1] [Token IDs Total Supply: 10**18,1] [Token IDs URL]
e.g., $ yes "" | bash new_token_erc1155.sh ABCToken 0,1 A,B 10**18,1 https://127.0.0.1/api/token
```

