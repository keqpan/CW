#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue> 
#include <map>
#include <forward_list>
#include <algorithm>
#include <cstdio>

//#include <boost/heap/priority_queue.hpp>

#include <math.h>

#include <windows.h>

using namespace std;
//using namespace boost::heap;

struct itemTr {
	int id;
	int f;
	int d;
	int level;
};

struct item {
	int id;
	struct item * next;
};

bool myVecCmp(const vector <int> & i, const vector <int> & j) { 
	return (i < j);
}

void stFree(struct item * x) {
	struct item * tmp;
	while (x != NULL) {
		tmp = x;
		x = x->next;
		free(tmp);
	}

}


typedef bool(*mapComp)(const struct item &, const struct item &);
bool myMapCmp(const struct item & a, const struct item & b) {
	
	return (a.id > b.id);

}


void addItemToHeap(int x, priority_queue <int> & Heap, map <int, int, mapComp> & Lists) {
	map<int, int, mapComp>::iterator itMap;
}



int main() {
	fstream myfile;
	stringstream MyStSt;

	vector < vector<int> > Buffer;
	vector < struct item > Trie;

	/*bool(*foo)(const struct item &, const struct item &);
	foo = &myQueCmp;*/

	priority_queue <int> Heap;
	map <int, int, mapComp> Lists(myMapCmp);
	//map <int, int, bool(*)(const struct item &, const struct item &)> Lists(myMapCmp); equivalent declaration of map with function pointer


	vector <int> tmp;


	char fname[20];
	int n, l, j;
	int curId;
	struct item * saveNext;
	int bSize, curSize;
	struct item tmpId;
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

		string tt = MyStSt.str();

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

			//sort(Buffer.begin(), Buffer.end(), myVecCmp); there is no necessity to sort transactions
			curId = -1;
			saveNext = NULL;
			bSize = Buffer.size();
			for (int k = 0; k < bSize; k++) {
				curSize = Buffer[k].size();

				addItemToHeap(Buffer[k][0]);

				/*if (Buffer[k][0] == curId) {
					saveNext->next = (struct item *) malloc(sizeof(struct item));
					saveNext = saveNext->next;
					saveNext->id = curId;
					saveNext->next = NULL;
				}
				else {
					if (curId != -1)
						Heap.push(tmpId);

					curId = Buffer[k][0];
					tmpId.id = curId;
					tmpId.next = NULL;
					saveNext = &tmpId;
				}*/
				
				for (int z = 0; z < curSize; z++) { // itemset test output
					cout << Buffer[k][z] << " ";
				}

				cout << endl;
			}	

			if (curId != -1)
				Heap.push(tmpId);

			Heap.top().next = NULL;

			while (!Heap.empty())
			{

				cout << Heap.top().id << endl;
				Heap.pop();
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