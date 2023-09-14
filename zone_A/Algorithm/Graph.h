#ifndef GRAPH
#define GRAPH

# include <vector>
# include <stack>

class Graph {
    private:
        // Number of vertices
        int num_v;
        // Vertex position of robot
        int pos;
        // Adjacency array (index: vertex, values: connected vertices)
        std::vector<std::vector<int>> adj;
        // Stack of exploration paused vertices
        std::stack<int> stack;
        // Array of encountered or visited vertices
        std::vector<bool> visited;

    public:
        // Constructors
        Graph(int num_v);
        // Getters
        int getPos();
        std::vector<int> getEdges(int v);
        // Setters
        void addEdge(int v1, int v2);
        void setPos(int pos);
        // Other methods
        void evalPath();
};

Graph::Graph(int num_v) {
    this->num_v = num_v;
    this->pos = 0;  // Root = 0
    this->adj = {{}};
    this->visited = {0};
}

int Graph::getPos() {
    return pos;
}

std::vector<int> Graph::getEdges(int v) {
    return adj[v];
}

void Graph::addEdge(int v1, int v2) {
    adj[v1].push_back(v2);
    adj[v2].push_back(v1);
}

void Graph::setPos(int pos) {
    this->pos = pos;
}

void evalPath() {
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