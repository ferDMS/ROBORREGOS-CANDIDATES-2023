// #ifndef ARDUINOSTL_H
// #define ARDUINOSTL_H
// #include "ArduinoSTL.h"
// #endif

#ifndef GRAPH_H
#define GRAPH_H
#include "Graph.h"
#endif

#include <iostream>

void testZoneA(Graph &g)
{
    std::stack<Vertex *> stack; // Stack of paused vertices
    stack.push(&g[1]);          // Push the root vertex $S$
    Vertex *v;                  // Pointer to memory space of visited vertex
    int counter = 1;            // Counter of visited vertices

    // Loop while there are still vertices not completely explored (i.e.: while there is a paused vertex)
    while (!stack.empty())
    {
        // Assign the last-in vertex as the vertex to explore
        v = stack.top();

        // Remove the vertex from the stack as it is now going to be explored
        stack.pop();

        // If it is the first time we visit the vertex then it is marked as visited
        if (!v->visited)
        {
            // Serial.print(counter);
            // Serial.print(". ");
            // Serial.println(v->coords());
            std::cout << counter << ". " << v->coords() << std::endl;
            v->visited = true;
        }

        // Go through every possible adjacent vertex and schedule it for a visit if it hasn't been visited.
        // The order to add to the stack should be the reverse of the order we want to follow,
        // because a stack's order is LIFO. This means that the order to add the adjacent vertices should be
        // left -> up -> down -> right.
        if (v->adj.count(180) != 0 && !v->adj[180]->visited) {
            stack.push(v->adj[180]);
        }
        if (v->adj.count(90) != 0 && !v->adj[90]->visited) {
            stack.push(v->adj[90]);
        }
        if (v->adj.count(270) != 0 && !v->adj[270]->visited) {
            stack.push(v->adj[270]);
        }
        if (v->adj.count(0) != 0 && !v->adj[0]->visited) {
            stack.push(v->adj[0]);
        }

        counter++;
    }
}

void zoneAEdgeInit(Graph &g, std::string &adj_string)
{
    Vertex *vptr;
    int i = 0;
    int j = 1;
    std::stringstream ss(adj_string);
    std::string word;

    while (std::getline(ss, word, ','))
    {
        // Define the new vertex to which assign edges
        vptr = g.get(Vertex(i, j));
        // Assign the edges specified on the string
        if (word.find('l') != std::string::npos) {
            vptr->adj[180] = g.get(vptr->left());
        }
        if (word.find('u') != std::string::npos) {
            vptr->adj[90] = g.get(vptr->up());
        }
        if (word.find('d') != std::string::npos) {
            vptr->adj[270] = g.get(vptr->down());
        }
        if (word.find('r') != std::string::npos) {
            vptr->adj[0] = g.get(vptr->right());
        }

        // Go to the next row
        j--;

        // If we passed the last row, go to the next column and restart row to the top
        if (j == -2)
        {
            j = 1;
            i--;
        }
    }
}

void zoneAGraphInit(Graph &g)
{
    // Add the test case vertices
    g[0] = Vertex(0, 1, "green");
    g[1] = Vertex(0, 0, "yellow");
    g[2] = Vertex(0, -1, "red");
    g[3] = Vertex(-1, 1, "blue");
    g[4] = Vertex(-1, 0, "red");
    g[5] = Vertex(-1, -1, "green");
    g[6] = Vertex(-2, 1, "red");
    g[7] = Vertex(-2, 0, "blue");
    g[8] = Vertex(-2, -1, "blue");
    g[9] = Vertex(-3, 1, "black");
    g[10] = Vertex(-3, 0, "green");
    g[11] = Vertex(-3, -1, "red");
    g[12] = Vertex(-4, 1, "blue");
    g[13] = Vertex(-4, 0, "blue");
    g[14] = Vertex(-4, -1, "green");
    g[15] = Vertex(-5, 1, "cyan");

    // Define edges between vertices as a formatted string from top-right to bottom-left
    // The order of vertices matches the order above, and their coordinates
    // l = left, d = down, u = up, r = right
    std::string adj_string = "ld  ,ud  ,lu  ,ldr ,uld ,ur  ,lr  ,lr  ,l   ,rd  ,lurd,ulr ,d   ,ru  ,r   ,r   ";
    //       Vertex #          0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15

    // Function to initialize the edges based on the formatted string.
    zoneAEdgeInit(g, adj_string);

    // Display edges of all vertices
    for (int i = 0; i < g.n; i++)
    {
        // Serial.print("Vertex ");
        // Serial.print(g[i].coords());
        // Serial.print(": ");
        std::cout << "Vertex " << g[i].coords() << ": ";

        // For every edge found for vertex i
        for (std::map<int, Vertex *>::iterator it = g[i].adj.begin(); it != g[i].adj.end(); ++it)
        {
            // If it is not a nullptr (nullptr is an edge to vertex K (black square))
            if (it->second)
            {
                // Serial.print(it->second->coords());
                // Serial.print(" ");
                std::cout << it->second->coords() << " ";
            }
        }
        // Serial.println();
        std::cout << "\n";
    }
}
