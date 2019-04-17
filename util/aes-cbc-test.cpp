/*---------------------------------------------------------------------
Project:    OpenSSL AES-(128,256)-CBC encryption/decryption example
Purpose:
Author:     Ho-Jung Kim (godmode2k@hotmail.com)
Date:       September 09, 2018
Filename:   aes-cbc-test.cpp

Last modified: September 09, 2018
License:

*
* Copyright (C) 2018 Ho-Jung Kim (godmode2k@hotmail.com)
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
-----------------------------------------------------------------
NOTE:
-----------------------------------------------------------------
-----------------------------------------------------------------------*/



// OpenSSL: AES-(128,256)-CBC encryption/decryption
//          (libeay32.dll)
#include "openssl/aes.h"
//#include "openssl/hmac.h"


// 128bit or 256bit
#define AES_KEYLENGTH 128 // 128bit
//#define AES_KEYLENGTH 256 // 256bit


// refer: hex_print: https://stackoverflow.com/questions/43192493/aes-256-cbc-encryption-c-using-openssl
static void hex_print(const void* pv, size_t len) {
	const unsigned char * p = (const unsigned char*)pv;
	if (NULL == pv)
		printf("NULL");
	else {
		size_t i = 0;
		for (; i<len;++i)
			printf("%02X ", *p++);
	}
	printf("\n");
}

