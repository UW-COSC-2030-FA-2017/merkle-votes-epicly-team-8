#pragma once

#include "bTREE.h"
#include <string>
using namespace std;
class pMT
{
private:
    int selectedHash;
    bTREE myMerkle;
    
	// Hash done by McKade
    string hash_1(string);
	// Hash done by Robert
    string hash_2(string);
	string hash_3(string);
	// Helper conversion functions
	string intToHex(int i);
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

