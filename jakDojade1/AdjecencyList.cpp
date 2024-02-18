#include "AdjecencyList.h"
#include "Vertex.h"

AdjecencyList::AdjecencyList() : head(nullptr), size(0), tail(nullptr)
{
}

void AdjecencyList::addElementAtTheEnd(Vertex* newAdjacentVertex, int roadLength)
{
	if (size == 0)
	{
		head = new AdjecencyListNode;
		head->adjecentVertex = newAdjacentVertex;
		head->roadLength = roadLength;
		head->next = nullptr;
		tail = head;
		size++;
	}
	else
	{
		AdjecencyListNode* newNode = new AdjecencyListNode;
		tail->next = newNode;
		newNode->adjecentVertex = newAdjacentVertex;
		newNode->next = nullptr;
		newNode->roadLength = roadLength;
		tail = newNode;
		size++;
	}
}

AdjecencyListNode* AdjecencyList::findNodeWithGivenName(char* name)
{
	AdjecencyListNode* currentNode = head;

	for (int i = 0; i < size; i++)
	{
		if (strcmp(currentNode->adjecentVertex->cityName, name) == 0) return currentNode;
		currentNode = currentNode->next;
	}

	return nullptr;
}
