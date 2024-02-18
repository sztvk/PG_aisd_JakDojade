#include "MyStack.h"

MyStack::MyStack() : size(0), top(nullptr)
{
}

void MyStack::addElementAtTheEnd(Vertex* vertexToAdd)
{
	if(size == 0)
	{
		top = new StackNode;
		top->previous = nullptr;
		top->vertexOnStack = vertexToAdd;
		size++;
	}
	else
	{
		StackNode* newNode = new StackNode;
		newNode->previous = top;
		newNode->vertexOnStack = vertexToAdd;
		top = newNode;
		size++;
	}
}

void MyStack::deleteLastElement()
{
	if (size == 1)
	{
		delete top;
		top = nullptr;
	}
	else
	{
		StackNode* temp = top;
		top = top->previous;
		delete temp;
	}
	size--;
}
