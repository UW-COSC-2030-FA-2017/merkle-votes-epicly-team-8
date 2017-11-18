#include <stdio.h>
#include "pMT.h"
#include <iostream>
#include<fstream>
using namespace std;

int main(int argc, char **argv)
{
	// ------------------Tests for bTREE------------------
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

	// ------------------Tests for pMT------------------
	ifstream inFile;
	pMT m1(1);
	pMT m2(2);
	pMT m3(3);

	inFile.open("testFile.txt");
	if (inFile.is_open())
	{
		string vote, time;
		while (!inFile.eof())
		{
			getline(inFile, time, ':');
			getline(inFile, vote);
			m1.insert(vote, atoi(time.c_str()));
			m2.insert(vote, atoi(time.c_str()));
			m3.insert(vote, atoi(time.c_str()));	
		}

		cout << "\n--------------Using  First Hash Function--------------" << endl;
 		cout << m1 << endl;
		cout << "\n--------------Using Second Hash Function--------------" << endl;
		cout << m2 << endl;
		cout << "\n--------------Using  Third Hash Function--------------" << endl;
		cout << m3 << endl;

		cout << "Trying to find vote - 4028858:Lance" << endl;
		int m1f = m1.find("Lance", 4028858, 1);
		int m2f = m1.find("Lance", 4028858, 1);
		int m3f = m1.find("Lance", 4028858, 1);
		if (m1f > 0)
		{
			cout << "\tFound vote in " << m1f << " operations" << endl;
		}
		if (m2f > 0)
		{
			cout << "\tFound vote in " << m2f << " operations" << endl;
		}
		if (m3f > 0)
		{
			cout << "\tFound vote in " << m3f << " operations" << endl;
		}

		cout << "Trying to find vote - 4028857:Lance" << endl;
		m1f = m1.find("Lance", 4028857, 1);
		m2f = m1.find("Lance", 4028857, 1);
		m3f = m1.find("Lance", 4028857, 1);
		if (m1f == 0)
		{
			cout << "\tCouldn't find vote" << endl;
		}
		if (m2f == 0)
		{
			cout << "\tCouldn't find vote" << endl;
		}
		if (m3f == 0)
		{
			cout << "\tCouldn't find vote" << endl;
		}

		cout << "\nTrying to find hashes that do exist" << endl;
		cout << "\tNumber of operations to find (0 if not found): " << m1.findHash("C23D70E2") << endl;
		cout << "\tNumber of operations to find (0 if not found): " << m2.findHash("8370BBE3") << endl;
		cout << "\tNumber of operations to find (0 if not found): " << m3.findHash("114ED347") << endl;

		cout << "\nTrying to find hashes that do NOT exist" << endl;
		cout << "\tNumber of operations to find (0 if not found): " << m1.findHash("C23D00E2") << endl;
		cout << "\tNumber of operations to find (0 if not found): " << m2.findHash("83700BE3") << endl;
		cout << "\tNumber of operations to find (0 if not found): " << m3.findHash("114E0347") << endl;

		cout << "\nTrying to find locations of 'Lance'" << endl;
		cout << "\tL R moves to find: " << m1.locateData("Lance") << endl;
		cout << "\tL R moves to find: " << m2.locateData("Lance") << endl;
		cout << "\tL R moves to find: " << m3.locateData("Lance") << endl;

		cout << "\nTrying to find locations of 'Tyler'" << endl;
		cout << "\tL R moves to find: " << m1.locateData("Tyler") << endl;
		cout << "\tL R moves to find: " << m2.locateData("Tyler") << endl;
		cout << "\tL R moves to find: " << m3.locateData("Tyler") << endl;

		cout << "\nTrying to find locations of hashes that do exist" << endl;
		cout << "\tL R moves to find: " << m1.locateHash("C23D70E2") << endl;
		cout << "\tL R moves to find: " << m2.locateHash("8370BBE3") << endl;
		cout << "\tL R moves to find: " << m3.locateHash("114ED347") << endl;

		cout << "\nTrying to find locations of hashes that do NOT exist" << endl;
		cout << "\tL R moves to find: " << m1.locateHash("C23000E2") << endl;
		cout << "\tL R moves to find: " << m2.locateHash("83700BE3") << endl;
		cout << "\tL R moves to find: " << m3.locateHash("114E0347") << endl;
	}
	else
	{
		cerr << "File could not be opened!" << endl;
	}

	inFile.close();

	return 0;
}
