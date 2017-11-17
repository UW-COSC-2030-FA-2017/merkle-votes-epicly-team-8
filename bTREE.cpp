// bTREE.cpp
// Robert Randolph & Mckade Umbenhower
// COSC 2030, Section 01
// Merkle_Votes_HW
// December 01, 2017

#include <algorithm>	// sort
#include "bTREE.h"		// bTREE
#include <queue>

using std::sort;

// ===Public Function Definitions===

bTREE::bTREE()
{
	tree = NULL;
	headLeaf = NULL;
}

bTREE::~bTREE()
{
	destroy(tree);
}

// Returns the number of leaf nodes (the "data" nodes in a Merkle tree)
int bTREE::dataInserted()
{
	return dataInserted(tree);
}

// Returns the number of nodes in the tree.
int bTREE::numberOfNodes()
{
	return numberOfNodes(tree);
}

// Inserts a node ordered by time
int bTREE::insert(string data, int time)
{
	int operations = 0;

	treeNode *node = new treeNode(time, data, true, NULL, NULL, NULL, NULL, NULL);
	if (tree == NULL)
	{
		tree = node;
		return 1;
	}

	return insert(tree, node);
}

/*	Find whether a node exists in the tree.
	Returns the number of operations to find the node. */
int bTREE::find(string idata)
{
	bool found(false);
	return find(idata, tree, found, true);
}

// Returns the sequence of (L)eft and (R)ight moves to get to given node starting from root.
string bTREE::locate(string idata)
{
	string moves = "";
	return locate(idata, tree, moves);
}

// Returns true if the data in two trees are the same and false otherwise.
bool operator ==(const bTREE& lhs, const bTREE& rhs)
{
	bool result(true);
	vector<string> left_data = lhs.get_data();
	vector<string> right_data = rhs.get_data();

	if (left_data.size() != right_data.size()) result = false;
	else {
		sort(left_data.begin(), left_data.end());
		sort(right_data.begin(), right_data.end());
		for (int i(0); i < left_data.size(); i++) {
			if (left_data[i] != right_data[i]) {
				result = false;
				i = left_data.size() - 1;
			}
		}
	}

	return result;
}

// Returns true if the data in two trees are NOT the same and false otherwise.
bool operator !=(const bTREE& lhs, const bTREE& rhs)
{
	return !(lhs == rhs);
}

// Prints out all the times and votes of a tree.
std::ostream& operator <<(std::ostream& out, const bTREE& itree)
{
	vector<int> tree_time = itree.get_time();
	vector<string> tree_data = itree.get_data();

	for (int i(0); i < tree_time.size(); i++) {
		out << "Time: " << tree_time[i]
			<< " :: Vote: " << tree_data[i] << '\n';
	}

	return out;
}

// ===Private Function Definitions===

/*	Helper function to find number of data nodes.
Returns the number of data nodes in the tree. */
int bTREE::dataInserted(const treeNode *subtree)
{
	int count = 0;

	// If the tree doesn't exist, return 0
	if (subtree == NULL)
	{
		return count;
	}

	// If the tree has no children, add 1 to count
	if (subtree->left == NULL && subtree->right == NULL)
	{
		count++;
	}
	else 
	{
		// Otherwise, the count equals the number of data nodes in the left
		// tree added to the number of data nodes in the right tree
		count += dataInserted(subtree->left) + dataInserted(subtree->right);
	}

	return count;
}

/*	Helper function to find number of nodes.
	Increases size by one as long as the subtree treeNode != NULL */
int bTREE::numberOfNodes(const treeNode * subtree)
{
	int size(0);

	if (subtree != NULL) {
		size++;
		if (subtree->left != NULL) size += numberOfNodes(subtree->left);
		if (subtree->right != NULL) size += numberOfNodes(subtree->right);
	}

	return size;
}

/*	Helper function to insert data nodes.
Returns the number of operations performed */
int bTREE::insert(treeNode *subtree, treeNode *node)
{
	int operations = 0;

	if (tree == NULL)
	{
		tree = node;
		return 1;
	}

	return operations;
}

/*	Helper function to find whether a node exists in the tree.
	Returns the number of operations to find the node.
	Returns 0 if the node doesn't exist. */
int bTREE::find(const string idata, const treeNode * subtree, bool & found, bool root)
{
	int operations(0);

	if (!found && subtree != NULL) {
		operations++;
		if (idata != subtree->data) {
			if(subtree->left != NULL) operations += find(idata, subtree->left, found, false);
			if(subtree->right != NULL) operations += find(idata, subtree->right, found, false);
		}
		else found = true;	// Found that the node exists.

		// Checking if at the root node and whether or not the node was found.
		if (!found && root) {
			operations = 0;
		}
	}

	return operations;
}

/*Helper function that returns the sequence of (L)eft and (R)ight
moves to get to that node starting from root*/
string bTREE::locate(string data, const treeNode* subtree, string &moves)
{
	if (subtree == NULL)
	{
		return ".";
	}
	else if (subtree->data == data)
	{
		return moves = "";
	}
	else
	{
		if (subtree->left != NULL && locate(data, subtree->left, moves) != ".")
		{
			moves = "L" + moves;
		}
		else if (subtree->right != NULL && locate(data, subtree->right, moves) != ".")
		{
			moves = "R" + moves;
		}
		else
		{
			moves = ".";
		}
		return moves;
	}
}

/*	Helper functions for operators == and <<.
	Returns a vector with all the data in the tree. */
vector<string> bTREE::get_data() const
{
	vector<string> tree_data;
	get_data(tree_data, tree);

	return tree_data;
}
void bTREE::get_data(vector<string> & tree_data, const treeNode * subtree) const
{
	if (subtree != NULL) {
		tree_data.push_back(subtree->data);
		if (subtree->left != NULL) get_data(tree_data, subtree->left);
		if (subtree->right != NULL) get_data(tree_data, subtree->right);
	}

	return;
}

/*	Helper functions for operator <<.
	Returns a vector with all the times in the tree. */
vector<int> bTREE::get_time() const
{
	vector<int> tree_time;
	get_time(tree_time, tree);

	return tree_time;
}
void bTREE::get_time(vector<int> & tree_time, const treeNode * subtree) const
{
	if (subtree != NULL) {
		tree_time.push_back(subtree->time);
		if (subtree->left != NULL) get_time(tree_time, subtree->left);
		if (subtree->right != NULL) get_time(tree_time, subtree->right);
	}

	return;
}

/*	Helper function for destructor.
	Destroys all nodes in the tree. */
void bTREE::destroy(treeNode * subtree)
{
	if (subtree != NULL) {
		if(subtree->left != NULL)
			destroy(subtree->left);
		if(subtree->right != NULL)
			destroy(subtree->right);
		delete subtree;
		subtree = NULL;
	}

	return;
}