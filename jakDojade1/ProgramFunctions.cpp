#include "ProgramFunctions.h"

#pragma warning(disable : 4996)

using namespace std;

void ProgramFunctions::createNewMap(int height, int width)
{
	mapHeight = height;
	mapWidth = width;

	map = new char* [height];
	visitedSpots = new bool* [height];
	tableOfVertices = new Vertex **[height];

	for (int i = 0; i < height; i++)
	{
		map[i] = new char[width];
		visitedSpots[i] = new bool[width];
		tableOfVertices[i] = new Vertex * [width];

		for (int j = 0; j < width; ++j)visitedSpots[i][j] = false;
		for (int j = 0; j < width; ++j)tableOfVertices[i][j] = nullptr;
	}
}

void ProgramFunctions::writeDataToMap()
{
	char command = getchar();

	for (int i = 0; i < mapHeight; i++)
	{
		fgets(map[i], mapWidth + 1, stdin);
		getchar();

		for (int j = 0; j < mapWidth + 1; j++)
		{
			if (map[i][j] == '*')
			{
				verticesList.addElementAtTheEnd(nullptr, i, j);
			}
		}
	}
}

void ProgramFunctions::handleFlightsInput(char* command)
{
	char numberOfFlights[MAX_CITY_NAME];
	*command = getchar();
	findText(command, numberOfFlights, '\n');
	int flights = atol(numberOfFlights);

	for (int i = 0; i < flights; i++)
	{
		*command = getchar();
		if (*command == '\n') *command = getchar();

		//int letterCounter = 0;
		char firstCityNameInFlight[MAX_CITY_NAME];
		findText(command, firstCityNameInFlight, ' ');

		char secondCityNameInFlight[MAX_CITY_NAME];

		*command = getchar();
		findText(command, secondCityNameInFlight, ' ');

		char flightLength[MAX_CITY_NAME];
		*command = getchar();
		findText(command, flightLength, '\n');

		addFlight(firstCityNameInFlight, secondCityNameInFlight, atol(flightLength));
	}
}

void ProgramFunctions::addFlight(char* startingCity, char* destinationCity, int roadLength)
{
	Vertex* searchedCity = hashTableOfCities.findVertexWithGivenName(startingCity);
	Vertex* destinationCityVertex = hashTableOfCities.findVertexWithGivenName(destinationCity);
	
	if (searchedCity != nullptr) searchedCity->adjecencyList.addElementAtTheEnd(destinationCityVertex, roadLength);
}

char* ProgramFunctions::lookForCityName(int positionX, int positionY)
{
	int cityNameCounter = 0;
	char newCityName[MAX_CITY_NAME];

	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			int positionXToCheck = positionX + x;
			int positionYToCheck = positionY + y;

			if (x == 0 && y == 0) continue;

			if (positionXToCheck >= 0 && positionXToCheck < mapHeight && positionYToCheck >= 0 && positionYToCheck < mapWidth)
			{
				if ((map[positionXToCheck][positionYToCheck] >= 'A' && map[positionXToCheck][positionYToCheck] <= 'Z') ||(map[positionXToCheck][positionYToCheck] >= '0' && map[positionXToCheck][positionYToCheck] <= '9'))
				{
					// searching for the first letter in a city name
					while ((map[positionXToCheck][positionYToCheck - 1] != '.' && map[positionXToCheck][positionYToCheck - 1] != '#' && map[positionXToCheck][positionYToCheck - 1] != '*') && positionYToCheck >0)
					{
						positionYToCheck--;
					}

					// reading actual city name
					while ((map[positionXToCheck][positionYToCheck] >= 'A' && map[positionXToCheck][positionYToCheck] <= 'Z') || (map[positionXToCheck][positionYToCheck] >= '0' && map[positionXToCheck][positionYToCheck] <= '9'))
					{
						newCityName[cityNameCounter] = map[positionXToCheck][positionYToCheck];
						positionYToCheck++;
						cityNameCounter++;
					}

					newCityName[cityNameCounter] = '\0';
					return newCityName;
				}
			}
		}
	}
	return nullptr;
}

