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
#include <math.h>

using namespace std;
//using namespace boost::heap;

struct itemTr {
	int id;
	int f;
	int d; // error parameter
	int level;
};

struct item {
	vector<int>::iterator id;
	vector<int>::iterator end;
};

struct mapItem {
	int counts;
	forward_list<struct item> mapList;

	~mapItem() {
		mapList.~forward_list();
	}
};

bool myVecCmp(const vector <int> & i, const vector <int> & j) { 
	return (i < j);
}

typedef bool(*queComp)(const int &, const int &);
bool myQueCmp(const int & a, const int & b) {
	return (a > b); //to make min heap
}

void addItemToHeap(vector<int>::iterator x, vector<int>::iterator end, priority_queue <int, vector<int>, queComp> & Heap, map <int, struct mapItem> & Lists) {
	map <int, struct mapItem>::iterator itMap;
	struct mapItem tmpMapItem;
	struct item tmpItem;

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
		tmpMapItem.mapList = forward_list<struct item>(1, tmpItem);
		Lists.insert(pair<int, struct mapItem>(*x, tmpMapItem));
	}
}

void SetGen(vector < struct itemTr > & newNodeTrie, vector < struct itemTr >::iterator nodeTrie, vector < struct itemTr >::iterator end, priority_queue <int, vector<int>, queComp> & Heap, int level, map <int, struct mapItem> & Lists, int b_curr, int b) {
	map <int, struct mapItem>::iterator itMap;

	priority_queue <int, vector<int>, queComp> Heap2(myQueCmp);
	map <int, struct mapItem> Lists2;

	forward_list<struct item>::iterator mapNodes;

	struct itemTr tmp;

	int topId; //top element of the head
	int f, d, l;

	while (!Heap.empty())
	{
		topId = Heap.top();
		itMap = Lists.find(topId);
		cout << topId << endl;


		for (; nodeTrie != end && (*nodeTrie).level < level; nodeTrie++) {
			f = (*nodeTrie).f;
			d = (*nodeTrie).d;
			l = (*nodeTrie).level;

			if (f + d > b_curr) {
				newNodeTrie.push_back(*nodeTrie);
			}

		}
		if (nodeTrie != end && topId == (*nodeTrie).id) {
			f = (*nodeTrie).f + (*itMap).second.counts;
			d = (*nodeTrie).d;

			if (f + d > b_curr) {
				tmp.id = topId;
				tmp.f = f;
				tmp.d = d;
				tmp.level = level;

				newNodeTrie.push_back(tmp);
				nodeTrie++;

				for (mapNodes = (*itMap).second.mapList.begin(); mapNodes != (*itMap).second.mapList.end(); mapNodes++) {
					if ((*mapNodes).id != (*mapNodes).end && (*mapNodes).id + 1 != (*mapNodes).end)
						addItemToHeap((*mapNodes).id + 1, (*mapNodes).end, Heap2, Lists2);
						
				}

				SetGen(newNodeTrie, nodeTrie, end, Heap2, level+1, Lists2, b_curr, b);
				Heap.pop();
			}
		}
		else {
			f = (*itMap).second.counts;
			
			if (f >= b) {
				tmp.id = topId;
				tmp.f = f;
				tmp.d = b_curr - b;
				tmp.level = level;

				newNodeTrie.push_back(tmp);

				for (mapNodes = (*itMap).second.mapList.begin(); mapNodes != (*itMap).second.mapList.end(); mapNodes++) {
					if ((*mapNodes).id != (*mapNodes).end && (*mapNodes).id + 1 != (*mapNodes).end)
						addItemToHeap((*mapNodes).id + 1, (*mapNodes).end, Heap2, Lists2);

				}

				SetGen(newNodeTrie, end, end, Heap2, level + 1, Lists2, b_curr, b);
				Heap.pop();

			}
			else
				Heap.pop();
		}
	}

	Lists.clear();
}

void newRootNode(vector <vector < struct itemTr > > & newTrie, vector < struct itemTr >::iterator nodesTrie, vector < struct itemTr >::iterator end, int b_curr) {
	int f; // frequency of set
	int d; // max error in f
	int l; // level in Trie
	int cur_l;

	vector < struct itemTr > tmp;

	f = (*nodesTrie).f;
	d = (*nodesTrie).d;
	l = (*nodesTrie).level;

	if (f + d > b_curr) {
		tmp.push_back(*nodesTrie);

		nodesTrie++;
		while (nodesTrie != end) {

			f = (*nodesTrie).f;
			d = (*nodesTrie).d;
			l = (*nodesTrie).level;

			if (f + d > b_curr) {
				tmp.push_back(*nodesTrie);
			}
			else {
				for (; nodesTrie != end && (*nodesTrie).level >= l; nodesTrie++);
			}

		}

		newTrie.push_back(tmp);
	}


}

