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
		treeNode(int itime, string idata, bool ileaf, treeNode *ileft, treeNode *iright)
			: time(itime), data(idata), leaf(ileaf), left(ileft), right(iright) {}

        int time;
		string data;
		bool leaf;

		treeNode *left;
		treeNode *right;

		bool operator==(const treeNode &rhs)
		{
			if (left == NULL && right == NULL)
			{
				return ((time == rhs.time) && (data == rhs.data) && (leaf == rhs.leaf) &&
					(rhs.left == NULL) && (rhs.right == NULL));
			}
			else if (left == NULL)
			{
				return ((time == rhs.time) && (data == rhs.data) && (leaf == rhs.leaf) &&
					(rhs.left == NULL) && (*right == *rhs.right));
			}
			else if (right == NULL)
			{
				return ((time == rhs.time) && (data == rhs.data) && (leaf == rhs.leaf) &&
					(*left == *rhs.left) && (rhs.right == NULL));
			}
			else
			{
				return ((time == rhs.time) && (data == rhs.data) && (leaf == rhs.leaf) &&
					(*left == *rhs.left) && (*right == *rhs.right));
			}			
		}

		friend std::ostream& operator <<(std::ostream& out, const treeNode * subtree)
		{

			if (subtree != NULL) {
				out << subtree->left;
				out << "Time: " << subtree->time
					<< " :: Vote: " << subtree->data << '\n';
				out << subtree->right;
			}

			return out;
		}
    };

private:
	treeNode *tree;

	/*	Helper function to find number of data nodes.
	Returns the number of data nodes in the tree. */
	int dataInserted(const treeNode *);

/*	Helper function to find number of nodes.
	Returns the number of nodes in the tree. */
	static int numberOfNodes(const treeNode *);

	/*	Helper function to insert data nodes.
	Returns the number of operations performed */
	int insert(treeNode *, treeNode *);

/*	Helper function to find wether a node exists in the tree.
	Returns the number of operations to find the node. */
	static int find(const string, const treeNode *, bool &, bool);

	/*Helper function that returns the sequence of (L)eft and (R)ight 
	moves to get to that node starting from root*/
	string locate(string, const treeNode*, string &moves); 

/*	Helper function for destructor.
	Destroys all nodes in the tree. */
	static void destroy(treeNode *);

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
