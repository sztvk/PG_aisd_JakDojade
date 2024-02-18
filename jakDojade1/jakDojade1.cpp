#include <iostream>
#include "ProgramFunctions.h"

using namespace std;

int main()
{
    int width, height, numberOfFlights;
    char command = '.';
    cin >> width >> height;

    ProgramFunctions newProgram;

    newProgram.createNewMap(height, width);

    newProgram.writeDataToMap();
    newProgram.handleCities();

    newProgram.searchMap();
    newProgram.handleFlightsInput(&command);
    newProgram.handleQueries(&command);
   
    return 0;
}