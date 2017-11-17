#include "pMT.h"

pMT::pMT(int hashSelect)
/**
 * @brief 
 * @param hashSelect a number corresponding to the hashfunction to use for this pMT
 * @return 
 */
{
	selectedHash = hashSelect;
}

pMT::~pMT()
/**
 * @brief destructor
 * @return nada
 */
{
	
}

int pMT::insert(string vote, int time)
/**
 * @brief insert a vote and time into a leaf node of tree
 * @param vote - a string
 * @param time - an int representing the time 
 * @return the number of operations needed to do the insert, -1 if out of memory
 */
{	
	int operations = 0;
	// So every leaf is connected through a doubly-linked list
	// When we insert a new data node (leaf) as part of the Merkle tree,
	// the new node will be inserted by looking through these leaves until
	// a leaf has a higher timestamp than it does. This leaf is the
	// new leaf's 'partner.' Create a mutual parent between the new node 
	// and its partner using their hashes, and update the parent heirarchy
	// The new leaf should now be connected to the doubly-linked leaf list 
	// through its partner's previous and next pointers.

	// if the tree is empty
	if (numberOfNodes() == 0)
	{
		insert(vote, time);

		return 1;
	}

	// set the partner node
	treeNode *partner = headLeaf;
	while (time < partner->time && partner->nextLeaf != NULL)
	{
		partner = partner->nextLeaf;
		operations++;
	}
	treeNode *newNode = new treeNode(time, vote, true, NULL, NULL, NULL, NULL, NULL);
	treeNode *hashParent;

	// Set the hash string for the parent
	string hash;
	if (selectedHash == 1)
	{
		hash = hash_1(vote) + hash_1(partner->data);
	}
	else if (selectedHash == 2)
	{
		hash = hash_2(vote) + hash_2(partner->data);
	}
	else
	{
		hash = hash_3(vote) + hash_3(partner->data);
	}

	// set the parent node
	if (partner->time > time)
	{
		// partner is right child
		hashParent = new treeNode(0, hash, false, newNode, partner, partner->parent, NULL, NULL);
		newNode->nextLeaf = partner;
		if(partner->prevLeaf != NULL) newNode->prevLeaf = partner->prevLeaf;
		partner->prevLeaf = newNode;
	}
	else
	{
		// partner is left child
		hashParent = new treeNode(0, hash, false, partner, newNode, partner->parent, NULL, NULL);
		newNode->prevLeaf = partner;
		if (partner->nextLeaf != NULL) newNode->nextLeaf = partner->nextLeaf;
		partner->nextLeaf = newNode;
	}
	// set the child parents to the parent
	newNode->parent = hashParent;
	partner->parent = hashParent;
	
	// Reset the headLeaf if needed
	if (partner == headLeaf)
	{
		headLeaf = newNode;
	}

	// Update the parent heirarchy
	treeNode *temp = hashParent;
	while (temp->parent != NULL)
	{
		operations++;
		temp = temp->parent;

		if (selectedHash == 1)
		{
			temp->data = hash_1(temp->left->data) + hash_1(temp->right->data);
		}
		else if (selectedHash == 2)
		{
			temp->data = hash_2(temp->left->data) + hash_2(temp->right->data);
		}
		else
		{
			temp->data = hash_3(temp->left->data) + hash_3(temp->right->data);
		}
	}

	return operations;
}

int pMT::find(string vote, int time, int hashSelect)
/**
 * @brief given a vote, timestamp, and hash function, does this vote exist in the tree?
 * @param vote, a string
 * @param time, an int
 * @param hashSelect, an int corresponding to the hash functions _1, _2, and _3
 * @return 0 if not found, else number of opperations required to find the matching vote
 */
{
	return 1;
}

int pMT::findHash(string mhash)
/**
 * @brief does this hash exist in the tree?
 * @param mhash, a string to search for in the tree
 * @return 0 if not found, else number of opperations required to find the matching hash
 */
{
	return 1;
}


string pMT::locateData(string vote)
/**
 * @brief Function takes a hash of Vote and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root. 
 * @param vote, the data to search for 
 * @return sequence of L's and R's comprising the movement to the leaf node; else return a dot '.'
 */
{
	return "something";
}

string pMT::locateHash(string mhash)
/**
 * @brief Function takes a hash and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root. 
 * @param mhash, the hash to search for 
 * @return sequence of L's and R's comprising the movement to the hash node, ; else return a dot '.'
 */
{
	return "something";
}



