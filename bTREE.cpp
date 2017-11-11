// bTREE.cpp
// Robert Randolph & Mckade U.
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

int bTREE::dataInserted()
{
	return 0;
}

// Returns the number of nodes in the tree.
int bTREE::numberOfNodes()
{
	return numberOfNodes(tree);
}

int bTREE::insert(string data, int time)
{
	return 0;
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
	return "";
}

bool operator ==(const bTREE& lhs, const bTREE& rhs)
{
	bool result(false);

	return result;
}

bool operator !=(const bTREE& lhs, const bTREE& rhs)
{
	return false;
}

std::ostream& operator <<(std::ostream& out, const bTREE& itree)
{
	if (itree.tree != NULL) {
		out << itree.tree;
	}

	return out;
}

// ===Private Function Definitions===

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

/*	Helper function for destructor.
	Destroys all nodes in the tree. */
void bTREE::destroy(treeNode * subtree)
{
	if (subtree != NULL) {
		destroy(subtree->left);
		destroy(subtree->right);
		delete subtree;
		subtree = NULL;
	}

	return;
}