#pragma once
#include <string.h>
#include "Vertex.h"

struct QueueNode
{
	QueueNode* next;

	Point coordinates;
	Vertex* parent;
	int roadLength;
};

class MyQueue
{
public:
	QueueNode* head;
	QueueNode* tail;
	int size;

	MyQueue();

	void addElementAtTheEnd(int x, int y, Vertex* parent, int roadLength);
	void deleteFirstElement();
};

