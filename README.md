# Jak Dojadę

**April and May 2024**
 This program was implemeted for Algorithms and Data Structures course. Author of the original instruction: **Krzysztof Ocetkiewicz** (the description below is based on this instruction). This program was implemented as a simple console application.

A rectangular map divided into squares is given. There are three types of fields:
1. the field can be empty (impassable) - denoted as . or any letter (letters form name of the city which is also impassable)
2. the field can be a part of a road (passable in both directions) - denoted as #
3. the field can be a city (passable like a road) - denoted as *
Moving through one field takes one minute. We can only move between fields adjacent by sides. Additionally, some of the cities are connected by one-way air connections.

example of the map:
```
*#####*EE.FF*#####*
.AA...#.....#...BB.
......#######......
...AAAA..#..BBBB...
....*#########*....
GG.......#.......II
*........#........*
###################
*........#........*
HH.......#.......JJ
....*#########*....
...DDDD..#..CCCC...
.........#.........
.DD......#......CC.
*#################*
```

#### Input and output
First line of input contains width w and height h of the map. The next h lines describe the map (each line contains w characters such as letters, dot, # or * - meanings described above). The next line contains a single integer k - the number of flight connections. The next k lines will describe the connections in the format source destination time, where source is the name of the starting city, destination is the name of the destination city, and time is the flight time in minutes. The next line will contain a single integer q - the number of queries. Each query will appear on a separate line and will have the format source destination type. There are two types of quieries:
1. zero - print only the shortest time to travel from source city to destination city
2. one - despite printing the shortest time, the route should also be provided.

The output for each query consists of exactly one line. At the beginning of the line should be the number representing the shortest travel time between the cities. If the query has a type of one, all intermediate cities (excluding the starting and ending cities) should also be listed in the order they were visited, separated by spaces.

example of input:
```
20 20
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.
0
3
KIELCE KRAKOW 0
KRAKOW GDANSK 0
KRAKOW GDANSK 1
```
corresponding output:
```
5
40
40 KIELCE SZCZECIN
```

#### Implementation and functionality
The map is converted to a graph, where each vertex represents each city. Then to find the shortest path form one city to another I used Dijkstra algorithm and BFS.
Using standard string class and other standard library containers was not allowed, so I implemented my own data structures such as hashmap, priority queue, list and stack. These structures were necessary to pass tests which checked many edge cases and different types of graphs (such as fans, paths, complete graphs, spiral graphs).

