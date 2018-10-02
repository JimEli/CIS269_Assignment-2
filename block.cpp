/*************************************************************************
* Title: Block Class
* File: block.cpp
* Author: James Eli
* Date: 9/21/2018
*
* Blockchain Block Class Definition.
*
* Notes:
*  (1) Compiled/tested with MS Visual Studio 2017 Community (v141), and
*      Windows SDK version 10.0.17134.0
*  (2) Compiled/tested with Eclipse Oxygen.3a Release (4.7.3a), using
*      CDT 9.4.3 and MinGw gcc-g++ (6.3.0-1).
*
* Submitted in partial fulfillment of the requirements of PCC CIS-269.
*************************************************************************
* Change Log:
*   09/21/2018: Initial release. JME
*************************************************************************/
#include "block.h"

using namespace myBlock;

// All member ctor.
Block::Block(
	const unsigned long i,     // id
	char* h = nullptr,         // hash
	char* ph = nullptr,        // previous hash
	const unsigned long n = 0, // nonce
	const time_t t = 0         // time stamp
) : id(i), nonce(n), timeId(t)
{
	setHash(h);
	setPreviousHash(ph);
}

// All but hash ctor.
Block::Block(
	const unsigned long i,     // id
	char* ph = nullptr,        // previous hash
	const unsigned long n = 0, // nonce
	const time_t t = 0         // time stamp
) : id(i), nonce(n), timeId(t)
{
	setPreviousHash(ph);
	setHash((char *)std::to_string(calcHash()).c_str());
}

// Genesis block creator ctor.
Block::Block(unsigned long i)
{
	setTimeID(timeStamp());
	setID(i);
	setNonce(0);
	sHash = std::to_string(calcHash());
}

// Get/set id.
unsigned long Block::getID() const { return id; }
void Block::setID(unsigned long i) { id = i; }

// Get/set nonce.
unsigned long Block::getNonce() const { return nonce; }
void Block::setNonce(unsigned long n) { this->nonce = n; }

// Get/set time stamp.
time_t Block::getTimeID() const { return timeId; }
void Block::setTimeID(time_t ts) { this->timeId = ts; }

// Get/set hash.
char* Block::getHash() const { char* hash = (char *)sHash.c_str(); return hash; }
void Block::setHash(char* h) { sHash.assign(h, strlen(h)); }

// Get/set previous hash.
char* Block::getPreviousHash() const { char* previousHash = (char *)sPreviousHash.c_str(); return previousHash; }
void Block::setPreviousHash(char* ph) { sPreviousHash.assign(ph, strlen(ph)); }

// Compute hash from "prevHash + nonce". Return as 32-bit value.
inline uint32_t Block::calcHash() const
{
	//if (sPreviousHash.empty())
		//throw std::invalid_argument("prev hash null");

	// Hash function is fed a std::string.
	std::hash<std::string> sHash;
	std::stringstream ss;

	ss << sPreviousHash << nonce;

	return static_cast<uint32_t>(sHash(ss.str()));
}

// Block miner.
void Block::MineBlock(unsigned int difficulty)
{
	// Build string with difficulty number of leading zeros.
	std::string sDifficulty(difficulty, '0');

	uint32_t hash;			// Temp holder of 32-bit hash value.
	std::stringstream hexHash;	// Hash value formatted as hex string.

	// Loop (incrementing nonce) until hash meets difficulty level.
	do
	{
		nonce++;                // Increment nonce.
		hash = calcHash();      // Hash "prevhash + nonce".
		// Push integer through hex manipulator.
		hexHash.str("");
		hexHash << std::hex << std::setfill('0') << std::setw(8) << hash;
	} while (hexHash.str().substr(0, difficulty) != sDifficulty);

	// Save the hash.
	sHash = std::to_string(hash);

#ifdef _DEBUG
	// Debug output.
	std::cout << "Block mined: " << sHash << ", " << nonce << std::endl;
#endif
}

time_t Block::timeStamp() const { return std::time(0); }