void ProgramFunctions::dijkstra(Vertex* startingVertex, Vertex* destinationVertex)
{
	bool* visited = new bool[hashTableOfCities.numberOfElements];
	int* distance = new int[hashTableOfCities.numberOfElements];
	Vertex** predecessor = new Vertex * [hashTableOfCities.numberOfElements];
	MyPriorityQueue priorityQueue;
	Vertex* currentVertex = verticesList.head;

	int startingIndex = tableOfVertices[startingVertex->pointCoordinates.x][startingVertex->pointCoordinates.y]->vertexNumber;

	// initializing priority queue
	for (int i = 0; i < hashTableOfCities.numberOfElements; i++)
	{
		distance[i] = INFINITY_DISTANCE;
		predecessor[i] = nullptr;
		visited[i] = false;
		if (startingIndex == i)
		{
			distance[startingIndex] = 0;
			priorityQueue.insertElement(tableOfVertices[currentVertex->pointCoordinates.x][currentVertex->pointCoordinates.y], distance[tableOfVertices[currentVertex->pointCoordinates.x][currentVertex->pointCoordinates.y]->vertexNumber]);
		}

		currentVertex = currentVertex->nextVertex;
	}

	while (priorityQueue.size > 0)
	{
		Vertex* u = priorityQueue.head->vertex;
		priorityQueue.deleteFirstElement();
		visited[tableOfVertices[u->pointCoordinates.x][u->pointCoordinates.y]->vertexNumber] = true;

		if (u == destinationVertex) break;

		AdjecencyListNode* neighbour = u->adjecencyList.head;

		while(neighbour!=nullptr)
		{
			// szukam indeksu w glownej liscie
			int dIndexU = tableOfVertices[u->pointCoordinates.x][u->pointCoordinates.y]->vertexNumber;
			int dIndexV = tableOfVertices[neighbour->adjecentVertex->pointCoordinates.x][neighbour->adjecentVertex->pointCoordinates.y]->vertexNumber;

			if (visited[dIndexV])
			{
				neighbour = neighbour->next;
				continue;
			}

			int distanceSum = neighbour->roadLength;
			if (distance[dIndexU] != INFINITY) distanceSum += distance[dIndexU];
			if (distance[dIndexV] > distanceSum)
			{
				distance[dIndexV] = distanceSum;
				predecessor[dIndexV] = u;

				priorityQueue.insertElement(neighbour->adjecentVertex, distanceSum);
			}
			neighbour = neighbour->next;
		}
	}
	
	startingVertex->dijkstraResults.cityDistance = distance;
	startingVertex->dijkstraResults.cityPredecessors = predecessor;

	delete[] visited;
}

void ProgramFunctions::handleQueries(char* command)
{
	int numberOfQueries;
	std::cin >> numberOfQueries;

	for (int i = 0; i < numberOfQueries; i++)
	{
		*command = getchar();
		if (*command == '\n') *command = getchar();
		int letterCounter = 0;
		char firstCityName[MAX_CITY_NAME];
		findText(command, firstCityName, ' ');

		letterCounter = 0;
		char secondCityName[MAX_CITY_NAME];

		*command = getchar();
		findText(command, secondCityName, ' ');

		int mode;
		std::cin >> mode;

		Vertex* startingVertex = hashTableOfCities.findVertexWithGivenName(firstCityName);
		Vertex* destinationVertex = hashTableOfCities.findVertexWithGivenName(secondCityName);

		dijkstra(startingVertex, destinationVertex);

		if (mode == 0)
		{
			cout << startingVertex->dijkstraResults.cityDistance[destinationVertex->vertexNumber] << endl;
		}
		else if (mode == 1)
		{
			int distanceToPrint = startingVertex->dijkstraResults.cityDistance[destinationVertex->vertexNumber];

			MyStack roadToCity;
			Vertex* predecesorVertex = destinationVertex;

			do
			{
				int destinationVertexIndex = hashTableOfCities.findVertexWithGivenName(predecesorVertex->cityName)->vertexNumber;

				if (startingVertex->dijkstraResults.cityPredecessors[destinationVertexIndex]->cityName != nullptr) roadToCity.addElementAtTheEnd(startingVertex->dijkstraResults.cityPredecessors[destinationVertexIndex]);
				predecesorVertex = startingVertex->dijkstraResults.cityPredecessors[destinationVertexIndex];

			} while (predecesorVertex != nullptr);

			if (roadToCity.size == 1) cout << distanceToPrint << endl;
			else cout << distanceToPrint << " ";

			bool skipFirst = true;
			while (roadToCity.size > 0)
			{
				if (skipFirst) skipFirst = false;
				else
				{
					if (roadToCity.size > 1) cout << roadToCity.top->vertexOnStack->cityName << " ";
					else cout << roadToCity.top->vertexOnStack->cityName << endl;

				}
				roadToCity.deleteLastElement();
			}
		}
		delete startingVertex->dijkstraResults.cityDistance;
		delete startingVertex->dijkstraResults.cityPredecessors;
	}
}

