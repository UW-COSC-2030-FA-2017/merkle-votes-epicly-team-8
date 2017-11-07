#pragma once
#include <string>
using namespace std;

class bTREE
{
    struct treeNode{
		treeNode(int itime = 0, string idata = "Data", bool ileaf = false,
			treeNode *ileft = NULL, treeNode *iright = NULL)
			: time(itime), data(idata), leaf(ileaf), left(ileft), right(iright) {}

        int time;
		string data;
		bool leaf;

		treeNode *left;
		treeNode *right;
    };
    
private:
    //some data structure to hold your treeNodes together ...
    //DATASTUCTURE treeNodes tree;
    //any helper private variables you need
    
public:
    bTREE();
    ~bTREE();
    
    int dataInserted();
    int numberOfNodes();
    
    bool insert(string, int);
    
    bool find(string);
    
    string locate(string);
    
    
    friend bool operator==(const bTREE& lhs, const bTREE& rhs);
    friend bool operator!=(const bTREE& lhs, const bTREE& rhs);

    friend std::ostream& operator<<(std::ostream& out, const bTREE& p);
    
};

