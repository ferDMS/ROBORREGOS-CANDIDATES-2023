#ifndef ARDUINOSTL_H
#define ARDUINOSTL_H
#include "ArduinoSTL.h"
#endif

#ifndef GRAPH_H
#define GRAPH_H
#include "Graph.h"
#endif

#ifndef ROBOT_H
#define ROBOT_H
#include "Robot.h"
#endif

#include <stack>

void testZoneA(Graph &g)
{
    std::stack<Vertex *> stack; // Stack of paused vertices
    stack.push(&g[1]);          // Push the root vertex $S$
    Vertex *v;                  // Pointer to memory space of visited vertex
    int counter = 1;            // Counter of visited vertices
    String str_path;
    str_path.reserve(300);

    // Loop while there are still vertices not completely explored (i.e.: while there is a paused vertex)
    while (!stack.empty())
    {
        // Assign the last-in vertex as the vertex to explore
        v = stack.top();

        // Remove the vertex from the stack as it is now going to be explored
        stack.pop();

        // If it is the first time we visit the vertex then it is marked as visited
        if (!v->visited) {
            str_path.concat(counter);
            str_path.concat(". ");
            str_path.concat(v->coords());
            str_path.concat("   ");
            Serial.println(str_path);
            str_path = "";
            v->visited = true;
        }
        // Go through every possible adjacent vertex and schedule it for a visit if it hasn't been visited.
        // The order to add to the stack should be the reverse of the order we want to follow,
        // because a stack's order is LIFO. This means that the order to add the adjacent vertices should be
        // left -> up -> down -> right.
        if (v->adj[2] != nullptr && !v->adj[2]->visited) {
            stack.push(v->adj[2]);
        }
        if (v->adj[1] != nullptr && !v->adj[1]->visited) {
            stack.push(v->adj[1]);
        }
        if (v->adj[3] != nullptr && !v->adj[3]->visited) {
            stack.push(v->adj[3]);
        }
        if (v->adj[0] != nullptr && !v->adj[0]->visited) {
            stack.push(v->adj[0]);
        }

        counter++;
    }
}

void zoneAEdgeInit(Graph &g, char adj_string[79])
{
    Vertex *vptr;
    int i = 0;
    int j = 1;
    String word;

    for (int k = 0; k<79; k+=5) {

        vptr = g.get(Vertex(i, j));
        
        if ('l' == adj_string[k] || 'l' == adj_string[k+1] || 'l' == adj_string[k+2] || 'l' == adj_string[k+3]) {
            vptr->adj[2] = g.get(vptr->left());
        }
        if ('u' == adj_string[k] || 'u' == adj_string[k+1] || 'u' == adj_string[k+2] || 'u' == adj_string[k+3]) {
            vptr->adj[1] = g.get(vptr->up());
        }
        if ('d' == adj_string[k] || 'd' == adj_string[k+1] || 'd' == adj_string[k+2] || 'd' == adj_string[k+3]) {
            vptr->adj[3] = g.get(vptr->down());
        }
        if ('r' == adj_string[k] || 'r' == adj_string[k+1] || 'r' == adj_string[k+2] || 'r' == adj_string[k+3]) {
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
    char adj_string[79] = "ld  ,ud  ,lu  ,ldr ,uld ,ur  ,lr  ,lr  ,l   ,rd  ,lurd,ulr ,d   ,ru  ,r   ,r   ";
    //       Vertex #          0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15

    // Function to initialize the edges based on the formatted string.
    zoneAEdgeInit(g, adj_string);

    // Display edges of all vertices
    for (int i = 0; i < g.n; i++)
    {
        // Serial.println( String("Vertex " + g[i].coords() + ": ") );

        // For every possible edge found for vertex i
        for (int j = 0; j < 4; j++)
        {
            // If it is not a nullptr (nullptr is means the edge doesn't exist)
            if (g[i].adj[j])
            {
                // Serial.println( String(g[i].adj[j]->coords() + " ") );
            }
        }
        // Serial.println();
    }
}
