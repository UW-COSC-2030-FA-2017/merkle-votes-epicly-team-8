// bTREE.cpp
// Robert Randolph & Mckade Umbenhower
// COSC 2030, Section 01
// Merkle_Votes_HW
// December 01, 2017

#include "bTREE.h"	// bTREE

// ===Public Function Definitions===

bTREE::bTREE()
{
	tree = NULL;
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

	treeNode *node = new treeNode(time, data, true, NULL, NULL);
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

string bTREE::locate(string idata)
{
	string moves = "";
	return locate(idata, tree, moves);
}

bool operator ==(const bTREE& lhs, const bTREE& rhs)
{
	return lhs.tree == rhs.tree;
}

bool operator !=(const bTREE& lhs, const bTREE& rhs)
{
	return !(lhs.tree == rhs.tree);
}

std::ostream& operator <<(std::ostream& out, const bTREE& itree)
{
	if (itree.tree != NULL) {
		out << itree.tree;
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
		size += numberOfNodes(subtree->left);
		size += numberOfNodes(subtree->right);
	}

	return size;
}

/*	Helper function to insert data nodes.
Returns the number of operations performed */
int bTREE::insert(treeNode *subtree, treeNode *node)
{
	int operations = 0;

	if (subtree == NULL)
	{
		operations++;
		printf("Added on current\n");
		subtree = node;
	}
	else if (node->time > subtree->time)
	{
		if (subtree->right == NULL)
		{
			operations++;
			subtree->right = node;
			subtree->leaf = false;
		}
		else
		{
			operations++;
			insert(subtree->right, node);
		}
	}
	else if (node->time == subtree->time)
	{
		operations++;
		subtree->data = node->data;
	}
	else
	{
		if (subtree->left == NULL)
		{
			operations++;
			subtree->left = node;
			subtree->leaf = false;
		}
		else
		{
			operations++;
			insert(subtree->left, node);
		}
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
			operations += find(idata, subtree->left, found, false);
			operations += find(idata, subtree->right, found, false);
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