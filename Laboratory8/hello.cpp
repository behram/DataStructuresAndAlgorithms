#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <chrono>
#include <algorithm>
#include "BST.cpp"

using namespace std;

void BSTcounting(ifstream &textFile, BST &tree)
{
	string line;
	string word;
	while (getline(textFile, line))
	{
		for (int i = 0; !iscntrl(line[i]); ++i)
		{
			if (isalpha(line[i]))
			{
				word.push_back(tolower(line[i]));
				if (!isalpha(line[i + 1]))
				{
					auto node = treeSearch(tree.root, word);
					if (node)
					{
						node->elem.value++;
					}
					else
					{
						Element elem;
						elem.key = word;
						elem.value = 1;
						insertElem(tree, elem);
					}

					word.clear();
				}
			}
		}
	}
}

void BSTresult(BST &tree)
{
	vector<Element> vector = treeMAX(tree);
	cout << "Top 10 words" << endl;
	for (int i = 0; i < 10; ++i)
	{
		Element elem = vector.back();
		vector.pop_back();
		cout << elem.key << "\t" << elem.value << endl;
	}
}


/************* HashMap ************/
void HashTableCounting(ifstream &textFile, unordered_map <string, int> &hashmap)
{
	string line;
	string word;
	while (getline(textFile, line))
	{
		for (int i = 0; !iscntrl(line[i]); ++i)
		{
			if (isalpha(line[i]))
			{
				word.push_back(tolower(line[i]));
				if (!isalpha(line[i + 1])) {
					if (hashmap.count(word)){
						hashmap[word]++;
					} else {
						hashmap.insert({ word, 1 });
					}
					word.clear();
				}
			}
		}
	}
}

void HashTableResult(unordered_map <string, int> &hashmap)
{
	vector<pair<string, int>> pairs;
	for (auto itr = hashmap.begin(); itr != hashmap.end(); ++itr){
		pairs.push_back(*itr);
    }

	sort(pairs.begin(), pairs.end(), [](pair<string, int>& a, pair<string, int>& b)
	{
		return a.second < b.second;
	}
	);

	cout << "Top 10 words" << endl;
	for (int i = 0; i < 10; ++i)
	{
		auto elem = pairs.back();
		pairs.pop_back();
		cout << elem.first << "\t" << elem.second << endl;
	}
}

/************* HashMap ************/
int main()
{
	ifstream textFile;
	textFile.open("/private/var/www/DataStructuresAndAlgorithms/Laboratory8/big.txt", ifstream::in);


	/************* BST ************/
	clock_t all = clock();

	BST tree;
	init(tree);

	BSTcounting(textFile, tree);
	BSTresult(tree);

	all = clock() - all;
	cout << "BST : " << (((float)all)/CLOCKS_PER_SEC) << endl;
	/************* BST ************/







	/************* HashMap ************/
    all = clock();

    unordered_map <string, int> hashmap;
    HashTableCounting(textFile, hashmap);
    HashTableResult(hashmap);

    all = clock() - all;
    cout << "Hash Table : " << (((float)all)/CLOCKS_PER_SEC) << endl;
	/************* HashMap ************/

	return 0;
}
