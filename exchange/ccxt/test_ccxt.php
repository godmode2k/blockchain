<?php
header('Content-Type: application/json');

date_default_timezone_set( 'Asia/Seoul' );
//echo date('Y/m/d/ H:i:s', time()) . "<br>";



include "ccxt.php";


// print a list of all available exchange classe
//var_dump (\ccxt\Exchange::$exchanges);
echo json_encode(\ccxt\Exchange::$exchanges);


/*
$poloniex = new \ccxt\poloniex ();
$bittrex  = new \ccxt\bittrex  (array ('verbose' => true));
$quoinex  = new \ccxt\quoinex   ();
$zaif     = new \ccxt\zaif     (array (
			'apiKey' => 'YOUR_PUBLIC_API_KEY',
			'secret' => 'YOUR_SECRET_PRIVATE_KEY',
			));
$hitbtc   = new \ccxt\hitbtc   (array (
			'apiKey' => 'YOUR_PUBLIC_API_KEY',
			'secret' => 'YOUR_SECRET_PRIVATE_KEY',
			));

$exchange_id = 'binance';
$exchange_class = "\\ccxt\\$exchange_id";
$exchange = new $exchange_class (array (
			'apiKey' => 'YOUR_API_KEY',
			'secret' => 'YOUR_SECRET',
			'timeout' => 30000,
			'enableRateLimit' => true,
			));
*/


$exchange_id = 'binance';
$exchange_class = "\\ccxt\\$exchange_id";
$exchange = new $exchange_class ();

echo $exchange->fetch_tickers();
echo $exchange->fetch_ticker('BTC/LTC'))

?>
