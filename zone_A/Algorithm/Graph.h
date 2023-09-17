#ifndef GRAPH
#define GRAPH

# include <vector>
# include <stack>
# include <unordered_map>
# include "Vertex.h"

class Graph {
    private:
        // Number of vertices
        int n;
        // Graph vertex position of the robot
        Vertex pos;
        // Adjacency map.
        // adj[v].size() is the # of edges found until now for vertex v
        std::unordered_map<Vertex, std::vector<Vertex>> adj;
        // Stack of vertices paused
        std::stack<Vertex> stack;
        // Map to save if a vertex has been visited or fully explored (if 0 then it hasn't)
        std::unordered_map<Vertex, bool> visited;
        // Map of maximum possible edges for each vertex
        std::unordered_map<Vertex, int> max_edges;

    public:
        // Constructors
        Graph();
        Graph(int nIn);
        Graph(std::vector<Vertex> vertices);
        Graph(std::unordered_map<Vertex, int> max_edgesIn);
        Graph(std::unordered_map<Vertex, std::vector<Vertex>> adjIn);
        // Getters
        Vertex getPos();
        std::vector<Vertex> getEdges(Vertex v);
        int getMaxEdges(Vertex v);
        bool getVisitedStatus(Vertex v);
        // Setters
        void setPos(Vertex posIn);
        void setPos(int x, int y);
        void setMaxEdges(Vertex v, int edges);
        void addVertex(Vertex v)
        void addVertex(int x, int y);
        void addEdge(Vertex v1, Vertex v2);
        void setAsVisited(Vertex v);
        // Other methods
        void evalPath();
};

Graph::Graph() {
    n = 0;
}

Graph::Graph(int nIn) {
    n = nIn;
    pos.x = 0;
    pos.y = 0;
    adj[pos] = {};
    visited[pos] = 0;
}

Graph::Graph(std::vector<Vertex> vertices) {
    n = vertices.size();
    pos.x = 0;
    pos.y = 0;
    for (int i = 0; i < n; i++) {
        adj[vertices[i]] = {};
        visited[vertices[i]] = 0;
    }
}

Graph::Graph(std::unordered_map<Vertex, int> max_edgesIn) {
    n = max_edgesIn.size();
    pos.x = 0;
    pos.y = 0;
    max_edges = max_edgesIn;
    for (auto& it : max_edges) {
        adj[it.first] = {};
        visited[it.first] = 0;
    }
}

Graph::Graph(std::unordered_map<Vertex, std::vector<Vertex>> adjIn) {
    n = adjIn.size();
    pos.x = 0;
    pos.y = 0;
    adj = adjIn;
    for (auto& it : adj) {
        visited[it.first] = 0;
    }
}

Vertex Graph::getPos() {
    return pos;
}

std::vector<Vertex> Graph::getEdges(Vertex v) {
    return adj[v];
}

int Graph::getMaxEdges(Vertex v) {
    return max_edges[v];
}

bool Graph::getVisitedStatus(Vertex v) {
    return visited[v];
}

void Graph::setPos(Vertex posIn) {
    pos = posIn;
}

void Graph::setPos(int x, int y) {
    pos.x = x;
    pos.y = y;
}

void Graph::setMaxEdges(Vertex v, int edges) {
    max_edges[v] = edges;
}

void Graph::addVertex(Vertex v) {
    adj[v] = {};
    visited[v] = 0;
}

void Graph::addVertex(int x, int y) {
    Vertex v(x, y);
    addVertex(v);
}

void Graph::addEdge(Vertex v1, Vertex v2) {
    adj[v1].push_back(v2);
    adj[v2].push_back(v1);
}

void Graph::setAsVisited(Vertex v) {
    visited[v] = 1;
}

void Graph::evalPath() {
    /*
    Quick pseudocode for DFS path generation

    while (!stack.empty()) {
        bool up = detectPathUp()
        bool right = detectPathRight()
        bool down = detectPathDown()
        bool left = detectPathLeft()

        if (right) {
            stack.push(pos)
            addEdge(pos, pos+1)
            pos++
            goRight()
            
        } else if (down) {
        ""
        } else if (up) {
            ""
        } else if (left) {
            ""
        }
    
    */
}

#endif