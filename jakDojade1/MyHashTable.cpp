#include "MyHashTable.h"
#pragma warning(disable : 4996)

using namespace std;

MyHashTable::MyHashTable()
{
	numberOfElements = 0;
	hashTableWithLists = new HashTableList[NUMBER_OF_INDICES];
}

Vertex* MyHashTable::insertElement(char* cityName, int x, int y)
{
	Vertex* vertexToInsert = new Vertex;
	strcpy(vertexToInsert->cityName, cityName);
	vertexToInsert->vertexNumber = numberOfElements;
	vertexToInsert->pointCoordinates.x = x;
	vertexToInsert->pointCoordinates.y = y;

	int sumOfAsciiCodes = changeToSumOfAsciiCodes(vertexToInsert->cityName);
	int index = hashFunction(sumOfAsciiCodes);

	hashTableWithLists[index].insertElement(sumOfAsciiCodes, vertexToInsert);
	numberOfElements++;

	return vertexToInsert;
}

Vertex* MyHashTable::findVertexWithGivenName(char* cityName)
{
	int sumOfAsciiCodes = changeToSumOfAsciiCodes(cityName);
	int index = hashFunction(sumOfAsciiCodes);

	if (hashTableWithLists[index].size == 1) return hashTableWithLists[index].head->vertexInTable;
	else if(hashTableWithLists[index].size == 0) return nullptr;
	else
	{
		HashTableListNode* currentNode = hashTableWithLists[index].head;

		for (int i = 0; i < hashTableWithLists[index].size; i++)
		{
			if (strcmp(currentNode->vertexInTable->cityName, cityName) == 0)
			{
				return currentNode->vertexInTable;
			}
			currentNode = currentNode->next;
		}
	}

	return nullptr;
}

int MyHashTable::changeToSumOfAsciiCodes(char* cityName)
{
	int letterCounter = 0;
	int asciiSum = 0;
	while (cityName[letterCounter] != '\0')
	{
		asciiSum = asciiSum + cityName[letterCounter] * (letterCounter + 1) * 31;
		letterCounter++;
	}

	return asciiSum;
}

int MyHashTable::hashFunction(int asciiSum)
{
	return asciiSum % NUMBER_OF_INDICES;
}
