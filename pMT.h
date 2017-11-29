// pMT.h
// Robert Randolph & Mckade Umbenhower
// COSC 2030, Section 01
// Merkle_Votes_HW
// December 01, 2017

#ifndef PMT_H
#define PMT_H

#include <string>	// string
#include "bTREE.h"	// bTREE

using std::string;

class pMT : public bTREE
{
private:
    int selectedHash;
    
	// Hashs done by McKade
    string hash_1(string);
	string hash_2(string);
	// Hash done by Robert
	string hash_3(string);
	// Helper conversion functions
	string intToHex(long unsigned int i);
	int hexToInt(string s);

	//	Helper Function to print out the nodes of a passed in subtree
	void print_dif(const treeNode *);
    
public:
    pMT(int);
    ~pMT();    
    
	// Insert a node into the merkle tree.
    int insert(string, int);
    
	// Find a node in the merkle tree.
    int find(string vote, int time, int hashSelect);
	// Find a hash in the merkle tree.
    int findHash(string);
    
	// Find the L/R moves needed to get to the given string
    string locateData(string);
	// Find the L/R moves needed to get to the given hash
	string locateHash(string mhash);

	// Return the data of the root node.
	string getRootNode( void );

	// Prints out nodes in current tree that differ from passed tree.
	void print_dif(const pMT &);
	// Prints out data nodes in current tree that differ from passed tree.
	void print_difData(const pMT &);
    
	friend pMT operator^(const pMT& lhs, const pMT& rhs);
    friend bool operator==(const pMT& lhs, const pMT& rhs);
    friend bool operator!=(const pMT& lhs, const pMT& rhs);

    friend std::ostream& operator<<(std::ostream& out, const pMT& p);
};

#endif // !PMT_H
