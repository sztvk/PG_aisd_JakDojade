#pragma once

class Vertex;

struct AdjecencyListNode
{
	Vertex* adjecentVertex;
	int roadLength;

	AdjecencyListNode* next;
};

class AdjecencyList
{
public:
	AdjecencyListNode* head;
	AdjecencyListNode* tail;
	int size;

	AdjecencyList();
	void addElementAtTheEnd(Vertex* newAdjacentVertex, int roadLength);

	AdjecencyListNode* findNodeWithGivenName(char* name);

};

