#include "MyPriorityQueue.h"

MyPriorityQueue::MyPriorityQueue() : size(0), head(nullptr)
{
}

PriorityQueueNode* MyPriorityQueue::insertElement(Vertex* vertexToInsert, int roadLength)
{
	if (size == 0)
	{
		head = new PriorityQueueNode;
		head->vertex = vertexToInsert;
		head->roadLength = roadLength;
		head->previousNode = nullptr;
		head->next = nullptr;
		size++;

		return head;
	}
	else
	{
		PriorityQueueNode* currentNode = head;
		PriorityQueueNode* prev = head;
		bool isHead = true;
		for (int i = 0; i < size; i++)
		{	
			if (roadLength <= currentNode->roadLength) break;
			prev = currentNode;
			currentNode = currentNode->next;
			isHead = false;
		}
		if(!isHead)currentNode = prev;

		if (currentNode != nullptr && currentNode != head || !isHead)
		{
			PriorityQueueNode* newNode = new PriorityQueueNode;
			PriorityQueueNode* temp = currentNode->next;
			currentNode->next = newNode;
			newNode->previousNode = nullptr;
			newNode->vertex = vertexToInsert;
			newNode->roadLength = roadLength;
			newNode->next = temp;
			size++;
			return newNode;
		}
		else if (currentNode == head && currentNode != nullptr)
		{
			PriorityQueueNode* newNode = new PriorityQueueNode;
			newNode->next = head;
			head = newNode;
			newNode->previousNode = nullptr;
			newNode->vertex = vertexToInsert;
			newNode->roadLength = roadLength;
			size++;
			return newNode;
		}
	}

	return nullptr;
}

void MyPriorityQueue::deleteFirstElement()
{
	if (size == 0)
	{
		delete head;
		head = nullptr;
	}
	else
	{
		PriorityQueueNode* temp = head;
		head = temp->next;
		delete temp;
	}
	size--;
}
