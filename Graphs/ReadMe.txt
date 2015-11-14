CSS 343 
Homework #3 Due: Wednesday, February 11 Winter 2015

Dijkstra’s algorithm
Implement Dijkstra's shortest path algorithm, including recovering the paths. You will find the lowest cost paths and
display the cost and path from every vertex to every other vertex. A separate method will output one path in detail. The
data will be read from a file. The first line gives the number of vertices n. Following is a text description of each of the 1
through n vertices, one description per line (50 chars max length). After that, each line consists of 3 ints representing an
edge. If there is an edge from vertex 1 to vertex 2 with a weight of 10, the data is: 1 2 10. A zero for the first integer
signals the end of the data. For example:
4
Olson’s office
Classroom
STEM office
The Commons
1 2 10
1 3 5
2 4 10
2 1 15
3 1 5
3 4 20
0 0 0
Your output for all paths should be formatted like this:
Description From To Distance Path
Olson’s office
1 2 10 1 2
1 3 5 1 3
 1 4 20 1 2 4
Classroom
 2 1 15 2 1
 2 3 20 2 1 3
 2 4 10 2 4
STEM office
 3 1 5 3 1
 3 2 15 3 1 2
 3 4 20 3 4
The Commons
 4 1 --
 4 2 --
 4 3 --
Your output for a single detailed path should have a format like this (note that the location descriptions are included on
additional lines). For this method call: “G.display(2,3);” the output should be:
2 3 20 2 1 3
Classroom
Olson’s office
STEM office
Notes:
 You can assume that the input is properly formatted.
 Use an adjacency list to store the edges. This will require dynamic memory. Do not use vectors to store the edge lists.
 The graph will have no more than 100 vertices.
 Your class should have (at least) the following public methods: constructor, copy constructor, destructor, buildGraph
(ifstream &), insertEdge(int, int, int), removeEdge(int, int), findShortestPath(), displayAll(), display(int, int).
 For insert, replace any previous edge that existed between the two vertices.
 Use recursion, not a container to display a path.
 You should use a struct similar to this (from class) in your private data:
HW3 Page 1 of 2
http://courses.washington.edu/css343/cfolson/HW/HW3.htm 2/1/2015
struct Table {
 bool visited;
 int dist; // Current best distance to vertex
 int path; // Previous vertex in the path to this vertex
};
 In order to record all shortest paths, you will need a 2D array of the Table struct.
 A simple driver, data file, and some code to get you started are supplied on the course web site. You can change the
starter code, but not the driver.
