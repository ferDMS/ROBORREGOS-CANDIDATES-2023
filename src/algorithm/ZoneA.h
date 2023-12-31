#ifndef GRAPH_H
#define GRAPH_H
#include "Graph.h"
#endif

#ifndef ARDUINOSTL_H
#define ARDUINOSTL_H
#include "ArduinoSTL.h"
#endif

#ifndef ROBOT_H
#define ROBOT_H
#include "Robot.h"
#endif

#include <stack>

void zoneA(Robot &r)
{
    // At the start of zoneA the robot always starts facing left, and in the middle of the starting square
    r.facing = "down";

    // Initialize the counters for each color
    int red = 0;
    int green = 0;
    int blue = 0;
    bool k_found = 0;

    // Vertex location of the black square (defined once it is found)
    Vertex k_vertex;

    // Define the minimum ultrasonic detected distance at which an adjacent vertex can be detected
    double min_adj = 20.0;

    // Initializing each vertex with coordinate values
    std::vector<Vertex> vertices;
    for (int i = 0; i > -5; i--) {
        for (int j = 1; j > -2; j--) {
            vertices.push_back(Vertex(i,j));
        }
    }
    vertices.push_back(Vertex(-5, 1));
    vertices[1].color = "yellow";

    // Graph object to save the map of the 16 vertices present in ZoneA
    Graph g(vertices);

    Serial.println("Initialized graph");

    // Stack of vertices. The top vertex is the one the robot should be standing in.
    std::stack<Vertex *> stack;

    // Pointer to memory space of the previously visited vertex
    // Initial value is the vertex where the Zone starts $S$
    Vertex *prev_v = &g[1];

    // Push the root vertex $S$ to the stack
    stack.push(prev_v);

    // Loop while there are still vertices left to visit (while the stack isn't empty) except for the final ramp checkpoint
    // When the while loop ends, the only remaining vertex to visit will be the ramp checkpoint vertex
    // In the loop we basically:
        // 1. Get next unvisited vertex (top vertex) and mark it as visited ($E$ square exception)
        // 2. Calculate a path to the vertex and make the robot follow it (black square exception)
        // 3. Get the color of the square, increment count, and display it with the RGB LED
        // 4. Detect the adjacent vertices (black square adj exception)
        // 5. Add unvisited adj vertices to stack in correct priority order
        // 6. Save current vertex as previous vertex for next path calculation and next iteration

    Serial.println("Starting DFS traversal");
    while (!stack.empty())
    {


        // 1. Get next unvisited vertex (top vertex) and mark it as visited ($E$ square exception)
        // --------------------------------------------------------------------------------------
        // Assign the vertex that the robot is going to move to as the current vertex.
        Vertex *v = stack.top();

        // Remove the vertex from the stack as it is going to be visited this iteration
        stack.pop();

        Serial.print("Starting loop iteration with Vertex: ");
        Serial.println(v->coords());

        // If the vertex to move to is the final ramp checkpoint vertex then we skip the iteration
        // to continue with the rest of the vertices before leaving Zone A.
        if (v == g.get(Vertex(-5, 1))) { continue; }

        // The stack should only contain unvisited vertices, except for vertices found two times from different edges
        // To avoid visiting repeated vertices more than once, we skip the iteration if the vertex is visited
        if (v->visited) { continue; }
        
        // Mark the unvisited vertex as visited
        // Doing this after the final checkpoint skip condition allows the ramp vertex to remain as unvisited
        v->visited = true;


        // 2. Calculate a path to the vertex and make the robot follow it (black square exception)
        // --------------------------------------------------------------------------------------
        // If the source vertex is exactly the same as the destination vertex then we do nothing
        if (!(prev_v == v))
        {
            // Find vertex path to the destination vertex
            std::vector<Vertex *> path_v = g.findPath(*prev_v, *v);

            // Conversion of the vertex path into a direction and distance path
            // Starts at 1 because the path returned by the findPath method includes the source at index 0, for which no moves are necessary
            std::vector< std::pair<String, double> > path_d = r.convertPath(path_v);

            // Turn off the led before we leave the current vertex so that it can be turned on again when arriving to the destination vertex
            r.rgb("black");

            Serial.println("Moving to current vertex");

            // Make the robot follow the path up to one vertex before the destination (if there is such path)
            // These moves will be simple face() and move() methods. 
            for (int i = 0; i < path_d.size() - 1; i++)
            {
                // Function to make the robot look forward to the next path move
                r.face(path_d[i].first);
                // Function to make the robot move the distance specified on the path
                r.move(path_d[i].second);
            }

            // Make the robot slowly traverse to the destination vertex while it checks its color sensor (to detect a black square rapidly)
            // The last element of the path vector will always be the destination, so smartColorMove() should only be applied to this last element
        
            // Function to make the robot look forward to the destination vertex
            r.face(path_d[path_d.size()-1].first);
            // Function to make the robot move to the destination but go back if the square is black 
            bool valid_move = r.smartColorMove(path_d[path_d.size()-1].second, "black");
            if (!valid_move) {
                // Set the black square as found
                k_found = 1;
                // Save the coordinates of the black square
                k_vertex = *path_v[path_v.size()-1];
                // Whatever distance was traversed, go back in reverse
                r.move((-1.0) * r.last_traversed);
                // Skip current iteration as the objective of this iteration was only to gain info about black square
                continue;
            }
        }

        Serial.println("Moved to the current vertex");

        // 3. Get the color of the just-visited vertex and display it with the RGB LED
        // ---------------------------------------------------------------------------
        // The RGB LED should already be showing the color with the smartColorMove() method to make it visible for longer
        // bit incase it didn't correctly detect the color change, the RGB LED is still turned on here

        // Read color sensor value
        r.getColor();
        // Increment counter of detected color
        if (r.color == "red") { red++; }
        else if (r.color == "green") { green++; }
        else if (r.color == "blue") { blue++; }
        // Display detected color in RGB LED
        r.rgb(r.color);
        // Small delay to make visible the LED's color (precaution if the code runs really fast through the next operations)
        // TODO: UNCOMMENT
        delay(1000);

        Serial.println("Got color and displayed it");


        // 4. Detect the adjacent vertices (black square adj exception)
        // ------------------------------------------------------------
        // It is not necessary to measure adjacent vertices backwards because the robot moves forward and has knowledge of the vertex behind it
        
        // Get distances of the robot in every direction
        r.getAllDistances();

        Serial.print("Got the following adjacent sides vertices: ");

        // If distance to nearest surface is more than min_adj (in cm) and the black square has not been found, then that is a possible path = adjacent vertex
        // or if the black square has been found, then its coordinates must not match the adjacent vertex coordinates to be a possible path

        if ( ( r.left_d > min_adj && !k_found ) || ( r.left_d > min_adj && k_found && !(k_vertex == v->left()) ) ) {
            v->addEdge( g.get(v->left()) , "left");
            Serial.print(v->left().coords());
            Serial.print("   ");
        }
        if ( ( r.up_d > min_adj && !k_found ) || ( r.up_d > min_adj && k_found && !(k_vertex == v->up()) ) ) {
            v->addEdge( g.get(v->up()) , "up");
            Serial.print(v->up().coords());
            Serial.print("   ");
        }
        if ( (r.right_d > min_adj && !k_found) || ( r.right_d > min_adj && k_found && !(k_vertex == v->right()) ) ) {
            v->addEdge( g.get(v->right()) , "right");
            Serial.print(v->right().coords());
            Serial.println("   ");
        }
        if ( (r.down_d > min_adj && !k_found) || ( r.down_d > min_adj && k_found && !(k_vertex == v->down()) ) ) {
            v->addEdge( g.get(v->down()) , "down");
            Serial.print(v->down().coords());
            Serial.println("   ");
        }


        // 5. Add unvisited adj vertices to stack in correct priority order
        // ----------------------------------------------------------------
        // The order to add to the stack should be the reverse of the order we want to follow, because a stack's order is LIFO.
        // This means that the order to add the adjacent vertices should be left -> up -> down -> right.

        // Loop for every direction that might have adjacent vertices, in order

        // If there is an adjacent vertex in that direction and it is unvisited, then we schedule it for a visit (add to stack)
        if (v->adj[2] != nullptr && !v->adj[2]->visited) {
            stack.push(v->adj[2]);  // Left
        }
        if (v->adj[1] != nullptr && !v->adj[1]->visited) {
            stack.push(v->adj[1]);  // Up
        }
        if (v->adj[3] != nullptr && !v->adj[3]->visited) {
            stack.push(v->adj[3]);  // Down
        }
        if (v->adj[0] != nullptr && !v->adj[0]->visited) {
            stack.push(v->adj[0]);  // Right
        }

        Serial.println("Added unvisited adjacent vertices to stack");


        // 6. Save current vertex as previous vertex for next path calculation and next iteration
        // --------------------------------------------------------------------------------------
        prev_v = v;

        Serial.println("Restarting loop");
    }


    // 7. Calculate and traverse path to closest unique color (5 total appearances) vertex and turn on RGB LED with color
    // ------------------------------------------------------------------------------------------------------------------

    
    // std::vector<Vertex *> path = g.findPath(&prev_v, Vertex(-4, 1));

    // TODO: CALCULATE AND TRAVERSE PATH TO VERTEX(-4,1)
    // TODO: MOVE TO FINISH CHECKPOINT AND GRAB CUBE

    // Move to the finish checkpoint
    // face("left");
    // move(18.0);
    // grab();
    // move(12.0);
    // face("down");
}