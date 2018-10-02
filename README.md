
# Pima CC CIS269 
## Assignment #2 
### Static vs. Dynamic Memory Allocation Using Arrays

Blockchain Class Driver Program. Tests our blockchain.

Part 1 Static Memory Allocation (60 pts)
Make class that includes the properties:
* public long id;
* public char* hash;
* public char* previousHash;
* public long nonce;
* public long timeId;

Methods:
* 3 constructors (empty, all properties, a constructor that takes in id,  previousHash, nonce, and timeID and generates the hash using a function).
* public getters and setters for all the properties.
* generate hash (example in class, take the previousHash value and concatenate with nonce to get hash value).
* The driver should make a static array containing 5 or more static blocks.

Part 2 Dynamic Memory Allocation (25 pts):
 Modify your code so you dynamically allocate memory for the block data type  array of 5 elements.

Part 3 Pointer Adjustment (15 pts):
Create a new dynamic array of 6 elements and move the pointer to the new array and add a block type class to the last element of the new array.

Notes:
* There is no specialization for C strings with std::hash<const char*>.  This produces a hash of the value of the pointer (the memory address).
* Hash returns std:size_t, so it’s a 32-bit value on a 32-bit system, and a 64-bit value on a 64-bit system.
* Consider per the instructions, the Block parameters are all public (?).  And hash and previousHash are returned as char* in accessor functions. This exposes the member data to tampering, and seems to violate the most basic principles of OOP.
* I’m not sure I understand the purpose of an all-member constructor. Why allow creation of a Block with user supplied data (hash, time stamp, etc)? If our block chain is for a crypto-currency, this seems to expose it to counterfeiting.
* Compiled/tested with MS Visual Studio 2017 Community (v141), and Windows SDK version 10.0.17134.0 (32 & 64-bit).
* Compiled/tested with Eclipse Oxygen.3a Release (4.7.3a), using CDT 9.4.3 and MinGw32 gcc-g++ (6.3.0-1).
* Submitted in partial fulfillment of the requirements of PCC CIS-269.
