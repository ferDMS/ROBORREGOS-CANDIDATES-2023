#ifndef VERTEX
#define VERTEX

#include <cmath>
#include <string>

struct Vertex
{
    // Variables
    int x;
    int y;

    // Variables with default values
    std::string color;         // Square color
    std::vector<Vertex *> adj; // List of pointers that point to connected vertices
    bool visited;              // Has the vertex been visited?
    int max_edges;             // Maximum possible edges to other vertices, -1 = no limit

    // Constructors
    Vertex();
    Vertex(int xIn, int yIn);
    Vertex(int xIn, int yIn, std::string colorIn, int max_edgesIn);

    // Methods
    Vertex up();
    Vertex down();
    Vertex left();
    Vertex right();
    int distance(Vertex v);
    std::string coords();

    // Operators
    bool operator==(const Vertex &v) const;
};

// Default constructor
Vertex::Vertex() : x(0), y(0), color("white"), visited(false), max_edges(-1) {}

// Constructor specifying only the coordinates of the vertex
Vertex::Vertex(int xIn, int yIn) : x(xIn), y(yIn), color("white"), visited(false), max_edges(-1) {}

// Constructor specifying coordinates and color of the vertex
Vertex::Vertex(int xIn, int yIn, std::string colorIn, int max_edgesIn) : x(xIn), y(yIn), color(colorIn), visited(false), max_edges(max_edgesIn) {}

// The up(), down(), left(), and right() methods return the same Vertex object but shifted in that direction
Vertex Vertex::up() { return Vertex(x, y + 1); }
Vertex Vertex::down() { return Vertex(x, y - 1); }
Vertex Vertex::left() { return Vertex(x - 1, y); }
Vertex Vertex::right() { return Vertex(x + 1, y); }

// Amount of edges needed to get to a discoverable Vertex v
int Vertex::distance(Vertex v) { return abs(x - v.x + y - v.y); }

// Return the formatted coordinates
std::string Vertex::coords()
{
    std::string coordinates = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    return coordinates;
}

// Two vertices are the same if their coordinates are the same, which is their "naming convention"
bool Vertex::operator==(const Vertex &v) const { return (x == v.x && y == v.y); }

#endif