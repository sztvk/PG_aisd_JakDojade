#include "VertexList.h"
#include "Vertex.h"
#pragma warning(disable : 4996)

VertexList::VertexList()
{
	this->head = nullptr;
	this->size = 0;
	this->tail = nullptr;
}

void VertexList::addElementAtTheBeginning(char* cityName, int positionX, int positionY)
{
	if (size == 0)
	{
		head = new Vertex;
		if(cityName!=nullptr)strcpy(head->cityName, cityName);
		head->nextVertex = nullptr;
		head->pointCoordinates.x = positionX;
		head->pointCoordinates.y = positionY;
		tail = head;
		size++;
	}
	else
	{
		Vertex* temp = head;
		temp = head;
		head = new Vertex;
		head->nextVertex = temp;
		head->pointCoordinates.x = positionX;
		head->pointCoordinates.y = positionY;

		if (cityName != nullptr)strcpy(head->cityName, cityName);
		size++;
	}
}

void VertexList::addElementAtTheEnd(char* cityName, int positionX, int positionY)
{
	if (size == 0)
	{
		addElementAtTheBeginning(cityName, positionX, positionY);
	}
	else
	{
		Vertex* newNode = new Vertex;
		tail->nextVertex = newNode;
		newNode->pointCoordinates.x = positionX;
		newNode->pointCoordinates.y = positionY;
		newNode->nextVertex = nullptr;
		
		if (cityName != nullptr)strcpy(newNode->cityName, cityName);
		
		tail = newNode;
		size++;
	}
}

void VertexList::deleteFirstElement()
{
	if (size == 0)
	{
		delete head;
		head = NULL;
		tail = nullptr;
	}
	else
	{
		Vertex* temp = head;
		head = temp->nextVertex;
		delete temp;
	}
	size--;
}

void VertexList::deleteLastElement()
{
	Vertex* currentVertex = head;
	if (size == 0) deleteFirstElement();
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (i == size - 1)
			{
				delete currentVertex;
				size--;
				break;
			}
			currentVertex = currentVertex->nextVertex;
		}
	}
}

void VertexList::deleteAllElements()
{
	for (int i = 0; i < size; i++)
	{
		deleteFirstElement();
	}
}

Vertex* VertexList::findVertexWithGivenName(char* name)
{
	Vertex* currentVertex = head;

	for (int i = 0; i < size; i++)
	{
		if (strcmp(currentVertex->cityName, name) == 0) return currentVertex;

		currentVertex = currentVertex->nextVertex;
	}

	return nullptr;
}
