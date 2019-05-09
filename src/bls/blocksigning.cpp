// Copyright (c) 2014-2019 The Flashcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "blocksigning.h"
#include "util.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>  

#include <fstream>  // read privkeyfile.dat
#include <cstdlib>

#include "primitives/block.h"
 
using namespace std;
 
vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
 
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
 
  return internal;
}


bool BlsVerifyCoinbaseTransaction(const std::string &scriptSig, const std::string _hashPrevBlock)
{
    bls::init(); // use BN254
	// Init public key
	bls::PublicKey _pubkey;
    _pubkey.setStr(CONF_BLS_PUBKEY, MCLBN_IO_SERIALIZE_HEX_STR);
	// Init Signature
	bls::Signature sig;
	// Parse data signature from ScriptSig
	vector<std::string> arStr = split(scriptSig, ' ');

	if(arStr.size() > 2)
	{
		// Set Signature
		try{
			sig.setStr(arStr[2], MCLBN_IO_SERIALIZE_HEX_STR);
		}catch (exception& e){
			//cout << "Erorr! Exception: Miner Signature is not valid form" << arStr[2].c_str() << e.what() << endl;
			LogPrintf("Erorr! Exception: Miner Signature is not valid form: %s; e.what(): %s\n", arStr[2].c_str(), e.what());
			return false;
		}
		std::string messageSign = BlsSerializeMessage(arStr[0], arStr[1], _hashPrevBlock);
		if (sig.verify(_pubkey, messageSign)) {
			return true;
		} else {
			return false;
		}
	}
	return false; 
}

std::string BlsSerializeMessage(const std::string &nHeigh, const std::string &nExtraNonce, const std::string &_hashPrevBlock){
	return nHeigh + ":" + nExtraNonce + ":" + _hashPrevBlock;
}
