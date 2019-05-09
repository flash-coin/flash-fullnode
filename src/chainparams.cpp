// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = CONF_PSZTIMESTAMP;
    const CScript genesisOutputScript = CScript() << ParseHex(CONF_SCRIPT_PUBKEY) << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 9000;
        consensus.BIP34Hash = uint256S("625f7f268ef85c24c0d03d0e7b0a37ed4ecd37fbb31e676495a0b5e1e2b1ef2f");
        consensus.powLimit = uint256S("7fffff0000000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
        consensus.nPowTargetSpacing = 2.5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = true; // don't adjust difficulty of mining every 2016 blocks.
        consensus.nRuleChangeActivationThreshold = 6048; // 75% of 8064
        consensus.nMinerConfirmationWindow = 8064; // nPowTargetTimespan / nPowTargetSpacing * 4
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1485561600; // January 28, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517356801; // January 31st, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1485561600; // January 28, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1517356801; // January 31st, 2018

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");  // WL: Change to minimum dificulty

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xdb;
        
        nDefaultPort = CONF_PORT;
        
		nPruneAfterHeight = 100000;
		
		genesis = CreateGenesisBlock(CONF_BLOCK_NTIME, CONF_BLOCK_NNONCE, CONF_BLOCK_NBITS, CONF_BLOCK_NVERSION, 100000 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S(CONF_GENESIS_BLOCK));
		assert(genesis.hashMerkleRoot == uint256S(CONF_BLOCK_HASH_MERKLE_ROOT));

        vSeeds.push_back(CDNSSeedData("Seed Node 1", "88.150.227.120"));
        vSeeds.push_back(CDNSSeedData("Seed Node 2", "35.176.101.245"));
        vSeeds.push_back(CDNSSeedData("Seed Node 3", "34.250.49.12"));        
        vSeeds.push_back(CDNSSeedData("Seed Node 4", "82.221.107.80"));
        vSeeds.push_back(CDNSSeedData("Seed Node 5", "82.221.107.83"));
        vSeeds.push_back(CDNSSeedData("Seed Node 6", "82.221.107.96"));
        vSeeds.push_back(CDNSSeedData("Seed Node 7", "13.229.38.118"));
        vSeeds.push_back(CDNSSeedData("Seed Node 8", "52.66.168.142"));
        vSeeds.push_back(CDNSSeedData("Seed Node 9", "13.112.113.227"));
        vSeeds.push_back(CDNSSeedData("Seed Node 10", "190.97.165.161"));
        vSeeds.push_back(CDNSSeedData("Seed Node 11", "190.97.165.163"));
        vSeeds.push_back(CDNSSeedData("Seed Node 12", "54.233.226.7"));
        vSeeds.push_back(CDNSSeedData("Seed Node 13", "54.233.227.177"));
        vSeeds.push_back(CDNSSeedData("Seed Node 14", "216.218.213.188"));
        vSeeds.push_back(CDNSSeedData("Seed Node 15", "216.218.213.189"));
        vSeeds.push_back(CDNSSeedData("Seed Node 16", "216.218.213.190"));        
        vSeeds.push_back(CDNSSeedData("Seed Node 17", "52.60.235.209"));
        vSeeds.push_back(CDNSSeedData("Seed Node 18", "192.99.95.233"));
        vSeeds.push_back(CDNSSeedData("Seed Node 19", "108.170.20.78"));
        vSeeds.push_back(CDNSSeedData("Seed Node 20", "66.85.173.32"));
        vSeeds.push_back(CDNSSeedData("Seed Node 21", "51.68.127.44"));
        vSeeds.push_back(CDNSSeedData("Seed Node 22", "54.37.232.99"));
        vSeeds.push_back(CDNSSeedData("Seed Node 23", "54.36.162.36"));
        vSeeds.push_back(CDNSSeedData("Seed Node 24", "51.68.174.104"));
        vSeeds.push_back(CDNSSeedData("Seed Node 25", "51.77.203.183"));
        vSeeds.push_back(CDNSSeedData("Seed Node 26", "51.75.68.116"));
        vSeeds.push_back(CDNSSeedData("Seed Node 27", "206.189.224.162"));
        vSeeds.push_back(CDNSSeedData("Seed Node 28", "139.99.75.33"));
        vSeeds.push_back(CDNSSeedData("Seed Node 29", "139.99.219.165"));
        vSeeds.push_back(CDNSSeedData("Seed Node 30", "139.59.64.48"));
        vSeeds.push_back(CDNSSeedData("Seed Node 31", "142.44.131.165"));

        vSeeds.push_back(CDNSSeedData("flashcointools.com", "dnsseed.flashcointools.com"));
        vSeeds.push_back(CDNSSeedData("flashcoinpool.org", "dnsseed.flashcoinpool.org"));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,CONF_PUBKEY_ADDRESS);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,CONF_SCRIPT_ADDRESS);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,50);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,CONF_SECRET_KEY);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;  // 13Apr2018-WL: set it back to true to prevent mining old-blocks 
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

	checkpointData = (CCheckpointData) {
		boost::assign::map_list_of
			( 0, uint256S(CONF_GENESIS_BLOCK))
        	( 57742, uint256S("0xfdc91783d135a0891c8c86a4ade070a5ddf3b39fec2ecfcfe520295f6c4f244f"))
        	( 116900, uint256S("0x9e78b5eb7ecb0ef14c296ce407a25ecf25482f60917e2786f879e417c0730ff8"))
			( 440638, uint256S("0xca5636ef71f4bee77fe877684fcccfb1569048de986db295bc1e78c4f8da9e2e"))
            ( 447624, uint256S("0x000002c7f3d429b10c7f2986fee12453a8ab5272b3fb0b160da91bd11c92723a"))
            ( 448307, uint256S("0x0000011b9dc38fa761d1a965c515a7794b49ba9808e42c25f85912f8f935883d"))
            ( 467265, uint256S("0x8244761282109d771447a8de38833fc8817725f832a8c4c00ee9183a21255e1a"))
            ( 468609, uint256S("0x000001113a8a0315f1c827ab97948497c048c96ff9fbce24669eaaa7c136dbf9"))
            ( 473910, uint256S("0x0d337af8ee21d92e43b4960cd734d657d30c5831494d5895113a66010d997e89"))
            ( 473924, uint256S("0x000002bc2207473998a5f9b3433049f70a87a736f090b623a7f20da4a8ccaf71"))
            ( 539307, uint256S("0x0000a08a204cb9a6c8862c1d788dd01df3161a96c7f45399828176feb7220d10"))
            ( 852847, uint256S("0x00002e2923f07893b6c23562d17ded2bf7acbb9dd8ee12fcdce465d15fc41e7b"))
            ( 852892, uint256S("0x0000f203ac1bbf853758a596483c4462aab259d0375bcbb1be961133b83b6c32"))
            ( 856789, uint256S("0x0000d22e5f36d63342e7ee4adf850b861f0bb27ddc050e803cb3bdcdabd4f1be"))
            ( 857691, uint256S("0x0000fc2b81e655fc5a5c0b2e7ec933e2af1af9777ffebf2d72b32bc0815eb638"))
            ( 859398, uint256S("0x00003d8db263a75dd1e2ed292872181177338687903aee1e6c40a6358ed2443a"))
            ( 859420, uint256S("0x000085fabe7aed6f4d15e9a04b254f9d7d27a5f114558b0b759af9049090558d")),
			1555170416, // * UNIX timestamp of last checkpoint block
        	1701780,   // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        	1000.0    // * estimated number of transactions per day after checkpoint
	};

    }
};
static CMainParams mainParams;

