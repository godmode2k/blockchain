<?php
//
// EOS Wallet
//
// hjkim, 2018.11.02
//



require_once('./eosio/EasyBitcoin-PHP/easybitcoin.php');
require_once('./conf_eos_rpc.php');



header('Content-Type: application/json');

date_default_timezone_set( 'Asia/Seoul' );
//echo date('Y/m/d/ H:i:s', time()) . "<br>";


// next: true/false (','), start: true/false (first)
function make_json($result, $key, $val, $next, $start) {
	if ( $start == true ) $result .= "{";
	if ( !empty($key) ) {
		$result .= "\"$key\": \"$val\"";
		if ( $next == true ) $result .= ",";
	}


	return $result;
}
function make_json_end($result, $next = false) {
	$result .= "}";
	if ( $next == true ) $result .= ",";

	return $result;
}
function make_json_error($val, $message = "") {
	//make_json( "{\"result\":\"$val\"}" );
	//$result = make_json( "", "result", $val, false, true );
	$result = make_json( "", "result", $val, true, true );
	$result = make_json( $result, "message", $message, false, false );
	$result = make_json_end( $result );
	return $result;
}



// ------------------------------------------------------------------------



$eos_contracts = array(
	// ("contract account", "symbol")
	array("testaaaaaaa1", "EOS")
);



function wallet_unlock($eos) {
	if ( !isset($eos) ) {
		echo "" . make_json_error( "false" );
		exit;
	}


// e.g.,
// wallet unlock
// - NOTE: --data '["default","wallet passphrase"]'
//curl http://127.0.0.1:8889/v1/wallet/unlock \
//  --header 'accept: application/json' \
//  --header 'content-type: application/json' \
////  --header 'content-type: application/json; charset=UTF-8' \
//  -X POST \
//  --data '["default","wallet passphrase"]'
//
// error:
// 1. "Already unlocked"
//{"code":500,"message":"Internal Service Error","error":{"code":3120007,"name":"wallet_unlocked_exception","what":"Already unlocked","details":[{"message":"Wallet is already unlocked: default","file":"wallet_manager.cpp","line_number":186,"method":"unlock"}]}}
//
// 2. "Invalid wallet password"
//{"code":500,"message":"Internal Service Error","error":{"code":3120005,"name":"wallet_invalid_password_exception","what":"Invalid wallet password","details":[{"message":"Invalid password for wallet: \"/data/data/eosio_mainnet/sync_data/testnet/keosd/default.wallet\"","file":"wallet.cpp","line_number":366,"method":"unlock"}]}}{"result": "false","message": ""}
//
// 3. "{}" no results
//{}
// - Always occured: Locked(lock_all) -> Unlock -> (result: "{}")


	$params = "[\"default\"," . "\"" . WPASSPHRASE . "\"]";
	$url = "v1/wallet/unlock";
	$result = $eos->request_wallet( $url, $params, false, false );

	//! Locked(lock_all) -> Unlock -> (result: "{}") -> Unlock again
	// - always occured
	if ( $result == "{}" ) {
		$result = $eos->request_wallet( $url, $params, false, false );
	}
	if ( $result == "{}" ) {
		echo "" . make_json_error( "false", "Error: Unlock" );
		exit;
	}

	if ( !empty($result) ) {
		$result = json_decode( $result );
		//echo ((array)$result)["code"] . "\n";

		$code = ((array)((array)$result)["error"])["code"];
		$code = trim( $code );

		if ( $code == "3120007" ) {
			//echo "Already unlocked\n";
			return;
		}
		else if ( $code == "3120005" ) {
			//echo "Invalid wallet password\n";
			$what = ((array)((array)$result)["error"])["what"] . "\n";
			echo "" . make_json_error( "false", "Error: " . trim($what) );
			exit;
		}
		else {
			$what = ((array)((array)$result)["error"])["what"] . "\n";
			echo "" . make_json_error( "false", "Error: " . trim($what) );
			exit;
		}

		/*
		$what = ((array)((array)$result)["error"])["what"] . "\n";
		if ( $what == "Invalid wallet password" ) {
			echo "" . make_json_error( "false", "Error: " . trim($what) );
			exit;
		}
		else if ( $what == "Already unlocked" ) {
			//echo "" . make_json_error( "false", "Error: " . trim($what) );
			return;
		}
		*/
	}
}

function wallet_lock($eos) {
// e.g.,
// curl http://127.0.0.1:8889/v1/wallet/lock_all
//  --header 'content-type: application/x-www-form-urlencoded; charset=UTF-8'
//  -X POST

	$params = null;
	$url = "v1/wallet/lock_all";
	$result = $eos->request_wallet( $url, $params, false, false );
}