// Arash Partow's DJB Hash Function edited to return a hex string
string pMT::hash_1(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	unsigned int hash = 15485863;
	unsigned int i = 0;
	unsigned int length = key.length();
	const char* str = key.c_str();

	// for every character of the string
	for (i = 0; i < length; i++, str++)
	{
		// add the hash to itself shifted five bits leftward, then add
		// the ith character of the string
		// this is the new hash
		hash = ((hash << 5) + hash) + (*str);
	}

	return intToHex(hash);
}

string pMT::hash_2(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	return "something";
}

// Arash Partow's RS Hash edited to return a hex string
string pMT::hash_3(string key)
/**
* @brief A function that takes in a key and returns a hash of that key using some custom function
* @param key, a string
* @return a hash of the key
*/
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
	unsigned int i = 0;
	unsigned int length = key.length();
	const char* str = key.c_str();

	// for every character of the string
	for (i = 0; i < length; i++, str++)
	{
		// take the hash, multiply it by a number, and add
		// the ith character of the string
		// this is the new hash
		hash = hash * a + (*str);
		// change the hash-multiplier to itself multiplied by a prime
		a = a * b;
	}

	return intToHex(hash);
}

// Convert the input integer to a hex string
string pMT::intToHex(int i)
{
	char* digits = "0123456789ABCDEF";
	string s = "";
	int temp = i;

	do
	{
		s.insert(s.begin(), digits[temp % 16]);
		temp = temp / 16;
	} while (temp != 0);
	return s;
}

// Convert the input hex string to an integer
int pMT::hexToInt(string s)
{
	const char *str = s.c_str();
	unsigned int result = 0;

	for (int i = 0; i < s.length(); i++)
	{
		if (str[i] == '0') result += 0;
		else if (str[i] == '1') result += 1 * pow(16, s.length() - 1 - i);
		else if (str[i] == '2') result += 2 * pow(16, s.length() - 1 - i);
		else if (str[i] == '3') result += 3 * pow(16, s.length() - 1 - i);
		else if (str[i] == '4') result += 4 * pow(16, s.length() - 1 - i);
		else if (str[i] == '5') result += 5 * pow(16, s.length() - 1 - i);
		else if (str[i] == '6') result += 6 * pow(16, s.length() - 1 - i);
		else if (str[i] == '7') result += 7 * pow(16, s.length() - 1 - i);
		else if (str[i] == '8') result += 8 * pow(16, s.length() - 1 - i);
		else if (str[i] == '9') result += 9 * pow(16, s.length() - 1 - i);
		else if (str[i] == 'A') result += 10 * pow(16, s.length() - 1 - i);
		else if (str[i] == 'B') result += 11 * pow(16, s.length() - 1 - i);
		else if (str[i] == 'C') result += 12 * pow(16, s.length() - 1 - i);
		else if (str[i] == 'D') result += 13 * pow(16, s.length() - 1 - i);
		else if (str[i] == 'E') result += 14 * pow(16, s.length() - 1 - i);
		else if (str[i] == 'F') result += 15 * pow(16, s.length() - 1 - i);
	}

	return result;
}

//			friend bool pMT::operator ==(const pMT& lhs, const pMT& rhs)
			/**
			 * @brief Comparison between two merkle trees
			 * @param lhs, the left hand side of the equality statment
			 * @param rhs, the right hand side of the equality statement
			 * @return true if equal, false otherwise
			 */
//			{
//			}

//			friend bool pMT::operator !=(const pMT& lhs, const pMT& rhs)
			/**
			 * @brief Comparison between two merkle trees
			 * @param lhs, the left hand side of the equality statment
			 * @param rhs, the right hand side of the equality statement
			 * @return true if not equal, false otherwise
			 */
//			{
    
//			}

//			friend pMT pMT::operator ^=(const pMT& lhs, const pMT& rhs)
			/**
			 * @brief XOR between two merkle trees
			 * @param lhs, the left hand side of the equality statment
			 * @param rhs, the right hand side of the equality statement
			 * @return true if not equal, false otherwise
			 */
//			{
    
//			}


//			friend std::ostream& pMT::operator <<(std::ostream& out, const pMT& p)
			/**
			 * @brief Print out a tree
			 * @param out
			 * @param p
			 * @return a tree to the screen
			 */
//			{
//			}


//			friend pMT pMT::operator ^(const pMT& lhs, const pMT& rhs)
			/**
			 * @brief Where do two trees differ
			 * @param lhs
			 * @param rhs
			 * @return a tree comprised of the right hand side tree nodes that are different from the left
			 */
//			{
//			}
