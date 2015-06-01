#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include <math.h>

#include <windows.h>


using namespace std;

int main() {
	fstream myfile;
	stringstream MyStSt;

	vector < vector<int> > Buffer;
	vector <int> tmp;

	char fname[20];
	int n, l, j;
	string str;
	/*cin >> fname;
	myfile.open(fname);*/
	//system("cd");

	myfile.open("example.txt");
	if (! myfile.is_open()) {
		cout << "Error opening file!" << endl;
		return -1;
	}

	for (j = 0; getline(myfile, str); j++) {
		//cout << str << '\n';

		MyStSt.str(str);
		l = str.length();

		for (int i = 0; i < l; i++) {

			MyStSt >> n;
			tmp.push_back(n);

		}

		Buffer.push_back(tmp);

		cout << Buffer[j][2] << endl;

	}

	//myfile << "Writing this to a file.\n";


	myfile.close();
	return 0;
}