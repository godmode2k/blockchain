<?php
// RSA Encryption/Decryption Test
// hjkim, 2018.12.03
//
// Keys
// $ openssl genrsa -out private.pem 2048
// $ openssl rsa -in private.pem -out public.pem -pubout
// $ openssl rsa -in private.pem -out private_enc.pem -aes256 -passout pass:1234
{
	// Padding
	// OPENSSL_PKCS1_PADDING: PHP default
	// OPENSSL_PKCS1_OAEP_PADDING: USE THIS

	$password = "1234";
	$plaintext = "test 0000 test 1111";
	$pubkey = openssl_pkey_get_public( "file://./keys/public.pem" );
	$privkey = openssl_pkey_get_private( "file://./keys/private_enc.pem", $password );

	$compressed = gzencode( $plaintext );

	openssl_public_encrypt( $compressed, $encrypted, $pubkey, OPENSSL_PKCS1_OAEP_PADDING );
	$base64 = base64_encode( $encrypted );
	$hex = bin2hex( $encrypted );

	echo "plain/text: <br>" . $plaintext . "<br> <br>";
	echo "compressed: <br>" . $compressed . "<br> <br>";
	echo "encrypted (gzip): <br>" . $encrypted . "<br> <br>";
	echo "encrypted (gzip: base64): <br>" . $base64 . "<br> <br>";
	echo "encrypted (gzip: hex): <br>" . $hex . "<br> <br>";

	$encrypted = base64_decode( $base64 );
	openssl_private_decrypt( $encrypted, $decrypted, $privkey, OPENSSL_PKCS1_OAEP_PADDING );
	$decompressed = gzdecode( $decrypted );

	echo "decrypted: <br>" . $decompressed . "<br> <br>";
	echo "<br> <br>";


	$compressed = "";
	$decompressed = "";
	$encrypted = "";
	$decrypted = "";
	$base64 = "";
	$hex = "";

	// 2048 bits, aes-256, compressed(gzip)
	$base64 = "LXzt0IUfS4d86btjwQ94uRxYAS71nDvFogSMpschE/QHtsJUzByP5vSH6BPaBXhLyt3Luv60zEbYZG32U/32FojNvihsMKSympXh9Ca6eiw0nKyIJd6Cy3IcIUpKkc2JpefRuQrqCNmQkfxeqTRCvqljQgmpuBCUeX9z91RU+uJC9bLf/3nN86IicenubD/ke2sQBW33UOKALLnEfaqwupbrgrAewWrvXcrJIB1PbtIYA22XE24WKfUIPO/TtElibEISNITdFf7nwPdtcBI7J9e8QX/QoBDrjmjBNqnMQrvvWIXhgvMt5riZWTG9UrxyTrRRSPBZf6a+PGVzicXnnA==";
	$encrypted = base64_decode( $base64, true );
	$hex = bin2hex( $encrypted );

	openssl_private_decrypt( $encrypted, $decrypted, $privkey, OPENSSL_PKCS1_OAEP_PADDING );
	$decompressed = gzdecode( $decrypted );
	echo "encrypted (gzip): <br>" . $encrypted . "<br> <br>";
	echo "encrypted (gzip: hex): <br>" . $hex . "<br> <br>";
	echo "decrypted (gzip): <br>" . $decrypted . "<br> <br>";
	echo "decompressed: <br>" . $decompressed . "<br> <br>";
	echo "<br> <br>";
}

?>
