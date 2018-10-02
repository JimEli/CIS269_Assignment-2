/*************************************************************************
* Title: Block class
* File: block.h
* Author: James Eli
* Date: 9/21/2018
*
* Blockchain Block Class Declaration.
*
* Declares a block class containing an ID, Time Stamp, Hash, Previous Hash
* and Nonce members. All members are public (?) except the hash and previous
* hash strings. Includes accessors (get/set) for all members. Provides ctors
* (empty, blockchain Genesis and all data ctor). Includes a formatted
* print function.
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
#pragma once
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <cstdint>    // uint32_t
#include <iostream>   // cout
#include <functional> // hash
#include <iomanip>    // hex conversion manipulators
#include <sstream>    // string conversion
#include <string>     // c++ strings
#include <cstring>    // strlen
#include <ctime>      // time()

// Difficulty level for mining.
const unsigned int DIFFICULTY = 2;

namespace myBlock {

	//template <typename T>
	class Block
	{
	public:
		// Ctors.
		Block() = default;
		Block(const unsigned long);
		Block(const unsigned long, /* id */
			char*,                 /* hash */
			char*,                 /* previous hash */
			const unsigned long,   /* nonce */
			const time_t           /* time stamp */
		);
		Block(const unsigned long, /* id */
			char*,                 /* previous hash */
			const unsigned long,   /* nonce */
			const time_t           /* time stamp */
		);

		// Dtor.
		~Block() = default;

		// Accessor functions for id number.
		void setID(const unsigned long);
		unsigned long getID() const;

		// Accessor functions for hash.
		void setHash(char*);
		char* getHash() const;

		// Accessor functions for previous hash.
		void setPreviousHash(char *);
		char* getPreviousHash() const;

		// Accessor functions for nonce.
		void setNonce(unsigned long);
		unsigned long getNonce() const;

		// Accessor functions for time stamp.
		void setTimeID(time_t);
		time_t getTimeID() const;

		// Mine blocks.
		void MineBlock(unsigned int);

		// Validate hash value for block.
		bool isHashValid();

		// Print formatted block data.
		friend std::ostream& operator<< (std::ostream& os, const Block& block)
		{
			return os << " Block ID #" << block.getID()
				<< ", Hash: " << block.getHash()
				<< ", Previous Hash: " << block.getPreviousHash()
				<< ", Nonce: " << block.getNonce()
				<< ", Time Stamp: " << block.getTimeID()
				<< std::endl;
		}

	private:
		// Private member data.
		char* hash;                // Hash of current block.
		char* previousHash;        // Hash of previous block.
		unsigned long id;          // Block identification number (id).
		unsigned long nonce;       // Nonce, used in computing hash.
		time_t timeId;             // Timestamp.

		std::string sHash;         // String of hash.
		std::string sPreviousHash; // String of previous hash.
		//T* data;

		// Hash calculation.
		inline uint32_t calcHash() const;

		// Sets time stamp to now (seconds past Unix epoch).
		time_t timeStamp() const;
	};
}
#endif
