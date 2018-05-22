#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <map>
#include <unordered_map>
#include <map>
#include <vector>
#include <cctype>
#include <chrono>
#include <algorithm>
#include "BST.cpp"

using namespace std;

void drawHeader();

/************* BST ************/
void BSTNormalize(ifstream &textFile, BST &tree)
{
	string line,word;
	while (getline(textFile, line))
	{
		word = "";
		for(size_t i = 0; i <= line.length(); i++)
		{
			if(word != "" && (i == line.length() || !isalpha(line[i])))
			{
				insertElem(tree, word);
				word = "";
			}
			else if(isalpha(line[i]))
			{
				word += tolower(line[i]);
			}
			else
			{
				continue;
			}
		}
	}
}

void BSTResult(BST &tree)
{
	int s = std::min(10, numberOfNodes(tree));
	Node *maxValue;

	drawHeader();
	for(int i = 0; i < s; i++)
	{
		maxValue = findMaxValue(tree.root);
		cout << i+1 << ".\t" << maxValue->elem.key << "\t" << maxValue->elem.value << endl;
		removeKey(tree, maxValue->elem.key);
	}
}
/************* BST ************/

/************* BBST ************/
void BBSTNormalize(ifstream &textFile, map <string, int> &bstmap)
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
					if (bstmap.count(word))
						bstmap[word]++;
					else
					{
						bstmap[word] = 1;
					}
					word.clear();
				}
			}
		}
	}
}
void BBSTResult(map <string, int> &bstmap)
{
	vector<pair<string, int>> pairs;
	for (auto itr = bstmap.begin(); itr != bstmap.end(); ++itr){
		pairs.push_back(*itr);
	}

	sort(pairs.begin(), pairs.end(), [=](pair<string, int>& a, pair<string, int>& b) {
		return a.second < b.second;
	});

	drawHeader();
	for (int i = 0; i < 10; ++i)
	{
		auto elem = pairs.back();
		pairs.pop_back();
		cout << i+1 << ".\t" << elem.first << "\t" << elem.second << endl;
	}
}
/************* BBST ************/

/************* HashMap ************/
void HashTableCounting(ifstream &textFile, unordered_map <string, int> &hashmap)
{
	string line,word;
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

void HashTableResult(unordered_map <string, int> hashmap)
{
	vector<pair<string, int>> pairs;

	for (auto itr = hashmap.begin(); itr != hashmap.end(); ++itr){
		pairs.push_back(*itr);
	}

	sort(pairs.begin(), pairs.end(), [=](pair<string, int>& a, pair<string, int>& b) {
		return a.second < b.second;
	});

	drawHeader();
	for (int i = 0; i < 10; ++i)
	{
		auto elem = pairs.back();
		pairs.pop_back();
		cout << i+1 << ".\t" << elem.first << "\t" << elem.second << endl;
	}
}

void drawHeader()
{
	cout << "Order" << "\t" << "Word" << "\t" << "Hit Count" << endl;
}

void drawLine()
{
	for (int i = 0; i < 50; ++i){
		cout << "-";
	}
	cout << "\n";
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

	BSTNormalize(textFile, tree);
	BSTResult(tree);

	all = clock() - all;
	cout << "BST : " << (((float)all)/CLOCKS_PER_SEC) << endl;
	drawLine();
	/************* BST ************/


	/************* BBST ************/
	textFile.clear();
	textFile.seekg(0, ios::beg);
	all = clock();

	map<string, int> bbstmap;
	BBSTNormalize(textFile, bbstmap);
	BBSTResult(bbstmap);

	all = clock() - all;
	cout << "BBST : " << (((float)all)/CLOCKS_PER_SEC) << endl;
	drawLine();
	/************* BBST ************/



	/************* HashMap ************/
    textFile.clear();
    textFile.seekg(0, ios::beg);
    all = clock();

    unordered_map <string, int> hashmap;
    HashTableCounting(textFile, hashmap);
    HashTableResult(hashmap);

    all = clock() - all;
    cout << "Hash Table : " << (((float)all)/CLOCKS_PER_SEC) << endl;
	/************* HashMap ************/

	return 0;
}
