#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdio>

#include <boost/heap/priority_queue.hpp>

#include <math.h>

#include <windows.h>

using namespace std;
using namespace boost::heap;

bool myVecCmp(vector <int> & i, vector <int> & j) { 
	return (i < j);
}

struct item {
	int id;
	int f;
	int d;
	int level;
};




int main() {
	fstream myfile;
	stringstream MyStSt;

	vector < vector<int> > Buffer;
	vector < struct item > Trie;

	vector <int> tmp;

	char fname[20];
	int n, l, j;
	int bSize, curSize;
	string str;
	/*cin >> fname;
	myfile.open(fname);*/
	//system("cd");

	myfile.open("example.txt");
	if (!myfile.is_open()) {
		cout << "Error opening file!" << endl;
		return -1;
	}

	for (j = 0; getline(myfile, str); j++) {
		//cout << str << '\n';
		MyStSt.clear();
		MyStSt.str(str);

		std::string tt = MyStSt.str();

		tmp.clear();

		while (MyStSt >> n) {		
			tmp.push_back(n);
		}

		Buffer.push_back(tmp);

		cout << str << endl;
		//cout << "aaf" << endl;

		if (j > 20) {
			j = 0;


			cout << "11 < 22" << endl;

			1 + 1;
			sort(Buffer.begin(), Buffer.end(), myVecCmp);

			bSize = Buffer.size();
			for (int k = 0; k < bSize; k++) {
				curSize = Buffer[k].size();
				for (int z = 0; z < curSize; z++)
					cout << Buffer[k][z] << " ";

				cout << endl;
			}



			Buffer.clear();
			getchar();
		}

	}
	//myfile.close();
	//myfile << "Writing this to a file.\n";
	cout << "aaf" << endl;

	getchar();

	return 0;
}