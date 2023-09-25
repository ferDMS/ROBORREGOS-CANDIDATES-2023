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

void getAdj(Robot &r, Graph &g, Vertex *v)
{

    // Pointer to auxiliary vertex
    Vertex *aux_v;

    // Get distances of the robot in every direction
    r.getDistances();

    // If distance to nearest surface is more than 10 cm, then that is a possible path = adjacent vertex
    if (r.left_d > 10.0)
    {
        aux_v = g.get(v->left());
        v->adj["left"] = aux_v;
        aux_v->adj["right"] = v;
    }

    if (r.up_d > 10.0)
    {
        aux_v = g.get(v->up());
        v->adj["up"] = aux_v;
        aux_v->adj["down"] = v;
    }

    if (r.right_d > 10.0)
    {
        aux_v = g.get(v->right());
        v->adj["right"] = aux_v;
        aux_v->adj["left"] = v;
    }

    // It is not necessary to measure adjacent vertices backwards because
    // the robot always moves forward, which means it has already mapped
    // the vertex behind it (it has passed it before).
}

void zoneA(Robot& r)
{
    // At the start of zoneA the robot always starts facing left, and in the middle of the starting square
    // r.facing(90)

    // Counter of visited vertices
    int v_counter = 0;

    // Initializing each vertex with coordinates and max_edges values
    std::vector<Vertex> vertices = {
        Vertex(0, 1, 2),
        Vertex(0, 0, "yellow", 3),
        Vertex(0, -1, 2),
        Vertex(-1, 1, 3),
        Vertex(-1, 0, 4),
        Vertex(-1, -1, 3),
        Vertex(-2, 1, 3),
        Vertex(-2, 0, 4),
        Vertex(-2, -1, 3),
        Vertex(-3, 1, 3),
        Vertex(-3, 0, 4),
        Vertex(-3, -1, 3),
        Vertex(-4, 1, 3),
        Vertex(-4, 0, 3),
        Vertex(-4, -1, 2),
        Vertex(-5, 1, 1)};

    // Graph object to save the map of the 16 vertices present in ZoneA
    Graph g(vertices);
    // Stack of vertices. The top vertex is the one the robot should be standing in.
    std::stack<Vertex *> stack;
    // Push the root vertex $S$ to the stack
    stack.push(&g[0]);
    // Pointer to memory space of visited vertex
    Vertex *v;
    // Pointer to memory space of auxiliary vertex (next vertex)
    Vertex *aux_v;
    // String to save the direction of the next movement
    int next_dir;

    // Loop while we are not at the square before the ramp checkpoint (i.e.: while 15 vertices haven't been visited)
    // When the while loop ends, the only remaining vertex in the stack will be the ramp checkpoint vertex
    while (v_counter != 15)
    {
        // Assign the vertex in which the robot is standing as the current vertex
        v = stack.top();
        // Remove the vertex from the stack as it is currently being visited
        stack.pop();
        // If it is the first time we visit the vertex then it is marked as visited
        if (!v->visited) {
            v_counter++;
            v->visited = true;
        }
        // Get possible paths / adjacent vertices by measuring the ultrasonics
        getAdj(r, g, v);

        // Go through every possible adjacent vertex and schedule it for a visit if it hasn't been visited.
        // The order to add to the stack should be the reverse of the order we want to follow,
        // because a stack's order is LIFO. This means that the order to add the adjacent vertices should be
        // left -> up -> down -> right.
        if (v->adj["left"] && !v->adj["left"]->visited) { stack.push(v->adj["left"]); }
        if (v->adj["up"] && !v->adj["up"]->visited) { stack.push(v->adj["up"]); }
        if (v->adj["down"] && !v->adj["down"]->visited) { stack.push(v->adj["down"]); }
        if (v->adj["right"] && !v->adj["right"]->visited) { stack.push(v->adj["right"]); }
        
        // Get the next vertex to visit in an auxiliary variable
        aux_v = stack.top();
        // Obtain direction to which the robot should move next
        next_dir = v->dir(*aux_v);


    }

    // Move to the finish checkpoint
    // face("left");
    // move(18.0);
    // grab();
    // move(12.0);
    // face("down");
}