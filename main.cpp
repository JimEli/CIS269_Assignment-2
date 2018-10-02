/*************************************************************************
* Title: Blockchain Driver (CIS-269 Assignment #2)
* File: main.cpp
* Author: James Eli
* Date: 9/21/2018
*
* Blockchain Class Driver Program. Tests our blockchain.
*
* Part 1 Static Memory Allocation (60 pts)
*   Make class that includes the properties:
*   - public long id;
*   - public char* hash;
*   - public char* previousHash;
*   - public long nonce;
*   - public long timeId;
*   Methods:
*   - 3 constructors (empty, all properties, a constructor that takes in id,
*     previousHash, nonce, and timeID and generates the hash using a function).
*   - public getters and setters for all the properties.
*   - generate hash (example in class, take the previousHash value and
*     concatenate with nonce to get hash value).
*  The driver should make a static array containing 5 or more static blocks.
*
* Part 2 Dynamic Memory Allocation (25 pts):
*   Modify your code so you dynamically allocate memory for the block data type
*   array of 5 elements.
*
* Part 3 Pointer Adjustment (15 pts):
*   Create a new dynamic array of 6 elements and move the pointer to the new
*   array and add a block type class to the last element of the new array.
*
* Notes:
*  (1) There is no specialization for C strings with std::hash<const char*>.
*      This produces a hash of the value of the pointer (the memory address).
*  (2) Hash returns std:size_t, so it’s a 32-bit value on a 32-bit system, and
*      a 64-bit value on a 64-bit system.
*  (3) Consider per the instructions, the Block parameters are all public (?)
*      And hash and previousHash are returned as char* in accessor functions.
*      This exposes the member data to tampering, and seems to violate the
*      most basic principles of OOP.
*  (4) I’m not sure I understand the purpose of an all-member constructor.
*      Why allow creation of a Block with user supplied data (hash, time stamp, 
*      etc)? If our block chain is for a crypto-currency, this seems
*      to expose it to counterfeiting.
*  (5) Compiled/tested with MS Visual Studio 2017 Community (v141), and
*      Windows SDK version 10.0.17134.0 (32 & 64-bit).
*  (6) Compiled/tested with Eclipse Oxygen.3a Release (4.7.3a), using
*      CDT 9.4.3 and MinGw32 gcc-g++ (6.3.0-1).
*
* Submitted in partial fulfillment of the requirements of PCC CIS-269.
*************************************************************************
* Change Log:
*   09/21/2018: Initial release. JME
*************************************************************************/
#include <iostream>  // cout
#include <cassert>   // assert
#include <algorithm> // min
#include <memory>    // unique pointer
#include <string>    // to_string
#include <ctime>     // time for random seed
#include <random>    // random

#include "block.h"
#include "Blockchain.h"

using namespace std;
using namespace myBlock;
using namespace myBlockchain;

// Array size for demonstration.
const int ARRAY_SIZE = 5;

// Grow dynamic array size +1.
template <typename T>
void grow(T* &oldArray, std::size_t &size)
{
	// Validate parameters.
	assert(oldArray && size);

	// In the rare event of bad_alloc exception, pass up to caller.
	T *newArray = new T[size + 1];

	// Copy original elements to new array.
	std::copy(oldArray, oldArray + size, newArray);

	// Reset original data.
	size += 1;
	delete[] oldArray;
	oldArray = newArray;
}

int main()
{
	// Lambda random number generator 0-9999. Used to generate nonces for demo.
	auto rng = []()->int { return int(10000 * rand() / (RAND_MAX + 1.0)); };
	// Seed the rng.
	srand((unsigned)time(0));

	// Catch exceptions (array out_of_range, bad_alloc).
	try
	{
		// Part 1 Static Memory Allocation.
		// Make a static array containing 5 or more static blocks.
		cout << "Static array of blocks:\n";
		Block staticArray[ARRAY_SIZE];

		// Use time as previous hash for genesis block.
		std::string seed = std::to_string(time(0));
		for (int i = 0; i < ARRAY_SIZE; i++)
			cout << (staticArray[i] = Block(i + 1, (i ? staticArray[i - 1].getHash() : (char*)seed.c_str()), rng(), time(0)));

		// Part 2 Dynamic Memory Allocation.
		// Dynamically allocate memory for the block data type array of 5 elements.
		cout << "Dynamic array of blocks:\n";
		Block *dynArray = new Block[ARRAY_SIZE];

		// Fill array and display.
		std::copy(staticArray, staticArray + ARRAY_SIZE, dynArray);
		for (int i = 0; i < ARRAY_SIZE; i++)
			cout << dynArray[i];

		// Part 3 Pointer Adjustment.
		// Create a new dynamic array of 6 elements and move the pointer to the new
		// array and add a block type class to the last element of the new array.
		cout << "Dynamic array increased by 1:\n";
		std::size_t size = ARRAY_SIZE;
		grow(dynArray, size);
		cout << (dynArray[ARRAY_SIZE] = Block(static_cast<unsigned long>(size), staticArray[ARRAY_SIZE - 1].getHash(), rng(), time(0)));

		// Return memory to heap.
		delete[] dynArray;

#if 0	// Extra section not compiled.

		// Part 4 Smart pointer version.
		// Dynamically allocate array of 5 block elements using a smart pointer.
		cout << "Smart Pointer array of blocks:\n";
		size = ARRAY_SIZE;
		std::unique_ptr<Block[]> spArray = std::make_unique<Block[]>(size);
		for (unsigned i = 0; i < size; i++)
			cout << (spArray[i] = staticArray[i]);

		// Create a new dynamic array of 6 elements and move the pointer to the new
		// array and add a block type class to the last element of the new array.
		cout << "Smart Pointer array increased by 1:\n";
		std::unique_ptr<Block[]> spTemp(static_cast<Block*>(spArray.release()));
		std::size_t newSize = size + 1;
		spArray.reset(new Block[newSize]);
		for (unsigned i = 0; i < std::min(size, newSize); i++)
			spArray[i] = spTemp[i];
		cout << (spArray[size] = Block(newSize, spArray[size - 1].getHash(), 0, time(0)));

		// Part 5 Create a blockchain.
		Blockchain bChain = Blockchain();

		cout << "Mining blocks...\n";
		for (int i = 1; i < 3; i++)
			bChain.addBlock(Block(i));

		bChain.walkChain();

#endif	// Extra section end.

	}
	catch (std::exception& e)
	{
		// Report exception and exit with failure code.
		std::cout << "Encountered exception: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	return 0;
}