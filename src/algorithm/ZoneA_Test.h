#ifndef ARDUINOSTL_H
#define ARDUINOSTL_H
#include "ArduinoSTL.h"
#endif

#ifndef GRAPH_H
#define GRAPH_H
#include "Graph.h"
#endif

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
        if (v->adj["left"] && !v->adj["left"]->visited)
        {
            stack.push(v->adj["left"]);
        }

        if (v->adj["up"] && !v->adj["up"]->visited)
        {
            stack.push(v->adj["up"]);
        }

        if (v->adj["down"] && !v->adj["down"]->visited)
        {
            stack.push(v->adj["down"]);
        }

        if (v->adj["right"] && !v->adj["right"]->visited)
        {
            stack.push(v->adj["right"]);
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
        if (word.find('l') != std::string::npos)
        {
            vptr->adj["left"] = g.get(vptr->left());
        }
        if (word.find('u') != std::string::npos)
        {
            vptr->adj["up"] = g.get(vptr->up());
        }
        if (word.find('d') != std::string::npos)
        {
            vptr->adj["down"] = g.get(vptr->down());
        }
        if (word.find('r') != std::string::npos)
        {
            vptr->adj["right"] = g.get(vptr->right());
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

Graph &zoneAGraphInit()
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

        // For every direction specified on the
        for (std::map<std::string, Vertex *>::iterator it = g[i].adj.begin(); it != g[i].adj.end(); ++it)
        {
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
