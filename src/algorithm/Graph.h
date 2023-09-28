#ifndef GRAPH
#define GRAPH

#ifndef ARDUINOSTL_H
#define ARDUINOSTL_H
#include "ArduinoSTL.h"
#endif

#ifndef VERTEX_H
#define VERTEX_H
#include "Vertex.h"
#endif

#include <vector>
#include <queue>

#define MAX_INT 2147483647

// Struct to comprise Vertex objects and define graph traversal methods
struct Graph
{
    // Number of vertices
    int n;

    std::vector<Vertex> vertices;

    // Constructors
    Graph();
    Graph(int nIn);
    Graph(std::vector<Vertex> verticesIn);

    // Methods
    Vertex *get(Vertex v);
    Vertex *add(Vertex v);

    // Discover shortest path from source to destination using Breath First Search. Returns pointer to first element of array.
    std::vector<Vertex *> findPath(Vertex &source, Vertex &destination);

    // Operators
    Vertex &operator[](int index);
};

// Default constructor for an empty graph
Graph::Graph() : n(0) {}

// Constructor for a graph of n vertices
Graph::Graph(int nIn) : n(nIn), vertices( std::vector<Vertex>(n, Vertex()) ) {}

// Constructor for a graph of already initialized vertices
Graph::Graph(std::vector<Vertex> verticesIn) : n(verticesIn.size()), vertices(verticesIn) {}

// Get pointer to vertex object from its coordinates
Vertex *Graph::get(Vertex v)
{
    for (int i = 0; i < n; i++) {
        if (v == vertices[i]) {
            return &vertices[i];
        }
    }
    Serial.println("Vertex not found");
    return nullptr;
}

// Add vertex (returns pointer to created object)
Vertex *Graph::add(Vertex v)
{
    vertices.push_back(v);
    n++;
    return &vertices[n - 1];
}

// Algorithm to find shortest path from a source vertex to a destination vertex using Breath First Search (search by distance)
std::vector<Vertex *> Graph::findPath(Vertex &source, Vertex &destination)
{
    // Declare queue of maximum n vertices (vertices queued are to be visited)
    // The integer queued represents the index for the vertex in the vertices vector
    std::queue<int> queue[n];
    // Declare array to save whether the iterated vertex i has been visited
    bool visited[n];
    // Declare array to save distances of the source vertex to each iterated vertex i
    int distance[n];
    // Declare array to save what the previous

    // Indices of source and destination on the vertices vector
    int s_index;
    int d_index;

    // Initialize values
    for (int i = 0; i < n; i++)
    {
        // Maximum integer value distance for vertices not yet encountered (we don't know how far they are)
        distance[i] = MAX_INT;

        if (vertices[i] == source) {
            // Distance from source to source is always 0
            distance[i] = 0;
            s_index = i;
        }
        if (vertices[i] == destination) {
            d_index = i;
        }
    }

    // Find shortest path to each vertex in vertices vector
    for (int i = 0; i < n; i++)
    {
        // Find shortest path
    }

   return {};
}

// Overload the [] operator to access vertices by index
Vertex &Graph::operator[](int index) { return vertices[index]; }

#endif