void makeNewTrie(vector <vector < struct itemTr > > & Trie, priority_queue <int, vector<int>, queComp> & Heap, map <int, struct mapItem> & Lists, int b_curr, int b) {
	map <int, struct mapItem>::iterator itMap;
	vector <vector < struct itemTr > >::iterator rootNodesTrie = Trie.begin();
	vector <vector < struct itemTr > >  newTrie;

	vector < struct itemTr > tmp;

	int topHeapId; // top of the Heap
	int f; // frequency of set
	int d; // max error in f

	int trSize = Trie.size();

	while (!Heap.empty())
	{
		topHeapId = Heap.top();
		itMap = Lists.find(topHeapId);
		cout << topHeapId << endl;

		for (; !Trie.empty() && (*rootNodesTrie)[0].id < topHeapId && rootNodesTrie != Trie.end(); rootNodesTrie++) {
			newRootNode(newTrie, (*rootNodesTrie).begin(), (*rootNodesTrie).end(), b_curr);
			(*rootNodesTrie).~vector();
		}

		if (!Trie.empty() && Heap.top() == (*rootNodesTrie)[0].id) {
			f = (*rootNodesTrie)[0].f + (*itMap).second.counts;
			d = (*rootNodesTrie)[0].d;

			if (f + d > b_curr) {
				newTrie.push_back(vector < struct itemTr >());

				SetGen(*(--newTrie.end()), (*rootNodesTrie).begin(), (*rootNodesTrie).end(), Heap, 0, Lists, b_curr, b);
			}
		}
		else {

			f = (*itMap).second.counts;

			if (f >= b) {
				newTrie.push_back(vector < struct itemTr >());

				SetGen(*(--newTrie.end()), tmp.begin(), tmp.begin(), Heap, 0, Lists, b_curr, b);

			}
			else
				Heap.pop();
		}

		//Trie[k].clear();

	}

	Lists.clear();
	Trie = newTrie;
}

void printItemsets(vector <vector < struct itemTr > > & Trie, double s, double eps, int N) {
	vector <vector < struct itemTr > >::iterator rootNodesTrie = Trie.begin();
	vector < struct itemTr >::iterator nodesTrie;

	int arr[100];
	int cur_l = 0;

	ofstream outFile;
	outFile.open("output.txt", ofstream::out | ofstream::trunc);

	for (; rootNodesTrie != Trie.end(); rootNodesTrie++) {
		for (nodesTrie = (*rootNodesTrie).begin(); nodesTrie != (*rootNodesTrie).end();) {
			if ((double)(*nodesTrie).f >= (s - eps)*N) {
				cur_l = (double)(*nodesTrie).level + 1;
				arr[cur_l - 1] = (double)(*nodesTrie).id;
				for (int i = 0; i < cur_l; i++)
					outFile << arr[i] << " ";
				outFile << "\n";

				nodesTrie++;
			}
			else {
				while (nodesTrie != (*rootNodesTrie).end() && (*nodesTrie).level >= cur_l - 1) {
					nodesTrie++;
				}
			}
		}
	}

	outFile << "End of output.\n";
	outFile.close();

}

int main() {
	fstream myfile;
	stringstream MyStSt;

	vector < vector<int> > Buffer;
	vector <vector < struct itemTr > > Trie;

	/*bool(*foo)(const struct item &, const struct item &);
	foo = &myQueCmp;*/

	priority_queue <int, vector<int>, queComp> Heap(myQueCmp);
	map <int, struct mapItem> Lists;
	//map <int, <int, forward_list<int*>, bool(*)(const struct item &, const struct item &)> Lists(myMapCmp); equivalent declaration of map with function pointer


	vector <int> tmp;

	double eps, s;
	int N = 0;
	int w;
	int b = 0; // the number of buckets
	int b_curr = 0; // current bucket id
	int buck_size = 20;

	char fname[20];
	int n, l, j = 1;
	int bSize, curSize; // size of vectors of items


	string str;
	/*cin >> fname;
	myfile.open(fname);*/
	//system("cd");

	cout << "Enter the support parameter: s = ";
	cin >> s;
	cout << "Enter the error parameter: eps = ";
	cin >> eps;

	w = (int) ceil(1 / eps);

	myfile.open("ex2.txt");
	if (!myfile.is_open()) {
		cout << "Error opening file!" << endl;
		return -1;
	}

	for (j = 1; getline(myfile, str) && j < 11; j++) {

		if (j == 1) {
			b++;
			b_curr++;
		}

		//cout << str << '\n';

		MyStSt.str(str);




		while (MyStSt >> n) {		
			tmp.push_back(n);
		}
		N++;
		MyStSt.clear();
		Buffer.push_back(tmp);
		tmp.clear();
		cout << str << endl;
		//cout << "aaf" << endl;

		if (j > w) {
			j = 0;
		}

		if (b > buck_size) {



			cout << "11 < 22" << endl;

			//sort(Buffer.begin(), Buffer.end(), myVecCmp); there is no necessity to sort transactions

			bSize = Buffer.size();
			for (int k = 0; k < bSize; k++) {
				curSize = Buffer[k].size();

				addItemToHeap(Buffer[k].begin(), Buffer[k].end(), Heap, Lists);
		
				for (int z = 0; z < curSize; z++) { // itemset test output
					cout << Buffer[k][z] << " ";
				}

				cout << endl;
			}	

			makeNewTrie(Trie, Heap, Lists, b_curr, b);
			
			while (!Heap.empty())
			{
				cout << Heap.top() << endl;
				Heap.pop();
			}

			//Lists.clear();
			Buffer.clear();

			b = 0;

			//getchar();
		}

	}

	if (j != 1) {
		bSize = Buffer.size();
		for (int k = 0; k < bSize; k++) {
			curSize = Buffer[k].size();

			addItemToHeap(Buffer[k].begin(), Buffer[k].end(), Heap, Lists);

			for (int z = 0; z < curSize; z++) { // itemset test output
				cout << Buffer[k][z] << " ";
			}

			cout << endl;
		}

		makeNewTrie(Trie, Heap, Lists, b_curr, b);

		while (!Heap.empty())
		{
			cout << Heap.top() << endl;
			Heap.pop();
		}

		//Lists.clear();
		Buffer.clear();
	}


	myfile.close();


	//myfile << "Writing this to a file.\n";
	cout << "aaf" << endl;
	printItemsets(Trie, s, eps, N);
	getchar();
	return 0;
}