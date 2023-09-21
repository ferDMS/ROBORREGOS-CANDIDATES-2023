#ifndef GRAPH
#define GRAPH

#include <vector>
#include <stack>
#include <unordered_map>
#include "Edge.hpp" // Also includes "Vertex.hpp"

class Graph {
    private:
        // Basic variables
            // Number of vertices
        int n;
            // Adjacency map.
            // adj[v].size() is the # of edges found until now for vertex v
        std::unordered_map<Vertex, std::vector<Edge> > adj;

        // Graph exploration variables
            // Current vertex location of exploration
        Vertex pos;
            // Stack of vertices paused
        std::stack<Vertex> stack;
            // Map of visited vertices
        std::unordered_map<Vertex, bool> visited;
            // Map of maximum possible edges for each vertex in adj
        std::unordered_map<Vertex, int> max_edges;

    public:
        // Constructors
        Graph();
        Graph(int nIn);
        Graph(std::vector<Vertex> vertices);
        Graph(std::unordered_map<Vertex, int> max_edgesIn);
        Graph(std::unordered_map<Vertex, std::vector<Edge> > adjIn);
        // Getters
        int size();
        Vertex getPos();
        std::vector<Edge> getEdges(Vertex v);
        int getMaxEdges(Vertex v);
        bool getVisitedStatus(Vertex v);
        // Setters
        void setPos(Vertex posIn);
        void setMaxEdges(Vertex v, int n_edges);
        void addVertex(Vertex v);
        void addDirEdge(Edge e);
        void addUndirEdge(Edge e);
        void addUndirEdge(Edge e, int weight);
        void setAsVisited(Vertex v);
};

Graph::Graph() {
    n = 0;
}

Graph::Graph(int nIn) {
    n = nIn;
    pos.x = 0;
    pos.y = 0;
    adj[pos] = std::vector<Edge>();
    visited[pos] = 0;
}

Graph::Graph(std::vector<Vertex> vertices) {
    n = vertices.size();
    pos.x = 0;
    pos.y = 0;
    for (int i = 0; i < n; i++) {
        adj[vertices[i]] = std::vector<Edge>();
        visited[vertices[i]] = 0;
    }
}

Graph::Graph(std::unordered_map<Vertex, int> max_edgesIn) {
    n = max_edgesIn.size();
    pos.x = 0;
    pos.y = 0;
    max_edges = max_edgesIn;
    for (std::unordered_map<Vertex, int>::iterator it = max_edges.begin(); it != max_edges.end(); it++) {
        adj[it->first] = std::vector<Edge>();
        visited[it->first] = 0;
    }
}

Graph::Graph(std::unordered_map<Vertex, std::vector<Edge> > adjIn) {
    n = adjIn.size();
    pos.x = 0;
    pos.y = 0;
    adj = adjIn;
    for (std::unordered_map<Vertex, std::vector<Edge> >::iterator it = adjIn.begin(); it != adjIn.end(); it++) {
        visited[it->first] = 0;
    }
}

int Graph::size() {
    return n;
}

Vertex Graph::getPos() {
    return pos;
}

std::vector<Edge> Graph::getEdges(Vertex v) {
    try {
        return adj[v];
    } catch (const std::out_of_range &e) {
        return std::vector<Edge>();
    }
}

int Graph::getMaxEdges(Vertex v) {
    try {
        return max_edges[v];
    } catch (const std::out_of_range &e) {
        return -1;
    }
}

bool Graph::getVisitedStatus(Vertex v) {
    try {
        return visited[v];
    } catch (const std::out_of_range &e) {
        return -1;
    }
}

void Graph::setPos(Vertex posIn) {
    pos = posIn;
}

void Graph::setMaxEdges(Vertex v, int n_edges) {
    max_edges[v] = n_edges;
}

void Graph::addVertex(Vertex v) {
    adj[v] = std::vector<Edge>();
    visited[v] = 0;
    max_edges[v] = -1;
    n++;
}

void Graph::addDirEdge(Edge e) {
    adj[e.u].push_back(e);
}

void Graph::addUndirEdge(Edge e) {
    addDirEdge(e);
    addDirEdge(e.reversed());
}

void Graph::addUndirEdge(Edge e, int weight) {
    addDirEdge(e);
    addDirEdge(e.reversed(weight));
}

void Graph::setAsVisited(Vertex v) {
    visited[v] = 1;
}

#endif