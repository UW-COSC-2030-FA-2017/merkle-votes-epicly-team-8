#include <stdio.h>
#include "pMT.h"
#include <iostream>
#include<fstream>
using namespace std;

int main(int argc, char **argv)
{
	// ------------------Tests for bTREE------------------
	/*bTREE bt;

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
		cout << "Trees different" << endl;*/

	// ------------------Tests for pMT------------------
	ifstream inFile;
	pMT m1(1);
	pMT m2(2);
	pMT m3(3);

	inFile.open("mv_test.txt");
	if (inFile.is_open())
	{
		string vote, time;
		// skip the first line
		getline(inFile, vote);
		while (!inFile.eof())
		{
			getline(inFile, vote, '\t');
			getline(inFile, time);
			m1.insert(vote, atoi(time.c_str()));
			m2.insert(vote, atoi(time.c_str()));
			m3.insert(vote, atoi(time.c_str()));	
		}
		// Read in a file and output the value of the root node
		cout << "\n--------------Using First Vote File--------------" << endl;
		cout << "Root node for first hash: " << m1.getRootNode() << endl;
		cout << "Root node for second hash: " << m2.getRootNode() << endl;
		cout << "Root node for third hash: " << m3.getRootNode() << endl;

		// Compare vote files
		ifstream inFile2;
		pMT m4(1);
		pMT m5(2);
		pMT m6(3);

		inFile2.open("mv_test2.txt");
		if (inFile2.is_open())
		{
			string vote, time;
			// skip the first line
			getline(inFile2, vote);
			while (!inFile2.eof())
			{
				getline(inFile2, vote, '\t');
				getline(inFile2, time);
				m4.insert(vote, atoi(time.c_str()));
				m5.insert(vote, atoi(time.c_str()));
				m6.insert(vote, atoi(time.c_str()));
			}
			// Read in a file and output the value of the root node
			cout << "\n--------------Using Second Vote File--------------" << endl;
			cout << "Root node for first hash: " << m4.getRootNode() << endl;
			cout << "Root node for second hash: " << m5.getRootNode() << endl;
			cout << "Root node for third hash: " << m6.getRootNode() << endl;

			// Compare two identical vote files
			cout << "\n--------------Using  First Hash Function--------------" << endl;
			m4.print_dif(m1);
			cout << "\n--------------Using Second Hash Function--------------" << endl;
			m5.print_dif(m2);
			cout << "\n--------------Using  Third Hash Function--------------" << endl;
			m6.print_dif(m3);
		}
		else
		{
			cerr << "File could not be opened!" << endl;
		}

		inFile2.close();

		// Compare vote files
		ifstream inFile3;
		pMT m7(1);
		pMT m8(2);
		pMT m9(3);

		inFile3.open("mv_test3.txt");
		if (inFile3.is_open())
		{
			string vote, time;
			// skip the first line
			getline(inFile3, vote);
			while (!inFile3.eof())
			{
				getline(inFile3, vote, '\t');
				getline(inFile3, time);
				m7.insert(vote, atoi(time.c_str()));
				m8.insert(vote, atoi(time.c_str()));
				m9.insert(vote, atoi(time.c_str()));
			}
			// Read in a file and output the value of the root node
			cout << "\n--------------Using Third Vote File--------------" << endl;
			cout << "Root node for first hash: " << m7.getRootNode() << endl;
			cout << "Root node for second hash: " << m8.getRootNode() << endl;
			cout << "Root node for third hash: " << m9.getRootNode() << endl;

			// Compare two differing vote files
			cout << "\n--------------Using  First Hash Function--------------" << endl;
			m7.print_dif(m1);
			cout << "\n--------------Using Second Hash Function--------------" << endl;
			m8.print_dif(m2);
			cout << "\n--------------Using  Third Hash Function--------------" << endl;
			m9.print_dif(m3);
		}
		else
		{
			cerr << "File could not be opened!" << endl;
		}

		inFile3.close();

		/* Statistics */
		/*
		cout << endl << endl << "_______________Statistics on m1_______________" << endl;
		cout << "Number of nodes: \t" << m1.numberOfNodes() << endl;
		cout << "Number of leaves: \t" << m1.dataInserted() << endl;
		cout << "Operations to insert: \t" << m1.insert("1333CB31EC:Candidate2", 44) << endl;
		cout << "Hashes needed to recompute: " << (m1.numberOfNodes() - m1.dataInserted()) << endl;
		*/


		/*** Merkle Tree tests
		cout << "\n--------------Using  First Hash Function--------------" << endl;
 		cout << m1 << endl;
		cout << "\n--------------Using Second Hash Function--------------" << endl;
		cout << m2 << endl;
		cout << "\n--------------Using  Third Hash Function--------------" << endl;
		cout << m3 << endl;

		cout << "Trying to find vote - 15D2CBA1EC:Candidate2" << endl;
		int m1f = m1.find("15D2CBA1EC:Candidate2", 4, 1);
		int m2f = m1.find("15D2CBA1EC:Candidate2", 4, 1);
		int m3f = m1.find("15D2CBA1EC:Candidate2", 4, 1);
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

		cout << "Trying to find vote - 15D2CBA1EE:Candidate2" << endl;
		m1f = m1.find("15D2CBA1EE:Candidate2", 4, 1);
		m2f = m1.find("15D2CBA1EE:Candidate2", 4, 1);
		m3f = m1.find("15D2CBA1EE:Candidate2", 4, 1);
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
		cout << "\tNumber of operations to find (0 if not found): " << m1.findHash("76DA28B6") << endl;
		cout << "\tNumber of operations to find (0 if not found): " << m2.findHash("94D7A914") << endl;
		cout << "\tNumber of operations to find (0 if not found): " << m3.findHash("8C341A4C") << endl;

		cout << "\nTrying to find hashes that do NOT exist" << endl;
		cout << "\tNumber of operations to find (0 if not found): " << m1.findHash("76DA28B2") << endl;
		cout << "\tNumber of operations to find (0 if not found): " << m2.findHash("94D7A913") << endl;
		cout << "\tNumber of operations to find (0 if not found): " << m3.findHash("8C341A43") << endl;

		cout << "\nTrying to find locations of '15D2CBA1EC:Candidate2'" << endl;
		cout << "\tL R moves to find: " << m1.locateData("15D2CBA1EC:Candidate2") << endl;
		cout << "\tL R moves to find: " << m2.locateData("15D2CBA1EC:Candidate2") << endl;
		cout << "\tL R moves to find: " << m3.locateData("15D2CBA1EC:Candidate2") << endl;

		cout << "\nTrying to find locations of '15D2CBA1EE:Candidate4'" << endl;
		cout << "\tL R moves to find: " << m1.locateData("15D2CBA1EE:Candidate4") << endl;
		cout << "\tL R moves to find: " << m2.locateData("15D2CBA1EE:Candidate4") << endl;
		cout << "\tL R moves to find: " << m3.locateData("15D2CBA1EE:Candidate4") << endl;

		cout << "\nTrying to find locations of hashes that do exist" << endl;
		cout << "\tL R moves to find: " << m1.locateHash("76DA28B6") << endl;
		cout << "\tL R moves to find: " << m2.locateHash("94D7A914") << endl;
		cout << "\tL R moves to find: " << m3.locateHash("8C341A4C") << endl;

		cout << "\nTrying to find locations of hashes that do NOT exist" << endl;
		cout << "\tL R moves to find: " << m1.locateHash("76DA28B2") << endl;
		cout << "\tL R moves to find: " << m2.locateHash("94D7A913") << endl;
		cout << "\tL R moves to find: " << m3.locateHash("8C341A43") << endl;*/
	}
	else
	{
		cerr << "File could not be opened!" << endl;
	}

	inFile.close();

	return 0;
}
