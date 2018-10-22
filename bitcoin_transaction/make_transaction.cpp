/* --------------------------------------------------------------
Project:	Make a Bitcoin Transaction
Purpose:	
Author:		Ho-Jung Kim (godmode2k@hotmail.com)
Date:		Since October 12, 2018
Filename:	make_transaction.cpp

Last modified: October 16, 2018
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
Note:
-----------------------------------------------------------------
1. Build:
	$ g++ -o make_transaction make_transaction.cpp \
		./bitcoin-master/src/base58.cpp \
		./bitcoin-master/src/crypto/sha256.cpp \
		-Wall -O2 -std=c++11 \
		-I./bitcoin-master/src
-------------------------------------------------------------- */



//! Header and Definition
// ---------------------------------------------------------------
#include "make_transaction.h"
// ---------------------------------------------------------------



//! Definition
// ---------------------------------------------------------------
// ---------------------------------------------------------------



//! Prototype
// ---------------------------------------------------------------
// ---------------------------------------------------------------



void base58_check(const char* base58_p2pkh, std::string& out_result) {
	// Decode base58 p2pkh (pubkey): decode base58 -> check -> encode to base256

	//const char* base58_p2pkh = "1KKKK6N21XKo48zWKuQKXdvSsCf95ibHFa";
	std::vector<unsigned char> result;

	if ( !DecodeBase58Check(base58_p2pkh, result) ) {
		std::cout << "base58_check(): error: decode base58 check" << std::endl;
	}

	std::cout << "base58_check(): result: size = " << result.size() << std::endl;
	//std::cout << "base58_check(): expect result:\nc8 e9 09 96 c7 c6 08 0e e0 62 84 60 0c 68 4e d9 04 d1 4c 5c" << std::endl;
	std::cout << "base58_check(): result:" << std::endl;

	std::vector<unsigned char>::iterator iter;
	std::string str;

	for ( iter = result.begin(); iter != result.end(); ++iter ) {
		//if ( *iter == 0 ) continue;
		// skip first '00'
		if ( iter == result.begin() ) continue;
		//printf( "%02x ", *iter );
		std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)*iter << " ";

		std::stringstream ss;
		ss << std::setfill('0') << std::setw(2) << std::hex << (int)*iter;
		str.append( ss.str() );
	}

	std::cout << "\nbase58_check(): result:\n" << str.c_str() << std::endl;
	str = "76a914" + str + "88ac";
	std::cout << "base58_check(): final result: (76 a9 14 (20bytes base256) 88 ac)\n" << str.c_str() << std::endl;

	out_result = str;
}

