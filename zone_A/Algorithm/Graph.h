#ifndef GRAPH
#define GRAPH

class Graph {
    private:
        // Number of vertices
        int num_v;
        // Vertex position of robot
        int pos;
        // Adjacency list (edges of each vertex)
        vector<int> adj[num_v];

    public:
        // Constructors
        Graph(int v);
        // Add an undirected edge between two vertices
        void addEdge(int v1, int v2);
};

Graph::Graph(int v) {
    this->num_v = v;
    // The graph expands from the starting vertex (0)
    this->pos = 0;
}

#endif