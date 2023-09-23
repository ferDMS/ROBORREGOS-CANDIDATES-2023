#include <iostream>
#include "../general/Graph.hpp"
#include <stack>
#include <sstream>

void zoneA(Graph& g) 
{    
    std::stack<Vertex> stack;
    stack.push(g[0]);
    Vertex v;
    int counter = 0;

    while (!stack.empty())
    {
        v = stack.top();
        stack.pop();

        if (!v.visited)
        {
            std::cout << counter << ". " << v.coords() << std::endl;
            v.visited = true;
        }
    }
}

void zoneAEdgeInit(Graph& g, std::string& adj_string) {
    Vertex v;
    int i = 0;
    int j = 1;
    std::stringstream ss(adj_string);
    std::string word;

    while (std::getline(ss, word, ',')) {
        // Define the new vertex to which assign edges
        v = g.get(Vertex(i,j));
        std::cout << "i=" << i << ", j=" << j << std::endl;
        std::cout << &v << std::endl;
        // Assign the edges specified on the string
        if (word.find('l') != std::string::npos) { v.adj.push_back(  &g.get( v.left()  )  ); }
        if (word.find('r') != std::string::npos) { v.adj.push_back(  &g.get( v.right() )  ); }
        if (word.find('u') != std::string::npos) { v.adj.push_back(  &g.get( v.up()    )  ); }
        if (word.find('d') != std::string::npos) { v.adj.push_back(  &g.get( v.down()  )  ); }
        // Go to the next row
        j--;
        // If we passed the last row, go to the next column and restart row to the top
        if (j == -2) {
            j = 1;
            i--;
        }

        std::cout << "Vertex " << v.coords() << ":\t";
        for (int j = 0; j < v.adj.size(); j++)
        {
            std::cout << &v.adj[j] << "\t";
        }
        std::cout << "\n";
    }
}


int main()
{
    // Initialize a graph object through the default constructor
    Graph g(16);

    // Add the test case vertices
    g[0] = Vertex(0, 1, "green", 2);
    g[1] = Vertex(0, 0, "yellow", 3);
    g[2] = Vertex(0, -1, "red", 2);
    g[3] = Vertex(-1, 1, "blue", 3);
    g[4] = Vertex(-1, 0, "red", 4);
    g[5] = Vertex(-1, -1, "green", 3);
    g[6] = Vertex(-2, 1, "red", 3);
    g[7] = Vertex(-2, 0, "blue", 4);
    g[8] = Vertex(-2, -1, "blue", 3);
    g[9] = Vertex(-3, 1, "black", 3);
    g[10] = Vertex(-3, 0, "green", 4);
    g[11] = Vertex(-3, -1, "red", 3);
    g[12] = Vertex(-4, 1, "blue", 3);
    g[13] = Vertex(-4, 0, "blue", 3);
    g[14] = Vertex(-4, -1, "green", 2);
    g[15] = Vertex(-5, 1, "cyan", 1);

    // Define edges between vertices as a formatted string
    // The order of vertices matches the order above, and their coordinates
    // l = left, d = down, u = up, r = right
    std::string adj_string = "ld,ud,lu,ldr,uld,ur,lr,lr,l,rd,lurd,ulr,d,ru,r,r";
    zoneAEdgeInit(g, adj_string);

    // Display edges of all vertices
    for (int i = 0; i < g.n; i++)
    {
        std::cout << "Vertex " << g[i].coords() << ":\t";
        for (int j = 0; j < g[i].adj.size(); j++)
        {
            std::cout << &g[i].adj[j] << "\t";
        }
        std::cout << "\n";
    }
    

    return 0;
}
