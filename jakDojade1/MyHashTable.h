#pragma once
#include "HashTableList.h"

#define NUMBER_OF_INDICES 10007

class MyHashTable
{
public:
	int numberOfElements;
	HashTableList* hashTableWithLists;


	MyHashTable();

	Vertex* insertElement(char* cityName, int x, int y);
	Vertex* findVertexWithGivenName(char* cityName);

	int changeToSumOfAsciiCodes(char* cityName);
	int hashFunction(int asciiSum);
};