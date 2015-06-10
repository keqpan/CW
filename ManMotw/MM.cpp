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

struct Item {
	vector<int>::iterator id;
	vector<int>::iterator end;
};

struct mapItem {
	int counts;
	forward_list<struct Item> mapList;
};

bool myVecCmp(const vector <int> & i, const vector <int> & j) { 
	return (i < j);
}


typedef bool(*mapComp)(const struct mapItem &, const struct mapItem &);
bool myMapCmp(const struct mapItem & a, const struct mapItem & b) {
	
	return (*(a.mapList.front().id) > *(b.mapList.front().id));

}


void addItemToHeap(vector<int>::iterator x, vector<int>::iterator end, priority_queue <int> & Heap, map <int, struct mapItem, mapComp> & Lists) {
	map <int, struct mapItem, mapComp>::iterator itMap;
	struct mapItem tmpMapItem;
	struct Item tmpItem;

	itMap = Lists.find(*x);

	if (itMap != Lists.end()) {
		tmpItem.id = x;
		tmpItem.end = end;
		itMap->second.counts++;
		itMap->second.mapList.push_front(tmpItem);
	}
	else {
		Heap.push(*x);
		tmpMapItem.counts = 1;
		tmpItem.id = x;
		tmpItem.end = end;
		tmpMapItem.mapList = forward_list<struct Item>(1, tmpItem);
		Lists.insert(pair<int, struct mapItem>(*x, tmpMapItem));
	}
}

void mySetGen(vector < struct item > * Trie, priority_queue <int> & Heap, map <int, struct mapItem, mapComp> & Lists) {

	Heap

	Lists.clear();
}

int main() {
	fstream myfile;
	stringstream MyStSt;

	vector < vector<int> > Buffer;
	vector < struct item > Trie;

	/*bool(*foo)(const struct item &, const struct item &);
	foo = &myQueCmp;*/

	priority_queue <int> Heap;
	map <int, struct mapItem, mapComp> Lists(myMapCmp);
	//map <int, <int, forward_list<int*>, bool(*)(const struct item &, const struct item &)> Lists(myMapCmp); equivalent declaration of map with function pointer


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

			bSize = Buffer.size();
			for (int k = 0; k < bSize; k++) {
				curSize = Buffer[k].size();

				addItemToHeap(Buffer[k].begin(), Buffer[k].end(), Heap, Lists);

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

			mySetGen(&Trie, Heap, Lists);
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