void ProgramFunctions::resetVisitedSpots()
{
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			visitedSpots[i][j] = false;
		}
	}
}

void ProgramFunctions::handleCities()
{
	Vertex* currentNode = verticesList.head;

	for (int i = 0; i < verticesList.size; i++)
	{
		char cityName[MAX_CITY_NAME];
		strcpy(cityName, lookForCityName(currentNode->pointCoordinates.x, currentNode->pointCoordinates.y));
		bool isSurrounded = isCitySurroundedByRoads(currentNode->pointCoordinates.x, currentNode->pointCoordinates.y);

		// add vertices with cities to the data structures
		tableOfVertices[currentNode->pointCoordinates.x][currentNode->pointCoordinates.y] = hashTableOfCities.insertElement(cityName, currentNode->pointCoordinates.x, currentNode->pointCoordinates.y);
		currentNode->setName(cityName);

		currentNode->isSurroundedByRoads = isSurrounded;
		tableOfVertices[currentNode->pointCoordinates.x][currentNode->pointCoordinates.y]->isSurroundedByRoads = isSurrounded;

		currentNode = currentNode->nextVertex;
	}
}

void ProgramFunctions::searchMap()
{
	Vertex* currentNode = verticesList.head;
	for (int i = 0; i < verticesList.size; i++)
	{
		if (currentNode->isSurroundedByRoads == true)
		{
			startBFS(currentNode->pointCoordinates.x, currentNode->pointCoordinates.y, currentNode->cityName);
			resetVisitedSpots();
		}
		currentNode = currentNode->nextVertex;
	}
}

void ProgramFunctions::startBFS(int x, int y, char* cityName)
{
	MyQueue newQueue;
	newQueue.addElementAtTheEnd(x, y, nullptr, 0);

	visitedSpots[x][y] = true;

	while (newQueue.size > 0)
	{
		x = newQueue.head->coordinates.x;
		y = newQueue.head->coordinates.y;
		Vertex* parent = newQueue.head->parent;
		int roadLength = newQueue.head->roadLength;
		newQueue.deleteFirstElement();

		if (map[x][y] == '*')
		{
			Vertex* city = tableOfVertices[x][y];

			if (parent != nullptr)
			{
				parent->adjecencyList.addElementAtTheEnd(city, roadLength);
				parent = city;
				continue;
			}

			parent = city;
		}
		

		for (int changeX = -1; changeX <= 1; changeX++)
		{
			for (int changeY = -1; changeY <= 1; changeY++)
			{
				if (changeX * changeY != 0 || changeX + changeY == 0) continue;

				int positionXToCheck = x + changeX;
				int positionYToCheck = y + changeY;

				if (positionXToCheck >= 0 && positionXToCheck < mapHeight && positionYToCheck >= 0 && positionYToCheck < mapWidth)
				{
					if (map[positionXToCheck][positionYToCheck] == '#' || map[positionXToCheck][positionYToCheck] == '*')
					{
						if (visitedSpots[positionXToCheck][positionYToCheck] == false)
						{
							newQueue.addElementAtTheEnd(positionXToCheck, positionYToCheck, parent, roadLength + 1);
							visitedSpots[positionXToCheck][positionYToCheck] = true;
						}
					}
				}
			}
		}
	}
}

bool ProgramFunctions::isCitySurroundedByRoads(int x, int y)
{
	for (int changeX = -1; changeX <= 1; changeX++)
	{
		for (int changeY = -1; changeY <= 1; changeY++)
		{
			if (changeX * changeY != 0 || changeX + changeY == 0) continue;

			int positionXToCheck = x + changeX;
			int positionYToCheck = y + changeY;

			if (positionXToCheck >= 0 && positionXToCheck < mapHeight && positionYToCheck >= 0 && positionYToCheck < mapWidth)
			{
				if (map[positionXToCheck][positionYToCheck] == '#' || map[positionXToCheck][positionYToCheck] == '*')
				{
					return true;
				}
			}
		}
	}
	return false;
}

void ProgramFunctions::findText(char* command, char* charArray, char delimiter)
{
	int letterCounter = 0;
	while (*command != delimiter)
	{
		charArray[letterCounter] = *command;
		letterCounter++;
		*command = getchar();
	}
	charArray[letterCounter] = '\0';
}
