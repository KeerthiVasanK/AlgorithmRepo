// Word Search.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <map>
#include <vector>

typedef struct SearchableObject
{
	long id;
	std::string value;

	SearchableObject(long id, std::string value):id(id),value(value)
	{

	}

}Item;

std::vector<Item> SearchableList;
std::vector<Item>::iterator listIterator;

void ConstructData()
{
	listIterator = SearchableList.begin();

	SearchableList.push_back(Item(1,"Apple"));
	SearchableList.push_back(Item(2,"Poll"));
	SearchableList.push_back(Item(3,"Orange"));
	SearchableList.push_back(Item(4,"King"));
	SearchableList.push_back(Item(5,"Water"));
	SearchableList.push_back(Item(6,"Stupify"));
	SearchableList.push_back(Item(7,"Knuckle"));
	SearchableList.push_back(Item(8,"Pink"));
	SearchableList.push_back(Item(9,"Oswald"));
	SearchableList.push_back(Item(10,"Warp"));
}

typedef struct Node_Trie
{
	std::map<char, Node_Trie*> children;
	std::vector<long> items;

	bool bEndOfString;

	Node_Trie()
	{
		bEndOfString = false;
	}

}Trie;

Trie* pRoot; 

void Insert(Trie* node, Item item, int level = 0)
{
	char currentChar = item.value[level];
	int length = item.value.length();
	
	std::map<char, Node_Trie*>::iterator x = node->children.find(currentChar);

	if(x == node->children.end())
		node->children.insert(x, std::pair<char, Node_Trie*>(currentChar, new Trie()));

	node->items.push_back(item.id);

	x = node->children.find(currentChar);
	
	if(length != level)
		Insert(x->second, item, level + 1);
	else
		node->bEndOfString = true;
}

std::vector<long> Search(Trie* node, std::string text, int level = 0)
{
	int length = text.length();

	if(level == length)
		return std::vector<long>();

	char currentChar = text.at(level);

	std::map<char, Node_Trie*>::iterator x = node->children.find(currentChar);

	if(x == node->children.end())
		return std::vector<long>();
	else
	{
		if(level == length - 1)
			return x->second->items;
		else
			return Search(x->second, text, level +1);
	}

}

void SearchText()
{
	char text[100]; 
	printf("\n Enter text to search:\t");
	scanf("%s", text);

	std::vector<long> filteredList = Search(pRoot, std::string(text));

	for(int i = 0; i < filteredList.size(); i++)
	{
		std::string value = SearchableList.at(filteredList.at(i) - 1).value;

		printf("%s \n", value.c_str());
	}
}

void ConstructTrie()
{
	ConstructData();

	for(int i = 0; i < SearchableList.size(); i++)
		Insert(pRoot, SearchableList.at(i));
}

int _tmain(int argc, _TCHAR* argv[])
{
	pRoot = new Trie();

	ConstructTrie();

	SearchText();

	int x;
	scanf("%d",&x);

	return 0;
}

