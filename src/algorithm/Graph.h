#ifndef GRAPH
#define GRAPH

#include <vector>
#include <stack>
#include <limits>

#ifndef VERTEX_H
#define VERTEX_H
#include "Vertex.h"
#endif

// Struct to comprise Vertex objects and define graph traversal methods
struct Graph
{
    // Number of vertices
    int n;

    // Current position of exploration
    Vertex* pos;

    // List of vertices in the graph
    std::vector<Vertex> vertices;

    // Constructors
    Graph();
    Graph(int nIn);
    Graph(std::vector<Vertex> verticesIn);

    // Methods
    Vertex *get(Vertex v);
    Vertex *add(Vertex v);

    // Discover shortest path from source to destination using Breath First Search
    void findPath(Vertex source, Vertex destination);

    // Operators
    Vertex &operator[](int index);
};

// Default constructor for an empty graph
Graph::Graph()
{
    n = 0;
}

// Constructor for a graph of n vertices
Graph::Graph(int nIn)
{
    n = nIn;
    vertices = std::vector<Vertex>(n, Vertex());
}

// Constructor for a graph of already initialized vertices
Graph::Graph(std::vector<Vertex> verticesIn)
{
    n = vertices.size();
    vertices = verticesIn;
    pos = get(Vertex(0, 0));
}

// Get pointer to vertex object from its coordinates
Vertex *Graph::get(Vertex v)
{
    for (int i = 0; i < n; i++)
    {
        if (v == vertices[i])
        {
            return &vertices[i];
        }
    }
    // Serial.println("Vertex not found");
    // std::cout << "Vertex not found" << std::endl;
    return nullptr;
}

// Add vertex (returns pointer to created object)
Vertex *Graph::add(Vertex v)
{
    vertices.push_back(v);
    n++;
    return &vertices[n - 1];
}

void Graph::findPath(Vertex source, Vertex destination)
{
    
    /* 
    TODO: CHANGE THIS IMPLEMENTATION FROM DIJKSTRA'S ALGORITHM INTO BFS
    // Indices of source and destination on the vertices vector
    int s_index;
    int d_index;
    // Array that saves the distance from the source to vertices[i]
    int distance[n];
    // True if there is a definitive (final) shortest path tree to vertices[i]
    bool spt[n];

    // Initialize values
    for (int i = 0; i < n; i++)
    {
        // Infinite distance for vertices not yet encountered (we don't know how far they are)
        distance[i] = std::numeric_limits<int>::max();
        // False for all vertices except source, as the shortest path tree is still to be discovered
        spt[i] = 0;

        if (vertices[i] == source)
        {
            // Distance from source to source is always 0
            distance[i] = 0;
            s_index = i;
        }
        if (vertices[i] == destination)
        {
            d_index = i;
        }
    }

    // Find shortest path to each vertex in vertices vector
    for (int i = 0; i < n; i++)
    {
        // Find shortest path
    }
    */
}

// Overload the [] operator to access vertices by index
Vertex &Graph::operator[](int index) { return vertices[index]; }

#endif