void make_raw_transaction(
	std::string& out_result,
	const char* vin_prev_vout_transaction_hash,
	const int vin_prev_vout_transaction_hash_len,
	const int vin_prev_vout_source_index,
	const char* vin_script_sig_hex,
	const char* base58_pubkey_receiver,
	const int64_t amount_satoshi
) {
	// input
//	constexpr const char* vin_prev_vout_transaction_hash =
//		"81b4c832d70cb56ff957589752eb4125a4cab78a25a8fc52d6a09e5bd4404d48";
//	constexpr const int vin_prev_vout_transaction_hash_len = strlen(vin_prev_vout_transaction_hash);
	char vin_prev_vout_transaction_hash_reverse[vin_prev_vout_transaction_hash_len + 1] = {0,};
//	const int vin_prev_vout_source_index = 0;
	std::string vin_prev_vout_source_index_str_hex;
	std::string vin_prev_vout_source_index_str_hex_le;
	{
		//std::stringstream ss_hex;
		//std::string str_hex;
		//ss_hex << std::setfill('0') << std::setw(sizeof(int)*2) << std::hex << vin_prev_vout_source_index
		//	<< std::setfill('0') << std::setw(sizeof(int)*2) << std::hex << 0;
		//vin_prev_vout_source_index_str_hex = ss_hex.str();

		// uint16_t
		std::stringstream ss_hex;
		std::string str_hex;
		// 00 00 00 00
		ss_hex << std::setfill('0') << std::setw(sizeof(char)*8) << std::hex << vin_prev_vout_source_index;
		str_hex = ss_hex.str();
		//std::cout << "-> " << ss_hex.str() << std::endl;
		//std::cout << "-> " << str_hex.c_str() << std::endl;

		vin_prev_vout_source_index_str_hex = str_hex;
		{
			// reverse
			std::string str_hex_reverse;
			for ( int i = 0, j = str_hex.length() - 1; j > 0; i += 2, j -= 2 ) {
				str_hex_reverse += str_hex.at(j-1);
				str_hex_reverse += str_hex.at(j);
			}
			vin_prev_vout_source_index_str_hex_le = str_hex_reverse.c_str();
		}

		std::cout << std::endl;
		std::cout << "prev output source index: hex le = "
			<< vin_prev_vout_source_index_str_hex_le.c_str() << std::endl;
		std::cout << std::endl;
	}


	// sender pubkey
//	const char* vin_script_sig_hex = "";
	std::string vin_script_sig_str_len;

	{

		std::stringstream ss_hex;
		std::stringstream ss_hex_len;
		std::string str_hex;
		std::string str_hex_len;
		ss_hex << vin_script_sig_hex;
		str_hex = ss_hex.str();
		//std::cout << "hex -> " << ss_hex.str() << std::endl;
		//std::cout << "len(hex)/2 -> " << str_hex.length() / 2 << std::endl;
		//std::cout << "hex len(hex)/2 -> " << std::setfill('0') << std::setw(2) << std::hex
		//	<< str_hex.length() / 2 << std::endl;

		ss_hex_len << std::setfill('0') << std::setw(2) << std::hex << str_hex.length() / 2;
		str_hex_len = ss_hex_len.str();
		//std::cout << "hex len(hex)/2 -> " << str_hex_len.c_str() << std::endl;
		
		vin_script_sig_str_len = ss_hex_len.str();
	}



	// output
	//const char* vout_value_hex_le = "6264010000000000"; // 91234 (satoshis: .12345678) -> hex LE
//	const long double vout_value = .00091234; // 91234 (satoshis: .12345678) -> hex LE
	std::string vout_value_hex_le; // 91234 (satoshis: .12345678) -> hex LE
//	const char* vout_base58_p2pkh = "1KKKK6N21XKo48zWKuQKXdvSsCf95ibHFa"; // to address (receiver)
	const char* vout_base58_p2pkh = base58_pubkey_receiver;
	std::string vout_script_pubkey_str;
	std::string vout_script_pubkey_str_len;
	{
		//std::cout << "satoshi: " << vout_value << std::endl;
		//std::cout << "satoshi: " << (vout_value * 100000000) << std::endl;
		//std::cout << "satoshi: (int64_t) " << (int64_t)(vout_value * 100000000) << std::endl;
		//std::cout << "satoshi: round (int64_t) " << (int64_t)std::round(vout_value * 100000000) << std::endl;
		std::cout << "satoshi: round (int64_t) " << amount_satoshi << std::endl;
		//printf( "%Lf, %ld\n", (vout_value * 100000000), (int64_t)std::round(vout_value * 100000000) );
		
		// value
		std::stringstream ss_value_hex;
		std::string str_value_hex;
		// 00 00 00 00 00 00 00 00
		//ss_value_hex << std::setfill('0') << std::setw(sizeof(int)*4) << std::hex << 91234;
		//ss_value_hex << std::setfill('0') << std::setw(sizeof(int)*4) << std::hex << (int64_t)std::round(vout_value * 100000000);
		//ss_value_hex << std::setfill('0') << std::setw(sizeof(int)*4) << std::hex << MAKE_SATOSHI(vout_value);
		ss_value_hex << std::setfill('0') << std::setw(sizeof(int)*4) << std::hex << amount_satoshi;
		str_value_hex = ss_value_hex.str();
		//std::cout << "value: " << ss_value_hex.str() << std::endl;
		std::cout << "value: " << str_value_hex.c_str() << std::endl;

		uint32_t u32 = strtoull( str_value_hex.c_str(), 0, 16 );
		std::stringstream ss_value_hex_le;
		std::string str_value_hex_le;
		// hex: 62 64 01 00 + 00 00 00 00
		ss_value_hex_le << std::hex << ntohl(u32) << std::setfill('0') << std::setw(sizeof(int)*2) << std::hex << 0;
		str_value_hex_le = ss_value_hex_le.str();
		std::cout << "value: hex le = " << str_value_hex_le.c_str() << std::endl;
		std::cout << std::endl;

		vout_value_hex_le = str_value_hex_le.c_str();


		// script pubkey length
		std::stringstream ss_hex_len;
		base58_check( vout_base58_p2pkh, vout_script_pubkey_str );
		ss_hex_len << std::setfill('0') << std::setw(2) << std::hex << vout_script_pubkey_str.length() / 2;
		vout_script_pubkey_str_len = ss_hex_len.str();
	}
	



	// reverse previous output tx hash
	{
		//memset( prev_vout_transaction_hash_reverse, 0x00, sizeof(prev_vout_transaction_hash_reverse) );
		for ( int i = 0, j = vin_prev_vout_transaction_hash_len - 1; j > 0; i += 2, j -= 2 ) {
			vin_prev_vout_transaction_hash_reverse[i] = vin_prev_vout_transaction_hash[j-1];
			vin_prev_vout_transaction_hash_reverse[i+1] = vin_prev_vout_transaction_hash[j];
		}
		std::cout << std::endl;
		std::cout << "prev vout tx hash: " << vin_prev_vout_transaction_hash << std::endl;
		std::cout << "(reverse)        : " << vin_prev_vout_transaction_hash_reverse << std::endl;
	}




	// result
	{
		char result[1024] = {0,};
		snprintf( result, sizeof(result),
				//"%s%s"
				//"%s%s%s%s%s"
				//"%s"
				//"%s%s%s"
				//"%s%s",

				"----------------------------\n"
				"version                    : %s\n"
				"input count                : %s\n"
				"\n"
				"[input]\n"
				"reverse prev output tx hash: %s\n"
				"prev output source index   : %s\n"
				"scriptsig length           : %s\n"
				"scriptsig                  : %s\n"
				"sequence                   : %s\n"
				"\n"
				"output count               : %s\n"
				"\n"
				"[output]\n"
				"value                      : %s\n"
				"script length              : %s\n"
				"script pubkey              : %s\n"
				"\n"
				"block lock time            : %s\n"
				"\n"
				"hash code type             : %s\n"
				"----------------------------\n",



				"01000000",		// version
				"01",			// number of input

				// input
				vin_prev_vout_transaction_hash_reverse,			// reverse prev output tx hash
				vin_prev_vout_source_index_str_hex_le.c_str(),	// prev output source index
				vin_script_sig_str_len.c_str(),					// scriptsig length
				vin_script_sig_hex,								// scriptsig
				"ffffffff",										// sequence

				// output
				"01",										// output count
				vout_value_hex_le.c_str(),					// value: satoshis (.12345678) hex LE
				vout_script_pubkey_str_len.c_str(),			// script length
				vout_script_pubkey_str.c_str(),				// script pubkey

				// block lock time
				"00000000",									// block lock time

				// hash code type
				"01000000"									// hash code type
				);
		std::cout << "\nresult:\n" << result << std::endl;

		out_result = "";
		out_result += "01000000";	// version
		out_result += "01";			// number of input

		// input
		out_result += vin_prev_vout_transaction_hash_reverse;			// reverse prev output tx hash
		out_result += vin_prev_vout_source_index_str_hex_le.c_str();	// source index
		out_result += vin_script_sig_str_len.c_str();					// scriptsig length
		out_result += vin_script_sig_hex;								// scriptsig
		out_result += "ffffffff";										// sequence

		// output
		out_result += "01";										// output count
		out_result += vout_value_hex_le.c_str();				// value: satoshis (.12345678) hex LE
		out_result += vout_script_pubkey_str_len.c_str();		// script length
		out_result += vout_script_pubkey_str.c_str();			// script pubkey

		// block lock time
		out_result += "00000000";								// block lock time

		// hash code type
		out_result += "01000000";								// hash code type
	}
}

