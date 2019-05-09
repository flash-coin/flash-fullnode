// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "coins.h"
#include "consensus/consensus.h"
#include "consensus/merkle.h"
#include "consensus/validation.h"
#include "main.h"
#include "miner.h"
#include "pubkey.h"
#include "script/standard.h"
#include "txmempool.h"
#include "uint256.h"
#include "util.h"
#include "utilstrencodings.h"

#include "test/test_bitcoin.h"

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(miner_tests, TestingSetup)

static
struct {
    unsigned char extranonce;
    unsigned int nonce;
} blockinfo[] = {
    {4, 0xa4ad9f65}, {2, 0x15cf2b27}, {1, 0x037620ac}, {1, 0x700d9c54},
    {2, 0xce79f74f}, {2, 0x52d9c194}, {1, 0x77bc3efc}, {2, 0xbb62c5e8},
    {2, 0x83ff997a}, {1, 0x48b984ee}, {1, 0xef925da0}, {2, 0x680d2979},
    {2, 0x08953af7}, {1, 0x087dd553}, {2, 0x210e2818}, {2, 0xdfffcdef},
    {1, 0xeea1b209}, {2, 0xba4a8943}, {1, 0xa7333e77}, {1, 0x344f3e2a},
    {3, 0xd651f08e}, {2, 0xeca3957f}, {2, 0xca35aa49}, {1, 0x6bb2065d},
    {2, 0x0170ee44}, {1, 0x6e12f4aa}, {2, 0x43f4f4db}, {2, 0x279c1c44},
    {2, 0xb5a50f10}, {2, 0xb3902841}, {2, 0xd198647e}, {2, 0x6bc40d88},
    {1, 0x633a9a1c}, {2, 0x9a722ed8}, {2, 0x55580d10}, {1, 0xd65022a1},
    {2, 0xa12ffcc8}, {1, 0x75a6a9c7}, {2, 0xfb7c80b7}, {1, 0xe8403e6c},
    {1, 0xe34017a0}, {3, 0x659e177b}, {2, 0xba5c40bf}, {5, 0x022f11ef},
    {1, 0xa9ab516a}, {5, 0xd0999ed4}, {1, 0x37277cb3}, {1, 0x830f735f},
    {1, 0xc6e3d947}, {2, 0x824a0c1b}, {1, 0x99962416}, {1, 0x75336f63},
    {1, 0xaacf0fea}, {1, 0xd6531aec}, {5, 0x7afcf541}, {5, 0x9d6fac0d},
    {1, 0x4cf5c4df}, {1, 0xabe0f2a0}, {6, 0x4a3dac18}, {2, 0xf265febe},
    {2, 0x1bc9f23f}, {1, 0xad49ab71}, {1, 0x9f2d8923}, {1, 0x15acb65d},
    {2, 0xd1cecb52}, {2, 0xf856808b}, {1, 0x0fa96e29}, {1, 0xe063ecbc},
    {1, 0x78d926c6}, {5, 0x3e38ad35}, {5, 0x73901915}, {1, 0x63424be0},
    {1, 0x6d6b0a1d}, {2, 0x888ba681}, {2, 0xe96b0714}, {1, 0xb7fcaa55},
    {2, 0x19c106eb}, {1, 0x5aa13484}, {2, 0x5bf4c2f3}, {2, 0x94d401dd},
    {1, 0xa9bc23d9}, {1, 0x3a69c375}, {1, 0x56ed2006}, {5, 0x85ba6dbd},
    {1, 0xfd9b2000}, {1, 0x2b2be19a}, {1, 0xba724468}, {1, 0x717eb6e5},
    {1, 0x70de86d9}, {1, 0x74e23a42}, {1, 0x49e92832}, {2, 0x6926dbb9},
    {0, 0x64452497}, {1, 0x54306d6f}, {2, 0x97ebf052}, {2, 0x55198b70},
    {2, 0x03fe61f0}, {1, 0x98f9e67f}, {1, 0xc0842a09}, {1, 0xdfed39c5},
    {1, 0x3144223e}, {1, 0xb3d12f84}, {1, 0x7366ceb7}, {5, 0x6240691b},
    {2, 0xd3529b57}, {1, 0xf4cae3b1}, {1, 0x5b1df222}, {1, 0xa16a5c70},
    {2, 0xbbccedc6}, {2, 0xfe38d0ef},
};

CBlockIndex CreateBlockIndex(int nHeight)
{
    CBlockIndex index;
    index.nHeight = nHeight;
    index.pprev = chainActive.Tip();
    return index;
}

bool TestSequenceLocks(const CTransaction &tx, int flags)
{
    LOCK(mempool.cs);
    return CheckSequenceLocks(tx, flags);
}

// Test suite for ancestor feerate transaction selection.
// Implemented as an additional function, rather than a separate test case,
// to allow reusing the blockchain created in CreateNewBlock_validity.
// Note that this test assumes blockprioritysize is 0.
void TestPackageSelection(const CChainParams& chainparams, CScript scriptPubKey, std::vector<CTransaction *>& txFirst)
{
}

// NOTE: These tests rely on CreateNewBlock doing its own self-validation!
BOOST_AUTO_TEST_CASE(CreateNewBlock_validity)
{
}

BOOST_AUTO_TEST_SUITE_END()