static unsigned char* __test_aes_cbc_encrypt(const char* key, const char* message, const int message_len, int* out_len_encoded) {
	AES_KEY enc_key;
	
	int len_out_encoded = ((message_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
	int len_out_decoded = message_len + 1;
	*out_len_encoded = (int)(((double)(message_len + AES_BLOCK_SIZE) / (double)AES_BLOCK_SIZE) * (double)AES_BLOCK_SIZE);

	// 256bit
	//int len_out_encoded = ((message_len + (AES_BLOCK_SIZE * 2)) / (AES_BLOCK_SIZE * 2)) * (AES_BLOCK_SIZE * 2);
	//int len_out_decoded = message_len + 1;
	//*out_len_encoded = (int)(((double)(message_len + (AES_BLOCK_SIZE * 2)) / (double)(AES_BLOCK_SIZE * 2)) * (double)(AES_BLOCK_SIZE * 2));

	// 128bit
	unsigned char aes_key[AES_KEYLENGTH/8] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
	// 256bit
	//unsigned char aes_key[AES_KEYLENGTH] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	//                                           0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

	unsigned char iv_encoded[AES_BLOCK_SIZE] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
	// 256bit
	//unsigned char iv_encoded[AES_BLOCK_SIZE * 2] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	//                                           0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
	unsigned char* out_encoded = new unsigned char[len_out_encoded];

	memset( aes_key, 0x00, AES_BLOCK_SIZE );
	memcpy( aes_key, (unsigned char*)key, AES_BLOCK_SIZE );
	// 256bit
	//memset( aes_key, 0x00, AES_BLOCK_SIZE * 2 );
	//memcpy( aes_key, (unsigned char*)key, AES_BLOCK_SIZE * 2 );

	memset( out_encoded, 0x00, len_out_encoded );


	AES_set_encrypt_key( aes_key, AES_KEYLENGTH, &enc_key );
	AES_cbc_encrypt( (unsigned char*)message, out_encoded, len_out_encoded, &enc_key, iv_encoded, AES_ENCRYPT );


	fprintf( stdout, "source:\n");
	fprintf( stdout, "%s\n", message );
	fprintf( stdout, "len = %d\n", message_len );
	hex_print( message, message_len );

	fprintf( stdout, "encrypt:\n");
	fprintf( stdout, "%s\n", out_encoded );
	fprintf( stdout, "len = %d\n", len_out_encoded );
	fprintf( stdout, "out: message len = %d\n", out_len_encoded );
	hex_print( out_encoded, len_out_encoded );

	return out_encoded;
}

static unsigned char* __test_aes_cbc_decrypt(const char* key, const unsigned char* encoded_message, const int encoded_message_len) {
	AES_KEY dec_key;
	
	int len_out_encoded = encoded_message_len;
	int len_out_decoded = (encoded_message_len - AES_BLOCK_SIZE) + 1;
	// 256bit
	//int len_out_decoded = (encoded_message_len - (AES_BLOCK_SIZE * 2)) + 1;

	// 128bit
	unsigned char aes_key[AES_KEYLENGTH/8] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
	// 256bit
	//unsigned char aes_key[AES_KEYLENGTH] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	//                                           0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

	unsigned char iv_decoded[AES_BLOCK_SIZE] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
	// 256bit
	//unsigned char iv_decoded[AES_BLOCK_SIZE * 2] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	//                                           0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
	const unsigned char* out_encoded = encoded_message;
	unsigned char* out_decoded = new unsigned char[len_out_decoded];

	fprintf( stdout, "encoded len = %d\n", encoded_message_len );
	fprintf( stdout, "plain-text len = %d\n", len_out_decoded );

	memset( aes_key, 0x00, AES_BLOCK_SIZE );
	memcpy( aes_key, (unsigned char*)key, AES_BLOCK_SIZE );
	// 256bit
	//memset( aes_key, 0x00, AES_BLOCK_SIZE * 2 );
	//memcpy( aes_key, (unsigned char*)key, AES_BLOCK_SIZE * 2 );

	memset( out_decoded, 0x00, len_out_decoded );
	

	AES_set_decrypt_key( aes_key, AES_KEYLENGTH, &dec_key );
	AES_cbc_encrypt( out_encoded, out_decoded, len_out_decoded, &dec_key, iv_decoded, AES_DECRYPT );


	fprintf( stdout, "decrypt:\n");
	fprintf( stdout, "%s\n", out_decoded );
	fprintf( stdout, "len = %d\n", len_out_decoded );
	hex_print( out_decoded, len_out_decoded );

	return out_decoded;
}

static void __test_aes_cbc(const char* key, const char* message, const int message_len) {
	/*
	// refer:
	 - https://github.com/i03nomura1y/Sample/blob/master/AES/OpenSSLSample.c
	 - https://crypto.stackexchange.com/questions/12621/why-does-openssl-append-extra-bytes-when-encrypting-with-aes-128-ecb
	 - https://users.dcc.uchile.cl/~pcamacho/tutorial/crypto/openssl/openssl_intro.html
	 - https://www.codeproject.com/Articles/1016357/OpenSSL-Tour-for-Win-Developer
	*/

	/*
	// openssl command-line test

	$ echo '1234567890123456' | openssl aes-256-cbc -a -salt
	enter aes-256-cbc encryption password: 1234
	Verifying - enter aes-256-cbc encryption password:
	U2FsdGVkX18G0Vo08m8QE5AyKjqOhPxZYSMhVmJgnX8TIKaFGT8YrhtTFepOgTpj

	$ echo 'U2FsdGVkX18G0Vo08m8QE5AyKjqOhPxZYSMhVmJgnX8TIKaFGT8YrhtTFepOgTpj' | openssl aes-256-cbc -a -d -salt
	$ echo 'U2FsdGVkX18G0Vo08m8QE5AyKjqOhPxZYSMhVmJgnX8TIKaFGT8YrhtTFepOgTpj' | openssl aes-256-cbc -a -d -salt
	enter aes-256-cbc decryption password: 1234
	1234567890123456
	*/


	AES_KEY enc_key, dec_key;
	
	int len_out_encoded = ((message_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
	int len_out_decoded = message_len + 1;

	// 128bit
	unsigned char aes_key[AES_KEYLENGTH/8] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
	// 256bit
	//unsigned char aes_key[AES_KEYLENGTH] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	//                                           0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

	unsigned char iv_encoded[AES_BLOCK_SIZE] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
	unsigned char iv_decoded[AES_BLOCK_SIZE] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
	// 256bit
	//unsigned char iv_encoded[AES_BLOCK_SIZE] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	//                                           0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
	//unsigned char iv_decoded[AES_BLOCK_SIZE] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	//                                           0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

	unsigned char* out_encoded = new unsigned char[len_out_encoded];
	unsigned char* out_decoded = new unsigned char[len_out_decoded];

	memset( aes_key, 0x00, AES_BLOCK_SIZE );
	memcpy( aes_key, (unsigned char*)key, AES_BLOCK_SIZE );
	// 256bit
	//memset( aes_key, 0x00, AES_BLOCK_SIZE * 2 );
	//memcpy( aes_key, (unsigned char*)key, AES_BLOCK_SIZE * 2 );

	fprintf( stdout, "key = %s\n", key );
	fprintf( stdout, "key = %s\n", aes_key );

	memset( out_encoded, 0x00, len_out_encoded );
	memset( out_decoded, 0x00, len_out_decoded );



	AES_set_encrypt_key( aes_key, AES_KEYLENGTH, &enc_key );
	AES_cbc_encrypt( (unsigned char*)message, out_encoded, len_out_encoded, &enc_key, iv_encoded, AES_ENCRYPT );

	AES_set_decrypt_key( aes_key, AES_KEYLENGTH, &dec_key );
	AES_cbc_encrypt( out_encoded, out_decoded, len_out_decoded, &dec_key, iv_decoded, AES_DECRYPT );


	fprintf( stdout, "source:\n");
	fprintf( stdout, "%s\n", message );
	hex_print( message, message_len );

	fprintf( stdout, "encrypt:\n");
	fprintf( stdout, "%s\n", out_encoded );
	hex_print( out_encoded, len_out_encoded );

	fprintf( stdout, "decrypt:\n");
	fprintf( stdout, "%s\n", out_decoded );
	hex_print( out_decoded, len_out_decoded );


	if ( out_encoded ) {
		delete [] out_encoded;
		out_encoded = NULL;
	}

	if ( out_decoded ) {
		delete [] out_decoded;
		out_decoded = NULL;
	}
}

void __test_aes(void) {
	AES_KEY enc_key;
	const char* key = "1234"; // 128bit (16bytes)
	//const char* key = "12345678901234567890123456789012"; // 256bit (32bytes)
	const int key_len = strlen( key );
	// JSON example: https://json.org/example.html
	const char* message = "\n\
{\"widget\": {\n\
    \"debug\": \"on\",\n\
    \"window\": {\n\
        \"title\": \"Sample Konfabulator Widget\",\n\
        \"name\": \"main_window\",\n\
        \"width\": 500,\n\
        \"height\": 500\n\
    },\n\
    \"image\": { \n\
        \"src\": \"Images/Sun.png\",\n\
        \"name\": \"sun1\",\n\
        \"hOffset\": 250,\n\
        \"vOffset\": 250,\n\
        \"alignment\": \"center\"\n\
    },\n\
    \"text\": {\n\
        \"data\": \"Click Here\",\n\
        \"size\": 36,\n\
        \"style\": \"bold\",\n\
        \"name\": \"text1\",\n\
        \"hOffset\": 250,\n\
        \"vOffset\": 100,\n\
        \"alignment\": \"center\",\n\
        \"onMouseUp\": \"sun1.opacity = (sun1.opacity / 100) * 90;\"\n\
    }\n\
}}";

	const int message_len = strlen( message );


	__test_aes_cbc( key, message, message_len );

	fprintf( stdout, "------------------------------------\n" );

	// AES-(128,256)-CBC Encryption
	unsigned char* out_encoded = NULL;
	int out_len_encoded = 0;
	out_encoded = __test_aes_cbc_encrypt( key, message, message_len, &out_len_encoded );
	
	// AES-(128,256)-CBC Decryption
	unsigned char* out_decoded = NULL;
	out_decoded = __test_aes_cbc_decrypt( key, out_encoded, out_len_encoded );


	if ( out_encoded ) {
		delete [] out_encoded;
		out_encoded = NULL;
	}
	if ( out_decoded ) {
		delete [] out_decoded;
		out_decoded = NULL;
	}
}

