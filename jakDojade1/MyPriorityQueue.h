#pragma once
#include "Vertex.h"

struct PriorityQueueNode
{
	Vertex* vertex;
	int roadLength;
	Vertex* previousNode;

	PriorityQueueNode* next;
};

class MyPriorityQueue
{
public:
	PriorityQueueNode* head;
	int size;

	MyPriorityQueue();
	PriorityQueueNode* insertElement(Vertex* vertexToInsert, int roadLength);

	void deleteFirstElement();
};

