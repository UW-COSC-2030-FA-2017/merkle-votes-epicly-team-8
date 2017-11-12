// bTREE.h
// Robert Randolph & Mckade Umbenhower
// COSC 2030, Section 01
// Merkle_Votes_HW
// December 01, 2017

#ifndef BTREE_H
#define BTREE_H

#include <string>	// string
#include <vector>	// vector

using std::string;
using std::vector;

class bTREE
{
    struct treeNode {
		treeNode(int itime = 0, string idata = "Data", bool ileaf = false,
			treeNode *ileft = NULL, treeNode *iright = NULL)
			: time(itime), data(idata), leaf(ileaf), left(ileft), right(iright) {}

        int time;
		string data;
		bool leaf;

		treeNode *left;
		treeNode *right;

		friend std::ostream& operator <<(std::ostream& out, const treeNode * subtree)
		{

			/*if (subtree != NULL) {
				out << subtree->left;
				out << "Time: " << subtree->time
					<< " :: Vote: " << subtree->data << '\n';
				out << subtree->right;
			}*/

			return out;
		}
    };

private:
	treeNode *tree;

/*	Helper function to find number of nodes.
	Returns the number of nodes in the tree. */
	static int numberOfNodes(const treeNode *);

/*	Helper function to find wether a node exists in the tree.
	Returns the number of operations to find the node. */
	static int find(const string, const treeNode *, bool &, bool);

/*	Helper function for destructor.
	Destroys all nodes in the tree. */
	static void destroy(treeNode *);

public:
    bTREE();
    ~bTREE();

    int dataInserted();

	// Returns the number of nodes in the tree.
    int numberOfNodes();

    int insert(string, int);

/*	Find whether a node exists in the tree.
	Returns the number of operations to find the node. */
    int find(string);

    string locate(string);


    friend bool operator==(const bTREE& lhs, const bTREE& rhs);
    friend bool operator!=(const bTREE& lhs, const bTREE& rhs);

    friend std::ostream& operator<<(std::ostream& out, const bTREE&);

};

#endif // !BTREE_H
