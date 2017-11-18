// bTREE.h
// Robert Randolph & Mckade Umbenhower
// COSC 2030, Section 01
// Merkle_Votes_HW
// December 01, 2017

typedef unsigned int uint;

#ifndef BTREE_H
#define BTREE_H

#include <string>	// string
#include <vector>	// vector

using std::string;
using std::vector;

class bTREE
{
protected:
	struct treeNode {
		treeNode(int itime, string idata, bool ileaf, treeNode *ileft, treeNode *iright, treeNode *iparent, treeNode *inextLeaf, treeNode *iprevLeaf)
			: time(itime), data(idata), leaf(ileaf), left(ileft), right(iright), parent(iparent), nextLeaf(inextLeaf), prevLeaf(iprevLeaf) {}

		int time;
		string data;
		bool leaf;

		treeNode *left;
		treeNode *right;
		treeNode *parent;
		treeNode *nextLeaf;
		treeNode *prevLeaf;
	};
	treeNode *headLeaf;
	treeNode *tree;


	uint size, height;
private:
	/*	Helper function to find number of data nodes.
	Returns the number of data nodes in the tree. */
	int dataInserted(const treeNode *);

/*	Helper function to find number of nodes.
	Returns the number of nodes in the tree. */
	int numberOfNodes(const treeNode *);

	/*	Helper function to insert data nodes.
	Returns the number of operations performed */
	int insert(treeNode *, treeNode *, bool);

/*	Helper function to find wether a node exists in the tree.
	Returns the number of operations to find the node. */
	int find(const string, const treeNode *, bool &, bool);

	/*Helper function that returns the sequence of (L)eft and (R)ight 
	moves to get to that node starting from root*/
	string locate(string, const treeNode*, string &moves); 

/*	Helper functions for operators == and <<.
	Returns a vector with all the data in the tree. */
	vector<string> get_data() const;
	void get_data(vector<string> &, const treeNode *) const;

/*	Helper functions for operator <<.
	Returns a vector with all the times in the tree. */
	vector<int> get_time() const;
	void get_time(vector<int> &, const treeNode *) const;

/*	Helper function for destructor.
	Destroys all nodes in the tree. */
	void destroy(treeNode *);

public:
    bTREE();
    ~bTREE();

	// Returns the total number of data nodes (leaves) inserted in the tree
    int dataInserted();

	// Returns the number of nodes in the tree.
    int numberOfNodes();

	// Inserts a treeNode into the tree
    int insert(string, int);

/*	Find whether a node exists in the tree.
	Returns the number of operations to find the node. */
    int find(string);

	// returns the sequence of (L)eft and (R)ight moves to get to that node starting from root
    string locate(string);

    friend bool operator==(const bTREE& lhs, const bTREE& rhs);
    friend bool operator!=(const bTREE& lhs, const bTREE& rhs);

    friend std::ostream& operator<<(std::ostream& out, const bTREE&);

};

#endif // !BTREE_H
