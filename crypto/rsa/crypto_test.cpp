// RSA Encryption/Decryption Test
// hjkim, 2018.12.03

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdbool>
#include <string>
#include <exception>
#include <assert.h>

#include <crypto++/cryptlib.h>
#include <crypto++/rsa.h>
#include <crypto++/sha.h>
#include <crypto++/files.h>
#include <crypto++/osrng.h>



// PEM
// - https://www.cryptopp.com/wiki/PEM_Pack
// - https://github.com/noloader/cryptopp-pem
#include <pem.h>
#include <hex.h>
#include <crypto++/base64.h>
#include <crypto++/gzip.h>


using namespace CryptoPP;


/*
void encrypt_decrypt(void) {
	// Generate keys
	AutoSeededRandomPool rng;

	InvertibleRSAFunction params;
	params.GenerateRandomWithKeySize(rng, 3072);

	RSA::PrivateKey privateKey(params);
	RSA::PublicKey publicKey(params);

	string plain="RSA Encryption", cipher, recovered;


	// Encryption
	RSAES_OAEP_SHA_Encryptor e(publicKey);
	StringSource ss1(plain, true,
			new PK_EncryptorFilter(rng, e,
			new StringSink(cipher)
		) // PK_EncryptorFilter
	); // StringSource


	// Decryption
	RSAES_OAEP_SHA_Decryptor d(privateKey);
	StringSource ss2(cipher, true,
			new PK_DecryptorFilter(rng, d,
			new StringSink(recovered)
		) // PK_DecryptorFilter
	); // StringSource

	std::cout << "plain/text: " << plain << std::endl;
	std::cout << "encrypt: " << cipher << std::endl;
	std::cout << "decrypt: " << recovered << std::endl;
}
*/


void pem_test(void) {
	//! KEY
	// $ openssl genrsa -out rsa-priv.pem 2048
	// $ openssl rsa -in rsa-priv.pem -out rsa-pub.pem -pubout
	// $ openssl rsa -in rsa-priv.pem -out rsa-enc-priv.pem -aes256 -passout pass:test


	// Generate keys
	//AutoSeededRandomPool rng;
	//InvertibleRSAFunction params;
	//params.GenerateRandomWithKeySize(rng, 3072);
	//params.GenerateRandomWithKeySize(rng, 2048);
	//RSA::PrivateKey privateKey(params);
	//RSA::PublicKey publicKey(params);

	RSA::PrivateKey privkey;
	RSA::PublicKey pubkey;
	AutoSeededRandomPool rng;

	std::string plain = "RSA Encryption test";
	std::string passphrase = "1234";



	// Load a RSA public key
	FileSource fs1("./keys/public.pem", true);
	PEM_Load(fs1, pubkey);

	// Load a encrypted RSA private key
	//FileSource fs2("private.pem", true);
	FileSource fs2("./keys/private_enc.pem", true);
	PEM_Load(fs2, privkey, passphrase.data(), passphrase.size());

	bool valid = privkey.Validate(rng, 3);
	if (!valid) {
		std::cout << "error..." << std::endl;
		return;
	}



	RSAES_OAEP_SHA_Encryptor e(pubkey);
	RSAES_OAEP_SHA_Decryptor d(privkey);
	std::string encrypted, decrypted, base64, hex, compressed, decompressed;

	// Gzip
	StringSource(plain, true,
			new Gzip(new StringSink(compressed)));

	// Encryption
	//StringSource ss1(plain, true,
	StringSource(compressed, true,
			new PK_EncryptorFilter(rng, e,
			new StringSink(encrypted)
		) // PK_EncryptorFilter
	); // StringSource



	// ----------
	// base64 encode
	StringSource(encrypted, true,
			new Base64Encoder(new StringSink(base64)));
	StringSource(encrypted, true,
			new HexEncoder(new StringSink(hex)));


	std::cout << "Plain/text:\n" << plain << "\n" << std::endl;
	std::cout << "Compressed (gzip):\n" << compressed << "\n" << std::endl;
	std::cout << "Encrypted (gzip):\n" << encrypted << "\n" << std::endl;
	std::cout << "Encrypted (gzip: hex):\n" << hex << "\n" << std::endl;
	std::cout << "Encrypted (gzip: base64):\n" << base64 << "\n" << std::endl;
	std::cout << "\n\n" << std::endl;


	compressed = "";
	decompressed = "";
	encrypted = "";
	decrypted = "";
	hex = "";


	// base64 decode
	StringSource(base64, true,
			new Base64Decoder(new StringSink(encrypted)));

	StringSource(encrypted, true,
			new HexEncoder(new StringSink(hex)));

	std::cout << "Encrypted (gzip: hex):\n" << hex << "\n" << std::endl;
	// ----------


	// Decryption
	//StringSource ss2(encrypted, true,
	StringSource(encrypted, true,
			new PK_DecryptorFilter(rng, d,
			new StringSink(decrypted)
		) // PK_DecryptorFilter
	); // StringSource

	std::cout << "Decrypted (gzip):\n" << decrypted << "\n" << std::endl;

	// Gunzip
	StringSource(decrypted, true,
			new Gunzip(new StringSink(decompressed)));

	std::cout << "Decompressed (gzip):\n" << decompressed << "\n" << std::endl;
}



int main(int argc, char* argv[]) {
	pem_test();

	return 0;
}
