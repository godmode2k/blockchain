
# Filecoin Installation guide

----------
```sh
// Filecoin Installation guide
// hjkim (godmode2k@hotmail.com), 2021.03.12



Filecoin lotus
===============


https://docs.filecoin.io/
https://github.com/filecoin-project/lotus



--------------------------------------------
Build: mainnet, calibrationnet

https://docs.filecoin.io/get-started/lotus/installation/
--------------------------------------------
$ sudo apt-get install build-essential pkg-config mesa-opencl-icd ocl-icd-opencl-dev bzr jq hwloc libhwloc-dev curl git


$ wget https://golang.org/dl/go1.16.2.linux-amd64.tar.gz
$ rm -rf /usr/local/go && tar -C /usr/local -xzf go1.16.2.linux-amd64.tar.gz
$ echo 'export PATH=$PATH:/usr/local/go/bin' >> $HOME/.profile
$ source $HOME/.profile



{
$ curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

// If you have an AMD Zen or Intel Ice Lake CPU (or later),
// enable the use of SHA extensions by adding these two environment variables:
$ export RUSTFLAGS="-C target-cpu=native -g"
$ export FFI_BUILD_FROM_SOURCE=1
}

// Some older Intel and AMD processors without the ADX instruction support may panic with
// illegal instruction errors. To fix this, add the CGO_CFLAGS environment variable:
$ export CGO_CFLAGS_ALLOW="-D__BLST_PORTABLE__"
$ export CGO_CFLAGS="-D__BLST_PORTABLE__"


// dev testnet
//$ git clone -b ntwk-nerpa https://github.com/filecoin-project/lotus.git filecoin-ntwk-nerpa
//$ cd filecoin-ntwk-ntwk

// mainnet
$ git clone https://github.com/filecoin-project/lotus.git filecoin-master
$ cd filecoin-master
$ make clean all


// calibration-net
$ git clone https://github.com/filecoin-project/lotus.git filecoin-master
$ cd filecoin-master
$ make calibnet



--------------------------------------------
Build: local-devnet

https://docs.filecoin.io/build/local-devnet/
--------------------------------------------
$ git clone https://github.com/filecoin-project/lotus.git
$ cd filecoin-master


// If you are building Lotus >= 0.7.1 and have an older Intel or AMD processor (MacOS),
// set the following ENV variables before running make 2k:
$ export CGO_CFLAGS_ALLOW="-D__BLST_PORTABLE__"
$ export CGO_CFLAGS="-D__BLST_PORTABLE__"

// Make sure these are always set before running the commands.
$ export LOTUS_PATH=~/.lotusDevnet
$ export LOTUS_MINER_PATH=~/.lotusminerDevnet


// After cloning the Lotus repository
$ make 2k

// Set the LOTUS_SKIP_GENESIS_CHECK environment variable to _yes_.
// This tells your Lotus node that it's okay if the genesis being used doesn't match any baked-in genesis.
$ export LOTUS_SKIP_GENESIS_CHECK=_yes_


// Download the 2048 byte parameters:
$ ./lotus fetch-params 2048


// Pre-seal some sectors:
$ ./lotus-seed pre-seal --sector-size 2KiB --num-sectors 2


// Create the genesis block and start up the first node:
$ ./lotus-seed genesis new localnet.json
$ ./lotus-seed genesis add-miner localnet.json ~/.genesis-sectors/pre-seal-t01000.json
$ ./lotus daemon --lotus-make-genesis=devgen.car --genesis-template=localnet.json --bootstrap=false


// Then, in another console, import the genesis miner key:
// Make sure these are always set before running the commands.
$ export LOTUS_PATH=~/.lotusDevnet
$ export LOTUS_MINER_PATH=~/.lotusminerDevnet
$ ./lotus wallet import --as-default ~/.genesis-sectors/pre-seal-t01000.key


// Set up the genesis miner:
$ ./lotus-miner init --genesis-miner --actor=t01000 --sector-size=2KiB --pre-sealed-sectors=~/.genesis-sectors --pre-sealed-metadata=~/.genesis-sectors/pre-seal-t01000.json --nosync


// Now, finally, start up the miner:
$ ./lotus-miner run --nosync


// after restart
$ export LOTUS_PATH=~/.lotusDevnet
$ export LOTUS_MINER_PATH=~/.lotusminerDevnet
$ export LOTUS_SKIP_GENESIS_CHECK=_yes_
$ ./lotus daemon --lotus-make-genesis=devgen.car --genesis-template=localnet.json --bootstrap=false
$ ./lotus-miner run --nosync




--------------------------------------------
Run: mainnet, calibrationnet

https://docs.filecoin.io/get-started/lotus/chain/
--------------------------------------------
$ ./lotus daemon
//$ ./lotus sync wait


// mainnet: full chain snapshot
$ ./lotus daemon --import-chain https://fil-chain-snapshots-fallback.s3.amazonaws.com/mainnet/complete_chain_with_finality_stateroots_latest.car

// mainnet: Start the daemon using a lightweight snapshot
$ ./lotus daemon --import-snapshot https://fil-chain-snapshots-fallback.s3.amazonaws.com/mainnet/minimal_finality_stateroots_latest.car


// Remove the contents of the datastore/chain/ folder in the Lotus path
//$ rm -rf ~/.lotus/datastore/chain/*



// calibrationnet
$ ./lotus daemon



$ ./lotus sync status


$ ./lotus daemon stop



--------------------------------------------
Test: local-devnet

https://docs.filecoin.io/get-started/lotus/send-and-receive-fil/
https://docs.filecoin.io/store/lotus/store-data/
https://docs.filecoin.io/store/lotus/retrieve-data/
https://docs.filecoin.io/get-started/explore-the-network/#lotus
--------------------------------------------
// Make sure these are always set before running the commands.
$ export LOTUS_PATH=~/.lotusDevnet
$ export LOTUS_MINER_PATH=~/.lotusminerDevnet


// ------------------------------
// wallet: send and receive FIL
// ------------------------------

// Create a BLS wallet
$ ./lotus wallet new bls
t3sm2ujbr5dw6wjff3zz7bplrupon4el35qab2b2iokvn5o5q5co2i2jos3hphdeg3x2qnzikh7qyfczdnww3q


// Create a secp256k1 wallet
$ ./lotus wallet new
t1ce6kwh5rdu3pmvp6rb4z2ge65ryafnl7ciqr5yy


// Create a multisig wallet
$ ./lotus msig create address1 address2..


$ ./lotus wallet list
Address                                                                                 Balance                         Nonce  Default
t1ce6kwh5rdu3pmvp6rb4z2ge65ryafnl7ciqr5yy                                               0 FIL                           0
t3sm2ujbr5dw6wjff3zz7bplrupon4el35qab2b2iokvn5o5q5co2i2jos3hphdeg3x2qnzikh7qyfczdnww3q  0 FIL                           0
t3wqmq6ymuti6vjtd7x5htepaynwokk7plyxfs4m2d2dndqwmnza25o66r5wv6lu73ha5uae3wpbwyjcyxepna  49999999.99991597324575016 FIL  1      X


$ ./lotus wallet default
t3wqmq6ymuti6vjtd7x5htepaynwokk7plyxfs4m2d2dndqwmnza25o66r5wv6lu73ha5uae3wpbwyjcyxepna


$ ./lotus wallet set-default <address>


$ ./lotus wallet balance
49999999.99991597324575016 FIL


// lotus send <target address> <FIL amount>
$ ./lotus send t1ce6kwh5rdu3pmvp6rb4z2ge65ryafnl7ciqr5yy 100
bafy2bzaceaylxzqwszx2jvttlccukc4lrqszm7otgasdsfhfcm7gtasq7wkb2


// lotus send --from=<sender address> <target address> <FIL amount>
$ ./lotus send --from t3wqmq6ymuti6vjtd7x5htepaynwokk7plyxfs4m2d2dndqwmnza25o66r5wv6lu73ha5uae3wpbwyjcyxepna t1ce6kwh5rdu3pmvp6rb4z2ge65ryafnl7ciqr5yy 100
bafy2bzaceaqxoxv6lk7pomin5hpv5nypjrzykrxffh5ul3tlkemahswmy2ly2


$ ./lotus send --gas-premium 50 --gas-feecap 100 --from t3wqmq6ymuti6vjtd7x5htepaynwokk7plyxfs4m2d2dndqwmnza25o66r5wv6lu73ha5uae3wpbwyjcyxepna t1ce6kwh5rdu3pmvp6rb4z2ge65ryafnl7ciqr5yy 100
...

//$ ./lotus send --gas-limit --gas-premium 50 --gas-feecap 100 --from t3wqmq6ymuti6vjtd7x5htepaynwokk7plyxfs4m2d2dndqwmnza25o66r5wv6lu73ha5uae3wpbwyjcyxepna t1ce6kwh5rdu3pmvp6rb4z2ge65ryafnl7ciqr5yy 100
//...



// ------------------------------
// transaction hash
// ------------------------------

// getmessage message_cid <txid, cid>
// lotus chain getmessage <message_cid>
$ ./lotus chain getmessage bafy2bzaceaqxoxv6lk7pomin5hpv5nypjrzykrxffh5ul3tlkemahswmy2ly2
{
  "Version": 0,
  "To": "t1ce6kwh5rdu3pmvp6rb4z2ge65ryafnl7ciqr5yy",
  "From": "t3wqmq6ymuti6vjtd7x5htepaynwokk7plyxfs4m2d2dndqwmnza25o66r5wv6lu73ha5uae3wpbwyjcyxepna",
  "Nonce": 1,
  "Value": "100000000000000000000",
  "GasLimit": 2564897,
  "GasFeeCap": "101233",
  "GasPremium": "100179",
  "Method": 0,
  "Params": null,
  "CID": {
    "/": "bafy2bzaceaqxoxv6lk7pomin5hpv5nypjrzykrxffh5ul3tlkemahswmy2ly2"
  }
}



// ------------------------------
// mpool: Message Pool
// ------------------------------
// pending message
$ ./lotus mpool pending --local
...

$ ./lotus mpool replace --gas-feecap <value> --gas-premium <value>

//$ ./lotus mpool replace --gas-feecap --gas-premium <value> --gas-limit <value>

// automatically reprice the specified message
$ ./lotus mpool replace --auto



// ------------------------------
// Store data
// ------------------------------

// test file
$ head -1000 < /dev/urandom > test1


// Importing data
// lotus client import <./your-example-file.txt>
$ ./lotus client import test1
Import 1, Root bafk2bzaceb2bjilvoxceuoyrjwkc2mwgeb54adpfr2qkrzke63o4votmbcwuu


// You can list the data CIDs of the files you locally imported with
$ ./lotus client local
1: bafk2bzaceb2bjilvoxceuoyrjwkc2mwgeb54adpfr2qkrzke63o4votmbcwuu @/work/test/test1 (import)


// Find a miner
$ ./lotus state list-miners
t01000


// Find the price and conditions
// lotus client query-ask <miner>
$ ./lotus client query-ask t01000
Ask: t01000
Price per GiB: 0.0000000005 FIL
Verified Price per GiB: 0.00000000005 FIL
Max Piece size: 2 KiB
Min Piece size: 256 B


// Make the deal
// lotus client deal
// or
// where the duration is expressed in blocks (1 block is equivalent to 30s).
// lotus client deal <data CID> <miner> <price> <duration>
$ ./lotus client deal bafk2bzaceca3vngp2ob4iqbnnrfqklrqcjgjdbdrar5xhbz33m3n3gm7gub26 t01000 1 1
ERROR: minimum deal duration is 518400 blocks
$ ./lotus client deal bafk2bzaceca3vngp2ob4iqbnnrfqklrqcjgjdbdrar5xhbz33m3n3gm7gub26 t01000 1 518400
bafyreifywdgix45sdomz7yvoxustz2kliki6uewdx55brz56yjusbeup5i


// ------------------------------
// Checking deal status
// ------------------------------
$ ./lotus client list-deals
DealCid      DealId  Provider  State                          On Chain?  Slashed?  PieceCID     Size       Price       Duration  Verified
...usbeup5i  0       t01000    StorageDealCheckForAcceptance  N          N         ...ejpeeqpy  1.984 KiB  520542 FIL  520542    false
  Message: Provider state: StorageDealPublish


$ ./lotus-miner storage-deals list
ProposalCid  DealId  State               Client                                                                                  Size  Price       Duration
...usbeup5i  0       StorageDealPublish  t3wqmq6ymuti6vjtd7x5htepaynwokk7plyxfs4m2d2dndqwmnza25o66r5wv6lu73ha5uae3wpbwyjcyxepna  2KiB  520542 FIL  520542


$ ./lotus-miner storage-deals pending-publish
Publish period:             1h0m0s (ends in 54m18s)
First deal queued at:       2021-03-23 22:57:40.67831887 +0900 KST
Deals will be published at: 2021-03-23 23:57:40.67831887 +0900 KST
1 deals queued to be published:
ProposalCID                                                  Client                                                                                  Size
bafyreifywdgix45sdomz7yvoxustz2kliki6uewdx55brz56yjusbeup5i  t3wqmq6ymuti6vjtd7x5htepaynwokk7plyxfs4m2d2dndqwmnza25o66r5wv6lu73ha5uae3wpbwyjcyxepna  2KiB


$ ./lotus client list-deals
...



// ------------------------------
// Retrieve data
// ------------------------------

// Finding data by CID
// lotus client find <Data CID>
$ ./lotus client find bafk2bzaceca3vngp2ob4iqbnnrfqklrqcjgjdbdrar5xhbz33m3n3gm7gub26


// Making a retrieval deal
// lotus client retrieve --miner <miner ID> <Data CID> <outfile>
$ ./lotus client retrieve --miner t01000 bafk2bzaceca3vngp2ob4iqbnnrfqklrqcjgjdbdrar5xhbz33m3n3gm7gub26 /work/test/test1_copy





--------------------------------------------
Miner

https://docs.filecoin.io/mine/
https://docs.filecoin.io/mine/lotus/miner-setup/
--------------------------------------------







--------------------------------------------
Monitoring

https://docs.filecoin.io/reference/#chain-data-and-monitoring
https://github.com/s0nik42/lotus-farcaster

https://grafana.com/docs/grafana/latest/installation/debian/
https://prometheus.io/download/
--------------------------------------------
// Grafana
$ wget https://dl.grafana.com/oss/release/grafana-7.4.3.linux-amd64.tar.gz
$ tar -zxvf grafana-7.4.3.linux-amd64.tar.gz
$ cd grafana-7.4.3
$ ./bin/grafana-server web



// Prometheus
$ wget https://github.com/prometheus/prometheus/releases/download/v2.25.2/prometheus-2.25.2.linux-amd64.tar.gz
$ tar xzvf prometheus-2.25.2.linux-amd64.tar.gz
$ cd prometheus-2.25.2.linux-amd64

edit prometheus.yml
{
...
scrape_configs:
  # The job name is added as a label `job=<job_name>` to any timeseries scraped from this config.
  - job_name: 'prometheus'

    # Override the global default and scrape targets from this job every 5 seconds.
    scrape_interval: 5s

    static_configs:
      #- targets: ['localhost:9090']
      - targets: ['localhost:9100'] # prometheus-node-exporter IP:PORT (default port: 9100)
}

$ ./prometheus --config.file=prometheus.yml

Check URL: (Web Browser)
 - http://127.0.0.1:9090/metrics
 - http://127.0.0.1:9100/metrics
 - http://127.0.0.1:9090/ -> Status -> Targets (Endpoint: http://127.0.0.1:9100, State: UP)



// lotus-farcaster
{
// mainnet only but you can run on local-devnet
// for local-devnet
$ export LOTUS_PATH=~/.lotusDevnet
$ export LOTUS_MINER_PATH=~/.lotusminerDevnet

// lotus-farcaster only use $HOME/.lotus and $HOME/.lotusminer
$ ln -s $HOME/.lotusDevnet $HOME/.lotus
$ ln -s $HOME/.lotusminerDevnet $HOME/.lotusminer
}

$ sudo apt-get install python3 python3-pip # python v3.8
$ sudo apt-get install cron # for docker container

$ git clone https://github.com/s0nik42/lotus-farcaster.git
$ cd lotus-farcaster/lotus-exporter-farcaster

//$ chmod +x install.sh
//$ ./install.sh LOTUS_USER_USERNAME

$ sh install.sh root
$ sh check.sh root
$ /usr/local/bin/lotus-exporter-farcaster.py

{
// error: check.sh
in docker container, you can remove "sudo" in check.sh, run again.


// error: /usr/local/bin/lotus-exporter-farcaster.py
// File "/usr/local/bin/lotus-exporter-farcaster.py", line 463, in main
//  creation_date = detail["result"]["Log"][0]["Timestamp"]
// IndexError: list index out of range

<LINE 463>: comment-out and replace with ""
#creation_date = detail["result"]["Log"][0]["Timestamp"]
creation_date = ""
...
<LINE 472>: comment-out and replace with ...
'''
if detail["result"]["Log"][0]["Kind"] == "event;sealing.SectorStartCC":
    pledged = 1
else:
    pledged = 0
'''
pledged = 0


$ sh install.sh root
$ sh check.sh root
$ /usr/local/bin/lotus-exporter-farcaster.py
}

Check:
 - prometheus-node-exporter: /var/lib/prometheus/node-exporter/farcaster.prom

$ prometheus-node-exporter
$ service cron restart # for docker container





// Grafna: (Web Browser: http://127.0.0.1:3000)
1. login: admin / admin
2. change new password
3. Configuration -> Data Sources -> Add data source -> select "Prometheus"
4. Data Sources / Prometheus Settings
 - URL: http://127.0.0.1:9090
 - Save & Test -> result: "Data source is working"
5. Dashboard -> Manage
 - Import -> Upload .json file -> lotus-farcaster/grafana-dashboard/LOTUS farcaster-1606820741899.json -> Load
 - Data source: select "Prometheus (default)"
6. Dashboard -> Manage -> select "LOTUS farcaster"








__EOF__ 
```