void make_raw_signed_transaction(
	std::string& out_result,
	const char* privkey,
	const char* vin_prev_vout_transaction_hash,
	const int vin_prev_vout_transaction_hash_len,
	const int vin_prev_vout_source_index,
	const char* pubkey_sender,
	const char* pubkey_receiver,
	const int64_t amount_satoshi
) {
	std::string result_tx;
	std::string result_signed_tx;

	{
		std::string script_pubkey_str;
		base58_check( pubkey_sender, script_pubkey_str );

		make_raw_transaction(
			result_tx,
			vin_prev_vout_transaction_hash,
			vin_prev_vout_transaction_hash_len,
			vin_prev_vout_source_index,
			script_pubkey_str.c_str(),		// sriptsig
			pubkey_receiver,				// base58 pubkey
			amount_satoshi );
		std::cout << "result (tx):\n" << result_tx.c_str() << std::endl;
	}

	// sign
	{
		std::string out_privkey;
		base58_check( privkey, out_privkey );
		std::cout << "script privkey: " << out_privkey << std::endl;

		//! TODO: signed scriptSig
		//
	}
}

int main(void) {
	std::string result_tx;
	std::string result_signed_tx;

	// https://en.bitcoin.it/wiki/List_of_address_prefixes
	// Private key: base58 WIF (compressed pubkey; prefix 'K or L', uncompressed pubkey; prefix '5')
	const char* privkey = "KxDcFkCGcbtrzZH5TYEbMqMgAnFVvwGLCbAo9qhhEbG2bSYhJtfT";
	constexpr const char* vin_prev_vout_transaction_hash =
		"81b4c832d70cb56ff957589752eb4125a4cab78a25a8fc52d6a09e5bd4404d48";
	constexpr const int vin_prev_vout_transaction_hash_len = strlen(vin_prev_vout_transaction_hash);
	const int vin_prev_vout_source_index = 1;
	const char* pubkey_sender = "1MMMMSUb1piy2ufrSguNUdFmAcvqrQF8M5";
	const char* pubkey_receiver = "1KKKK6N21XKo48zWKuQKXdvSsCf95ibHFa";
	const long double amount = .00091234;
	const int64_t amount_satoshi = MAKE_SATOSHI( amount );

	// NOTE: doesn't correct
	// pubkey: 1MMMMSUb1piy2ufrSguNUdFmAcvqrQF8M5
	// WIF: 5HueCGU8rMjxEXxiPuD5BDku4MkFqeZyd4dZ1jvhTVqvbTLvyTJ
	// privkey: 0C28FCA386C7A227600B2FE50B7CAE11EC86D3BF1FBE471BE89827E19D72AA1D
	//          removed fist 1byte and last 4bytes
	

	// test: make_raw_transaction()
	/*
	{
		std::string script_pubkey_str;
		base58_check( pubkey_sender, script_pubkey_str );

		make_raw_transaction(
			result_tx,
			vin_prev_vout_transaction_hash,
			vin_prev_vout_transaction_hash_len,
			vin_prev_vout_source_index,
			script_pubkey_str.c_str(),		// sriptsig
			pubkey_receiver,				// base58 pubkey
			amount_satoshi );
		std::cout << "result (tx):\n" << result_tx.c_str() << std::endl;
	}
	*/

	// test: make_raw_signed_transaction()
	{
		make_raw_signed_transaction(
			result_signed_tx,
			privkey,
			vin_prev_vout_transaction_hash,
			vin_prev_vout_transaction_hash_len,
			vin_prev_vout_source_index,
			pubkey_sender, 		// scriptsig
			pubkey_receiver,	// base58 pubkey
			amount_satoshi );
		std::cout << std::endl;
		std::cout << "result (signed tx):\n" << result_signed_tx.c_str() << std::endl;
	}


	return 0;
}