/**
 * Testnet (v4)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
		consensus.nSubsidyHalvingInterval = 840000;
	    consensus.nMajorityEnforceBlockUpgrade = 51;
	    consensus.nMajorityRejectBlockOutdated = 75;
	    consensus.nMajorityWindow = 100;
	    consensus.BIP34Height = -1;
	    consensus.BIP34Hash = uint256S("");
	    consensus.powLimit = uint256S("7fffff0000000000000000000000000000000000000000000000000000000000");
	    consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
	    consensus.nPowTargetSpacing = 2.5 * 60;
	    consensus.fPowAllowMinDifficultyBlocks = true;
	    consensus.fPowNoRetargeting = false;
	    consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
	    consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
	    consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
	    consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
	    consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

	    // Deployment of BIP68, BIP112, and BIP113.
	    consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
	    consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1483228800; // January 1, 2017
	    consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517356801; // January 31st, 2018

	    // Deployment of SegWit (BIP141, BIP143, and BIP147)
	    consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
	    consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1483228800; // January 1, 2017
	    consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1517356801; // January 31st, 2018

	    // The best chain should have at least this much work.
	    consensus.nMinimumChainWork = uint256S("0x00");
	
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xdc;
		
		nDefaultPort = CONF_TESTNET_PORT;
		nPruneAfterHeight = 1000;
		
		genesis = CreateGenesisBlock(CONF_BLOCK_NTIME_TESTNET, CONF_BLOCK_NNONCE_TESTNET, CONF_BLOCK_NBITS, CONF_BLOCK_NVERSION, 100000 * COIN);
		consensus.hashGenesisBlock = genesis.GetHash();
		assert(consensus.hashGenesisBlock == uint256S(CONF_GENESIS_BLOCK_TESTNET));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("flashcointools.com", "testnet-seed.flashcointools.com"));
        vSeeds.push_back(CDNSSeedData("loshan.co.uk", "seed-b.flashcoin.loshan.co.uk", true));
        vSeeds.push_back(CDNSSeedData("thrasher.io", "dnsseed-testnet.thrasher.io", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,CONF_PUBKEY_ADDRESS_TEST);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,CONF_SCRIPT_ADDRESS_TEST);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,CONF_SECRET_KEY_TEST);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true; // 13Apr2018-WL: set it back to true to prevent mining old-blocks 
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;


        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
        	(0, uint256S(CONF_GENESIS_BLOCK_TESTNET)),
            0,
            0,
            0
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffff0000000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 2.5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nDefaultPort = CONF_TESTNET_PORT;
		nPruneAfterHeight = 1000;
		
		genesis = CreateGenesisBlock(CONF_BLOCK_NTIME_TESTNET, CONF_BLOCK_NNONCE_TESTNET, CONF_BLOCK_NBITS, CONF_BLOCK_NVERSION, 100000 * COIN);
		consensus.hashGenesisBlock = genesis.GetHash();
		assert(consensus.hashGenesisBlock == uint256S(CONF_GENESIS_BLOCK_TESTNET));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true; 
        fTestnetToBeDeprecatedFieldRPC = false;

	checkpointData = (CCheckpointData){
		boost::assign::map_list_of
			( 0, uint256S("0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206")),
			0,
			0,
			0
	};

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,CONF_PUBKEY_ADDRESS_TEST);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,CONF_SCRIPT_ADDRESS_TEST);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,CONF_SECRET_KEY_TEST);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}
 
