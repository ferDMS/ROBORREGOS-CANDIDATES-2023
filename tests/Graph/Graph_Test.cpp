#include <iostream>
#include "../../general/Graph.h"

int main() {
    // Create a default graph
    Graph g;

    // Add vertices to the graph
    g.add(Vertex(0,0,"yellow",3));
    g.add(Vertex(2,2));
    g.add(Vertex(4,4));

    // Print the coordinates of the vertices
    std::cout << "Vertex 0: (" << g[0].x << ", " << g[0].y << ")" << std::endl;
    std::cout << "Vertex 1: (" << g[1].x << ", " << g[1].y << ")" << std::endl;
    std::cout << "Vertex 2: (" << g[2].x << ", " << g[2].y << ")" << std::endl;

    // Test graph's attributes
    std::cout << "Number of vertices in graph is " << g.n << std::endl;

    // Test the up(), down(), left(), and right() methods and the [] overload
    g[0] = g[0].up().right();
    g[0].color = "yellow";  // Giving back its attribute
    std::cout << "Reassigning Vertex 0 shifted up and right: " << g[0].coords() << std::endl;
    g[2] = g[2].down().left();
    g[2].max_edges = 2;  // Giving it a new attribute
    std::cout << "Reassigning Vertex 2 shifted down and left: " << g[2].coords() << std::endl;

    // Test the distance() method
    int dist = g[0].distance(g[2]);
    std::cout << "Distance between vertex 0 and vertex 2: " << dist << std::endl;

    // Test the operator== overload
    std::cout << "g[0] == g[1]: " << (g[0] == g[1]) << std::endl;
    std::cout << "g[1] == g[2]: " << (g[1] == g[2]) << std::endl;
    
    // Test the coords() method
    for (int i = 0; i < 3; i++) {
        std::cout << "Vertex " << i << ": " << g[i].coords() << std::endl;
    }
    // Test combination of methods
    std::cout << "g[0].right().up() == g[2].left().down(): " << (g[0].right().up() == g[2].left().down()) << std::endl;

    // Test default constructor of Vertex and get() method
    // std::cout << "g[0]'s color is " << g.get(Vertex())->color << std::endl;
    
    // Test default constructor of Vertex and get() method
    Vertex* v = g.get(Vertex(1,1));
    std::cout << "g[0]'s color is " << v->color << std::endl;
    
    return 0;
}