function getnewaddress($eos, $_account) {
	if ( !isset($eos) ) {
		echo "" . make_json_error( "false" );
		exit;
	}

// e.g.,
// ./cleos -u http://127.0.0.1:8888 --wallet-url http://127.0.0.1:8889 create account eosio <account name> <owner public key> <active public key>
// ./cleos -u http://127.0.0.1:8888 --wallet-url http://127.0.0.1:8889 system newaccount <authorized account> <account name> <owner public key> <active public key> --stake-net "0.1 EOS" --stake-cpu "0.1 EOS" --buy-ram-kbytes 3

}

function getbalance($eos, $_account) {
	if ( !isset($eos) ) {
		echo "" . make_json_error( "false" );
		exit;
	}


	wallet_unlock( $eos );

	if ( !isset($_account) || empty($_account) ) {
// e.g.,
/*
// key pairs (private, public)
//curl http://localhost:8889/v1/wallet/list_keys \
//  --header 'accept: application/json' \
//  --header 'content-type: application/json' \
////  --header 'content-type: application/json; charset=UTF-8' \
//  -X POST \
//  --data '{"default":"wallet passphrase"}'
		$params = array(
			'default' => WPASSPHRASE
		);
		$url = "v1/wallet/list_keys";
		$result = $eos->request_wallet( $url, $params, false );
*/

// public keys
//curl http://localhost:8889/v1/wallet/get_public_keys \
//  --header 'accept: application/json' \
//  --header 'content-type: application/json' \
////  --header 'content-type: application/json; charset=UTF-8' \
//  -X POST
		$url = "v1/wallet/get_public_keys";
		$result_public_key = $eos->request_wallet( $url, $params, true, false );
		$result_public_key = json_decode($result_public_key);

		if ( !is_array($result_public_key) || sizeof($result_public_key) <= 0 ) {
			echo "" . make_json_error( "false", "get public keys" );
			exit;
		}


// get account from public key
//curl http://127.0.0.1:8888/v1/history/get_key_accounts
//  --header 'content-type: application/x-www-form-urlencoded; charset=UTF-8'
//  -X POST
//  --data '{"public_key":"EOS..."}'
		$account_list = array();
		$account_count = 0;
		for ($i = 0; $i < sizeof($result_public_key); $i++ ) {
			$params = array(
				'public_key' => $result_public_key[$i]
			);
			$url = "v1/history/get_key_accounts";
			$result = $eos->request_chain( $url, $params, true, false );

			if ( !isset($result) || empty($result) ) continue;

			$decoded = json_decode($result);
			if ( gettype($decoded) != object ) continue;
			
			$decoded = (array)$decoded;

			if ( !isset($decoded["account_names"]) || empty($decoded["account_names"]) ) {
				continue;
			}

			if ( !is_array($decoded["account_names"]) ) continue;

			//$result_json = make_json( $result_json, "", "", false, true );
			//$result_json = make_json( $result_json, "public_key", $result_public_key[$i], true, false );

			//foreach ( $decoded["account_names"] as $key => $val ) {
			//	$result_json = make_json( $result_json, "account", $val, true, false );
			//}
			$result_json = make_json( $result_json, "account", $decoded["account_names"][0], true, false );
			
			$found = false;
			for ( $j = 0; $j < sizeof($account_list); $j++ ) {
				if ( $account_list[$j]["account"] == $decoded["account_names"][0] ) {
					$found = true;
					break;
				}
			}

			if ( $found == true ) {
				array_push( $account_list[$j]["key"], $result_public_key[$i] );
			}
			else {
				$new_account = array(
					"account" => $decoded["account_names"][0],
					"key" => array( $result_public_key[$i] ),
					"balance" => array(),
				);
				array_push( $account_list, $new_account );
			}

			//$result_json = rtrim( $result_json, "," );
			//$result_json = make_json_end( $result_json, true );
		}

		//$result_json = rtrim( $result_json, "," );
		//$result_json = "[" . $result_json . "]";


/*
// expected result:
[
  {
    "account": "testaaaaaaa1",
    "key": [
      "EOS5B4aYA4oqUjdKicTmvget5SQF9sn3t62Hwa2b5reP7qoBR8c9P",
      "EOS6M8QgvoRktBk5vi4z79KFk3TR9zPn7jgLkMuK1JfUajFSECgFz"
    ]
  },
  {
    "account": "testaaaaaaa2",
    "key": [
      "EOS5ns5zqxA747rjjuH2NYUSgSbLSy568k4NqeRZAR159aRBEFzPx",
      "EOS7zdrQZUKrTsUUw8hkC3RrNgpJUjXvCk3e4cze9dSp8cU5RYbQ8"
    ]
  }
]
*/


// e.g.,
// ./cleos -u http://127.0.0.1:8888 --wallet-url http://127.0.0.1:8889 get currency balance <account name> eosio EOS
//
//curl http://127.0.0.1:8888/v1/chain/get_currency_balance \
//  --header 'accept: application/json' \
//  --header 'content-type: application/json' \
////  --header 'content-type: application/json; charset=UTF-8' \
//  -X POST \
//  --data '{"code":"testaaaaaaa1", "account":"eosio", "symbol":"EOS"}'
//
// result:
//["999999999.0000 EOS"]


		{
			global $eos_contracts;

			// balance
			for ( $i = 0; $i < sizeof($eos_contracts); $i++ ) {
				for ( $j = 0; $j < sizeof($account_list); $j++ ) {
					if ( $account_list[$j]["account"] == $eos_contracts[$i][0] ) continue;

					$params = array(
						'code' => $eos_contracts[$i][0],
						'account' => $account_list[$j]["account"],
						'symbol' => $eos_contracts[$i][1]
					);
					$url = "v1/chain/get_currency_balance";
					$result_balance = $eos->request_chain( $url, $params, true, false );
					$result_balance = json_decode($result_balance);

					if ( !is_array($result_balance) || sizeof($result_balance) <= 0 ) {
						echo "" . make_json_error( "false", "get currency balance" );
						exit;
					}

					array_push( $account_list[$i]["balance"], $result_balance[0] );
				}
			}

/*
// expected result:
[
  {
    "account": "testaaaaaaa1",
    "key": [
      "EOS5B4aYA4oqUjdKicTmvget5SQF9sn3t62Hwa2b5reP7qoBR8c9P",
      "EOS6M8QgvoRktBk5vi4z79KFk3TR9zPn7jgLkMuK1JfUajFSECgFz"
    ],
    "balance": [
      "1.0000 EOS"
    ]
  },
  {
    "account": "testaaaaaaa2",
    "key": [
      "EOS5ns5zqxA747rjjuH2NYUSgSbLSy568k4NqeRZAR159aRBEFzPx",
      "EOS7zdrQZUKrTsUUw8hkC3RrNgpJUjXvCk3e4cze9dSp8cU5RYbQ8"
    ],
    "balance": []
  }
]
*/
		}

		$result_json = json_encode( $account_list );
	}
	else {
// e.g.,
//curl http://127.0.0.1:8888/v1/chain/get_account \
//  --header 'accept: application/json' \
//  --header 'content-type: application/json' \
////  --header 'content-type: application/json; charset=UTF-8' \
//  -X POST \
//  --data '{"account_name":"eosio"}'

		//$_account = "testaaaaaaa1";
		$params = array(
			'account_name' => $_account
		);
		$url = "v1/chain/get_account";
		$result_json = $eos->request_chain( $url, $params, true, false );
	}

	return $result_json;

}

