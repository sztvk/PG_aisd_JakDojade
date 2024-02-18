#include "MyQueue.h"
#pragma warning(disable : 4996)

MyQueue::MyQueue() : size(0), head(nullptr), tail(nullptr)
{
}

void MyQueue::addElementAtTheEnd(int x, int y, Vertex* parent, int roadLength)
{
	if (size == 0)
	{
		head = new QueueNode;
		head->coordinates.x = x;
		head->coordinates.y = y;
		head->roadLength = roadLength;
		head->parent = parent;
		head->next = nullptr;
		tail = head;
		size++;
	}
	else
	{
		QueueNode* newNode = new QueueNode;
		tail->next = newNode;
		newNode->coordinates.x = x;
		newNode->coordinates.y = y;
		newNode->roadLength = roadLength;
		newNode->parent = parent;
		newNode->next = nullptr;
		tail = newNode;
		size++;
	}
}

void MyQueue::deleteFirstElement()
{
	if (size == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		QueueNode* temp = head;
		head = temp->next;
		delete temp;
	}
	size--;
}