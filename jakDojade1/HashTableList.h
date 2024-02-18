#pragma once
#include "Vertex.h"

struct HashTableListNode
{
	int key;
	Vertex* vertexInTable;
	HashTableListNode* next;
};

class HashTableList
{
public:
	int size;
	HashTableListNode* head;
	HashTableListNode* tail;

	HashTableList();
	void insertElement(int key, Vertex* vertexToInsert);
};

