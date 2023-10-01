#ifndef GRAPH_H
#define GRAPH_H
#include "Graph.h"
#endif

#ifndef ROBOT_H
#define ROBOT_H
#include "Robot.h"
#endif

void zoneB(Robot &r)
{
    // At the start of zoneB the robot always starts facing right, and in the middle of the starting square
    r.facing = "right";

    // Initializing each vertex with coordinate values
    std::vector<Vertex> vertices;
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j > -2; j--) {
            vertices.push_back(Vertex(i,j));
        }
    }
    
    vertices.push_back(Vertex(0, 0));
    vertices[15].color = "pink";

    // Graph object to save the map of the 16 vertices present in ZoneB
    Graph g(vertices);

    double from_middle = 20.0;

    r.getAllDistances();
    r.move(30.0);

    for (int i = 1; i < 4; i++) {
        r.face("up");
        r.move(from_middle);
        r.getColor();
        g.get(Vertex(i,1))->color = r.color;
        r.move((-1.0) * from_middle);
        r.face("down");
        r.move(from_middle);
        r.getColor();
        g.get(Vertex(i,-1))->color = r.color;
        r.move((-1.0) * from_middle);
        r.face("right");
        r.move(from_middle);
    }

    r.face("down");
    r.move(from_middle);
    r.getColor();
    g.get(Vertex(4,-1))->color = r.color;
    r.move((-1.0) * from_middle);
    r.face("right");
    r.move(from_middle);
    r.getColor();
    g.get(Vertex(5,0))->color = r.color;

    r.move(-120.0 - from_middle);
}