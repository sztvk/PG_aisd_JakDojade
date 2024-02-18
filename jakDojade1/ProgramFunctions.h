#pragma once
#include <iostream>
#include "VertexList.h"
#include "MyQueue.h"
#include "MyPriorityQueue.h"
#include "MyStack.h"
#include "MyHashTable.h"
#include <chrono>

#define INFINITY_DISTANCE INT_MAX

class ProgramFunctions
{
public:
	int mapHeight;
	int mapWidth;

	char** map;
	bool** visitedSpots;
	Vertex*** tableOfVertices;

	VertexList verticesList;
	MyHashTable hashTableOfCities;

	void createNewMap(int height, int width);
	void writeDataToMap();

	void handleFlightsInput(char* command);
	void addFlight(char* startingCity, char* destinationCity, int roadLength);

	char* lookForCityName(int positionX, int positionY);

	void dijkstra(Vertex* startingVertex, Vertex* destinationVertex);

	void handleQueries(char* command);

	void resetVisitedSpots();
	void deleteMapAndVisitedSpots();

	void handleCities();
	void searchMap();
	void startBFS(int x, int y, char* cityName);
	bool isCitySurroundedByRoads(int x, int y);
	void findText(char* command, char* charArray, char delimiter);
};

