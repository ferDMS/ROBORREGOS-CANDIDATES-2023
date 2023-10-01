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
    int find(Vertex v);

    // Discover shortest path from source to destination using Breath First Search. Returns pointer to first element of array.
    std::vector<Vertex *> findPath(Vertex source, Vertex destination);

    // Operators
    Vertex &operator[](int index);
};

// Default constructor for an empty graph
Graph::Graph() : n(0) {}

// Constructor for a graph of n vertices
Graph::Graph(int nIn) : n(nIn), vertices( std::vector<Vertex>(n, Vertex()) ) {}

// Constructor for a graph of already initialized vertices
Graph::Graph(std::vector<Vertex> verticesIn) : vertices(verticesIn), n(vertices.size())  {}

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

int Graph::find(Vertex v)
{
    for (int i = 0; i < n; i++)
    {
        if (v == vertices[i]) {
            return i;
        }
    }
    Serial.println("Vertex not found in the graph");
    return -1;
}

// Algorithm to find shortest path from a source vertex to a destination vertex using Breath First Search (search by distance)
std::vector<Vertex *> Graph::findPath(Vertex source, Vertex destination)
{
    std::queue<Vertex *> queue;
    const int maxVertices = vertices.size();
    bool visited[maxVertices];
    Vertex *parent[maxVertices];

    // Find the indices of the source and destination vertices
    int sourceIndex = -1, destinationIndex = -1;
    for (int i = 0; i < maxVertices; ++i)
    {
        visited[i] = 0;
        if (vertices[i] == source)
        {
            sourceIndex = i;
        }
        if (vertices[i] == destination)
        {
            destinationIndex = i;
        }
    }

    if (sourceIndex == -1 || destinationIndex == -1)
    {
        // Source or destination vertex not found
        Serial.println("Source or destination vertex not found");
        return std::vector<Vertex *>();
    }

    // Enqueue the source vertex
    queue.push(&vertices[sourceIndex]);
    visited[sourceIndex] = true;

    // Perform BFS
    while (!queue.empty())
    {
        Vertex *current = queue.front();
        queue.pop();

        // Serial.print("Current: ");
        // Serial.println(current->coords());

        if (current == &vertices[destinationIndex])
        {
            // Serial.println("Found final destination");
            // Reconstruct the path by backtracking from the destination to the source
            std::vector<Vertex *> path;
            int currentVertexIndex = find(*current);

            while (currentVertexIndex != sourceIndex)
            {
                path.push_back(current);
                currentVertexIndex = find(*parent[currentVertexIndex]);
                current = &vertices[currentVertexIndex];
            }

            path.push_back(&vertices[sourceIndex]);
            // Serial.println("Returning path from source to destination");
            std::reverse(path.begin(), path.end()); // Reverse the path to start from the source
            return path;
        }

        for (int i = 0; i < 4; ++i) // Assuming 4 possible directions
        {
            Vertex *neighbor = current->adj[i];

            if (neighbor != nullptr)
            {

                // Serial.print("Testing for ");
                // Serial.println(neighbor->coords());

                int neighborIndex = find(*neighbor);
                if (!visited[neighborIndex])
                {

                    // Serial.print("Added to queue: ");
                    // Serial.println(neighbor->coords());

                    queue.push(neighbor);
                    visited[neighborIndex] = true;
                    parent[neighborIndex] = current;
                }
            }
        }

        // Serial.print("Queue length: ");
        // Serial.println(queue.size());
    }

    // If no path is found, return an empty vector
    Serial.println("No path was found, returning empty vector");
    return std::vector<Vertex *>();
}

// Overload the [] operator to access vertices by index
Vertex &Graph::operator[](int index) { return vertices[index]; }

#endif