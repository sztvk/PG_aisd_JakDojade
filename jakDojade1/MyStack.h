#pragma once
#include "Vertex.h"

struct StackNode
{
	Vertex* vertexOnStack;
	StackNode* previous;
};

class MyStack
{
public:
	int size;
	StackNode* top;
	
	MyStack();
	void addElementAtTheEnd(Vertex* vertexToAdd);
	void deleteLastElement();
};

