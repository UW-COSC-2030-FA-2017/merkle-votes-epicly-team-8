#include <stdio.h>
#include "pMT.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
	bTREE bt;

	cout << "The tree has " << bt.dataInserted() << " leaf nodes and " << bt.numberOfNodes() << " total nodes." << endl;
	bt.insert("a", 5);
	bt.insert("b", 4);
	bt.insert("c", 6);
	bt.insert("d", 3);
	bt.insert("e", 8);
	bt.insert("k", 7);
	bt.insert("f", 2);
	bt.insert("g", 5);
	cout << bt << endl;
	cout << "The tree has " << bt.dataInserted() << " leaf nodes and ";
	cout << bt.numberOfNodes() << " total nodes." << endl;
	cout << "location of 'k': " << bt.locate("k") << endl;

	bTREE bt2, bt3;
	bt2.insert("s", 4);
	bt3.insert("s", 4);
	
	if (bt2 == bt3)
		cout << "Trees the same" << endl;
	bt3.insert("n", 55);
	if (bt3 != bt2)
		cout << "Trees different" << endl;

	return 0;
}
