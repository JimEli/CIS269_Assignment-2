/*************************************************************************
* Title: Blockchain class
* File: blockchain.h
* Author: James Eli
* Date: 9/21/2018
*
* Blockchain Class.
*
* Create and mine blocks.
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
#ifndef _BLOCKCHAIN_H_
#define _BLOCKCHAIN_H_

#include "Block.h"
#include "list.h"

using namespace myBlock;
using namespace myList;

namespace myBlockchain
{
	class Blockchain
	{
	public:
		// Create genesis block.
		Blockchain() { chain.push_back(Block(0)); }
		~Blockchain() = default;

		// Add new block to chain.
		void addBlock(Block newBlock)
		{
			newBlock.setPreviousHash(getPreviousBlock().getHash());
			newBlock.MineBlock(DIFFICULTY);
			chain.push_back(newBlock);
		}

		// Print entire chain.
		void walkChain() const { std::cout << chain; }

	private:
		// Retrieve previous block in chain.
		Block getPreviousBlock() const { return chain.back(); }

		// Blackchain is a singly-linked list.
		list<Block> chain;
	};
}
#endif
