#ifndef GRAPH
#define GRAPH

#include <vector>
#include <stack>
#include "Vertex.hpp"

// Struct to comprise Vertex objects and define graph traversal methods
struct Graph
{
    // Variables with default values
    int n;                        // Number of vertices
    Vertex pos;                   // Current position, at the start it is always x=0, y=0
    std::vector<Vertex> vertices; // List of vertices in the graph

    // Constructors
    Graph();
    Graph(int nIn);
    Graph(std::vector<Vertex> verticesIn);

    // Methods
    Vertex& get(Vertex v);
    Vertex& add(Vertex v);

    // Operators
    Vertex &operator[](int index);
};

// Default constructor for an empty graph
Graph::Graph()
{
    n = 0;
    pos = Vertex(0, 0);
}

// Constructor for a graph of n vertices
Graph::Graph(int nIn)
{
    n = nIn;
    pos = Vertex(0, 0);
    vertices = std::vector<Vertex>(n, Vertex());
}

// Constructor for a graph of already initialized vertices
Graph::Graph(std::vector<Vertex> verticesIn)
{
    n = vertices.size();
    pos = Vertex(0, 0);
    vertices = verticesIn;
}

// Get pointer to vertex object from its coordinates
Vertex& Graph::get(Vertex v)
{
    for (int i = 0; i < n; i++) {
        if (v == vertices[i]) {
            return vertices[i];
        }
    }
    std::cout << "Vertex not found" << std::endl;
    return pos;
}

// Add vertex (returns pointer to created object)
Vertex& Graph::add(Vertex v) {
    vertices.push_back(v);
    n++;
    return vertices[n-1];
}

// Overload the [] operator to access vertices by index
Vertex& Graph::operator[](int index) { return vertices[index]; }

#endif