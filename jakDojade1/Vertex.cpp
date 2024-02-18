#include "Vertex.h"
#pragma warning(disable : 4996)

Vertex::Vertex() : isSurroundedByRoads(false)
{
}

void Vertex::setName(char* newCityName)
{
	strcpy(this->cityName, newCityName);
}

Vertex::~Vertex()
{
	delete[] dijkstraResults.cityDistance;
	delete[] dijkstraResults.cityPredecessors;
}
