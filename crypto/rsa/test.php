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

	openssl_public_encrypt( $plaintext, $encrypted, $pubkey, OPENSSL_PKCS1_OAEP_PADDING );
	$base64 = base64_encode( $encrypted );
	$hex = bin2hex( $encrypted );

	openssl_private_decrypt( $encrypted, $decrypted, $privkey, OPENSSL_PKCS1_OAEP_PADDING );

	echo "plain/text: <br>" . $plaintext . "<br> <br>";
	echo "encrypted: <br>" . $encrypted . "<br> <br>";
	echo "encrypted (base64): <br>" . $base64 . "<br> <br>";
	echo "encrypted (hex): <br>" . $hex . "<br> <br>";
	echo "decrypted: <br>" . $decrypted . "<br> <br>";
	echo "<br> <br>";


	$encrypted = "";
	$decrypted = "";
	$base64 = "";
	$hex = "";

	$base64 = " base64(encrypted) ";
	$encrypted = base64_decode( $base64, true );
	$hex = bin2hex( $encrypted );

	openssl_private_decrypt( $encrypted, $decrypted, $privkey, OPENSSL_PKCS1_OAEP_PADDING );
	echo "encrypted: <br>" . $encrypted . "<br> <br>";
	echo "encrypted (hex): <br>" . $hex . "<br> <br>";
	echo "decrypted: <br>" . $decrypted . "<br> <br>";
	echo "<br> <br>";
}

?>
