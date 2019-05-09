// Copyright (c) 2014-2019 The Flashcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef FLASHCOIN_BLOCK_SIGNING_H
#define FLASHCOIN_BLOCK_SIGNING_H

#define MCLBN_FP_UNIT_SIZE 4
#define MCLBN_IO_SERIALIZE_HEX_STR 2048
#include <bls/bls.hpp>
#include <fstream>
#define  CONF_BLS_PUBKEY "84c3ad891b842ca6788bd79e0eb8d06da59fe94acc6a35382f3beee5b9032e177012ed91d5a4fe5f4fa717d8014cc377847ad5508769719b76d0e93e38a53d94"

bool BlsVerifyCoinbaseTransaction(const std::string &scriptSig, const std::string _hashPrevBlock);
std::string BlsSerializeMessage(const std::string &nHeigh, const std::string &nExtraNonce, const std::string &_hashPrevBlock);

#endif // FLASHCOIN_BLOCK_SIGNING_H