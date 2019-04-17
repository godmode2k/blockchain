// Crypto++ AES-256-CBC test
// hjkim, 2019.04.17
//
//
// SEE: also PHP version
// - base64_encode(openssl_encrypt("plain-text", "aes-256-cbc", "key: 32bytes", true, str_repeat(chr(0), 16)));
// - openssl_decrypt(base64_decode("base64(encrypted)"), "aes-256-cbc", "key: 32bytes", true, str_repeat(chr(0), 16));
// 



// Source-based: https://stackoverflow.com/questions/12306956/example-of-aes-using-crypto
//
// $ sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils



#include <iostream>
#include <iomanip>

#include "modes.h"
#include "aes.h"
#include "filters.h"

// base64
#include "base64.h"



int main(int argc, char* argv[]) {

	//Key and IV setup
	//AES encryption uses a secret key of a variable length (128-bit, 196-bit or 256-   
	//bit). This key is secretly exchanged between two parties before communication   
	//begins. DEFAULT_KEYLENGTH= 16 bytes
	CryptoPP::byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE ];
	memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
	memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

	// -----
	//! 256bits (32bytes key(password))
	//CryptoPP::byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH * 2 ], iv[ CryptoPP::AES::BLOCKSIZE * 2 ];
	//char* password = "12345678901234567890123456789012"; // 256bits (32bytes)
	//memcpy( key, (unsigned char*)password, CryptoPP::AES::DEFAULT_KEYLENGTH * 2 );
	//memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE * 2 );
	// -----


	//
	// String and Sink setup
	//
	std::string plaintext = "Now is the time for all good men to come to the aide...";
	std::string ciphertext;
	std::string decryptedtext;

	//
	// Dump Plain Text
	//
	std::cout << "Plain Text (" << plaintext.size() << " bytes)" << std::endl;
	std::cout << plaintext;
	std::cout << std::endl << std::endl;

	//
	// Create Cipher Text
	//
	CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);

	// -----
	//! 256bits (32bytes key(password))
	//CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH * 2);
	// -----

	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( ciphertext ) );
	stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() );
	stfEncryptor.MessageEnd();

	//
	// Dump Cipher Text
	//
	std::cout << "Cipher Text (" << ciphertext.size() << " bytes)" << std::endl;

	for( int i = 0; i < ciphertext.size(); i++ ) {
		std::cout << "0x" << std::hex << (0xFF & static_cast<CryptoPP::byte>(ciphertext[i])) << " ";
	}
	std::cout << std::endl << std::endl;




	// -----
	//! 256bits (32bytes key(password))
	// base64 test
	std::string base64;
	StringSource(ciphertext, true,
		new Base64Encoder(new StringSink(base64)));
	std::cout << "base64 (enc): " << base64 << std::endl;

	ciphertext.clear();
	StringSource(base64, true,
		new Base64Decoder(new StringSink(ciphertext)));
	std::cout << "base64 (dec): " << ciphertext << std::endl;

	std::cout << std::endl << std::endl;
	// -----




	//
	// Decrypt
	//
	CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	// -----
	//! 256bits (32bytes key(password))
	//CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH * 2);
	// -----
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
	stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertext.c_str() ), ciphertext.size() );
	stfDecryptor.MessageEnd();

	//
	// Dump Decrypted Text
	//
	std::cout << "Decrypted Text: " << std::endl;
	std::cout << decryptedtext;
	std::cout << std::endl << std::endl;

	return 0;
}

