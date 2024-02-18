#pragma once
#include <string.h>

class Vertex;

class VertexList
{
public:
	Vertex* head;
	Vertex* tail;
	int size;

	VertexList();

	void addElementAtTheBeginning(char* cityName, int positionX, int positionY);
	void addElementAtTheEnd(char* cityName, int positionX, int positionY);

	void deleteFirstElement();
	void deleteLastElement();
	void deleteAllElements();

	Vertex* findVertexWithGivenName(char* name);
};

