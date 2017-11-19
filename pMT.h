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

class pMT : private bTREE
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
	
    
public:
    pMT(int);
    ~pMT();    
    
    int insert(string, int);
    
    int find(string vote, int time, int hashSelect);
    int findHash(string);
    
    string locateData(string);
	string locateHash(string mhash);
    
    friend bool operator==(const pMT& lhs, const pMT& rhs);
    friend bool operator!=(const pMT& lhs, const pMT& rhs);

    friend pMT operator^(const pMT& lhs, const pMT& rhs);

    friend std::ostream& operator<<(std::ostream& out, const pMT& p);
};

#endif // !PMT_H
