#ifndef __MAKE_TRANSACTION_H__
#define __MAKE_TRANSACTION_H__

/* --------------------------------------------------------------
Project:	Make a Bitcoin Transaction
Purpose:	
Author:		Ho-Jung Kim (godmode2k@hotmail.com)
Date:		Since October 12, 2018
Filename:	make_transaction.h

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
-------------------------------------------------------------- */



//! Header and Definition
// ---------------------------------------------------------------
#include <iostream>
#include <iomanip>			// std::setfill
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cmath>			// std::round

#include <arpa/inet.h>		// ntohl

#include "base58.h"
// ---------------------------------------------------------------



//! Definition
// ---------------------------------------------------------------
#define MAKE_SATOSHI(amount)	(int64_t)std::round(amount * 100000000)
// ---------------------------------------------------------------



//! Prototype
// ---------------------------------------------------------------
void base58_check(const char* base58_p2pkh, std::string& out_result);
void make_raw_transaction(
	std::string& out_result,
	const char* vin_prev_vout_transaction_hash,
	const int vin_prev_vout_transaction_hash_len,
	const int vin_prev_vout_source_index,
	const char* vin_script_sig_hex,
	const char* base58_pubkey_receiver,
	const int64_t amount_satoshi
);
void make_raw_signed_transaction(
	std::string& out_result,
	const char* privkey,
	const char* vin_prev_vout_transaction_hash,
	const int vin_prev_vout_transaction_hash_len,
	const int vin_prev_vout_source_index,
	const char* pubkey_sender,
	const char* pubkey_receiver,
	const int64_t amount_satoshi
);
// ---------------------------------------------------------------



#endif	// __MAKE_TRANSACTION_H__