function sendfrom($eos, $_from_account, $_to_account, $_amount, $_wallet_passphrase) {
	if ( !isset($eos) ) {
		echo "" . make_json_error( "false" );
		exit;
	}

	if ( !isset($_from_account) || !isset($_to_account)
		|| !isset($_amount) || !isset($_wallet_passphrase)
		|| empty($_from_account) || empty($_to_account)
		|| empty($_amount) || empty($_wallet_passphrase) ) {
		echo "" . make_json_error( "false", "ERROR: input data" );
		exit;
	}

	$datetime_zone = date_default_timezone_get();

}

function gettransactions($eos, $_account) {
	if ( !isset($eos) ) {
		echo "" . make_json_error( "false" );
		exit;
	}

	$datetime_zone = date_default_timezone_get();

}

function gettransactionhash($eos, $txhash) {
	if ( !isset($eos) ) {
		echo "" . make_json_error( "false" );
		exit;
	}

	if ( !isset($txhash) || empty($txhash) || empty($txhash[0]) ) {
		echo "" . make_json_error( "false", "ERROR: input data" );
		exit;
	}


	$datetime_zone = date_default_timezone_get();

}

function getaccounts($eos, $_account) {
	if ( !isset($eos) ) {
		echo "" . make_json_error( "false" );
		exit;
	}

	wallet_unlock( $eos );

	if ( !isset($_account) || empty($_account) ) {
// e.g.,
/*
// key pairs (private, public)
//curl http://localhost:8889/v1/wallet/list_keys \
//  --header 'accept: application/json' \
//  --header 'content-type: application/json' \
////  --header 'content-type: application/json; charset=UTF-8' \
//  -X POST \
//  --data '{"default":"wallet passphrase"}'
		$params = array(
			'default' => WPASSPHRASE
		);
		$url = "v1/wallet/list_keys";
		$result = $eos->request_wallet( $url, $params, false );
*/

// public keys
//curl http://localhost:8889/v1/wallet/get_public_keys \
//  --header 'accept: application/json' \
//  --header 'content-type: application/json' \
////  --header 'content-type: application/json; charset=UTF-8' \
//  -X POST
		$url = "v1/wallet/get_public_keys";
		$params = null;
		$result_public_key = $eos->request_wallet( $url, $params, true, false );
		$result_public_key = json_decode($result_public_key);

		if ( !is_array($result_public_key) || sizeof($result_public_key) <= 0 ) {
			echo "" . make_json_error( "false", "get public keys" );
			exit;
		}


// get account from public key
//curl http://127.0.0.1:8888/v1/history/get_key_accounts
//  --header 'content-type: application/x-www-form-urlencoded; charset=UTF-8'
//  -X POST
//  --data '{"public_key":"EOS..."}'
		$account_list = array();
		$account_count = 0;
		for ($i = 0; $i < sizeof($result_public_key); $i++ ) {
			$params = array(
				'public_key' => $result_public_key[$i]
			);
			$url = "v1/history/get_key_accounts";
			$result = $eos->request_chain( $url, $params, true, false );

			if ( !isset($result) || empty($result) ) continue;

			$decoded = json_decode($result);
			if ( gettype($decoded) != object ) continue;
			
			$decoded = (array)$decoded;

			if ( !isset($decoded["account_names"]) || empty($decoded["account_names"]) ) {
				continue;
			}

			if ( !is_array($decoded["account_names"]) ) continue;

			//$result_json = make_json( $result_json, "", "", false, true );
			//$result_json = make_json( $result_json, "public_key", $result_public_key[$i], true, false );

			//foreach ( $decoded["account_names"] as $key => $val ) {
			//	$result_json = make_json( $result_json, "account", $val, true, false );
			//}
			$result_json = make_json( $result_json, "account", $decoded["account_names"][0], true, false );
			
			$found = false;
			for ( $j = 0; $j < sizeof($account_list); $j++ ) {
				if ( $account_list[$j]["account"] == $decoded["account_names"][0] ) {
					$found = true;
					break;
				}
			}

			if ( $found == true ) {
				array_push( $account_list[$j]["key"], $result_public_key[$i] );
			}
			else {
				$new_account = array(
					"account" => $decoded["account_names"][0],
					"key" => array( $result_public_key[$i] )
				);
				array_push( $account_list, $new_account );
			}

			//$result_json = rtrim( $result_json, "," );
			//$result_json = make_json_end( $result_json, true );
		}

		//$result_json = rtrim( $result_json, "," );
		//$result_json = "[" . $result_json . "]";


/*
// expected result:
[
  {
    "account": "testaaaaaaa1",
    "key": [
      "EOS5B4aYA4oqUjdKicTmvget5SQF9sn3t62Hwa2b5reP7qoBR8c9P",
      "EOS6M8QgvoRktBk5vi4z79KFk3TR9zPn7jgLkMuK1JfUajFSECgFz"
    ]
  },
  {
    "account": "testaaaaaaa2",
    "key": [
      "EOS5ns5zqxA747rjjuH2NYUSgSbLSy568k4NqeRZAR159aRBEFzPx",
      "EOS7zdrQZUKrTsUUw8hkC3RrNgpJUjXvCk3e4cze9dSp8cU5RYbQ8"
    ]
  }
]
*/


		$result_json = json_encode( $account_list );
	}
	else {
// e.g.,
//curl http://127.0.0.1:8888/v1/chain/get_account \
//  --header 'accept: application/json' \
//  --header 'content-type: application/json' \
////  --header 'content-type: application/json; charset=UTF-8' \
//  -X POST \
//  --data '{"account_name":"eosio"}'

		//$_account = "testaaaaaaa1";
		$params = array(
			'account_name' => $_account
		);
		$url = "v1/chain/get_account";
		$result_json = $eos->request_chain( $url, $params, true, false );
	}

	return $result_json;
}

function gettxpool($eos, $_txid) {
	if ( !isset($eos) ) { 
		echo "" . make_json_error( "false" );
		exit;
	}


	$datetime_zone = date_default_timezone_get();

}





// ----------------------------------------------------------------------



$eos = new EOSIO( RPC_USERNAME, RPC_PASSWORD, RPC_HOST, RPC_PORT, RPC_PORT_WALLET );
if ( !isset($eos) ) {
	echo "" . make_json_error( "false" );
	exit;
}


//$_account = "testaaaaaaa1";
$result = getaccounts( $eos, $_account );

//$result = getbalance( $eos, $_account );



echo $result;

