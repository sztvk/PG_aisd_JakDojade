#pragma once
#include <iostream>
#include "AdjecencyList.h"
#define MAX_CITY_NAME 10

struct Point
{
	int x;
	int y;
};

struct DijkstraResults
{
	int* cityDistance;
	Vertex** cityPredecessors;
};

class Vertex
{
public:
	char cityName[MAX_CITY_NAME];
	int vertexNumber;
	AdjecencyList adjecencyList;
	DijkstraResults dijkstraResults;
	Point pointCoordinates;

	bool isSurroundedByRoads;

	Vertex* nextVertex;

	Vertex();
	void setName(char* cityName);
	~Vertex();
};

