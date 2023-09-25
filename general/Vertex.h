#ifndef VERTEX
#define VERTEX

#include <sstream>
#include <cmath>
#include <string>
#include <map>

struct Vertex
{
    // Variables
    int x;
    int y;

    // Variables with default values
    std::string color; // Square color
    bool visited;      // Has the vertex been visited?
    int max_edges;     // Maximum possible edges to other vertices, -1 = no limit

    // Variables always initialized with default values

    // Map of 4 pointers that point to connected vertices on all directions
    std::map<std::string, Vertex *> adj;

    // Constructors
    Vertex(int xIn, int yIn, std::string colorIn, int max_edgesIn);
    Vertex(int xIn, int yIn, int max_edgesIn);
    Vertex(int xIn, int yIn);
    Vertex();

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

// Constructor specifying coordinates, color, and max_edges of the vertex
Vertex::Vertex(int xIn, int yIn, std::string colorIn, int max_edgesIn) : x(xIn), y(yIn), color(colorIn), max_edges(max_edgesIn) {
    visited = false;
    adj["right"] = nullptr;
    adj["down"] = nullptr;
    adj["up"] = nullptr;
    adj["left"] = nullptr;
}

// Constructor specifying only the coordinates and max_edges of the vertex, uses the constructor above
Vertex::Vertex(int xIn, int yIn, int max_edgesIn) : Vertex(xIn, yIn, "", max_edgesIn) {}

// Constructor specifying only the coordinates of the vertex, uses the constructor above
Vertex::Vertex(int xIn, int yIn) : Vertex(xIn, yIn, -1) {}

// Default constructor uses constructor above
Vertex::Vertex() : Vertex(0, 0) {}

// The up(), down(), left(), and right() methods return a Vertex object of coordinates in that direction
Vertex Vertex::up() { return Vertex(x, y + 1); }
Vertex Vertex::down() { return Vertex(x, y - 1); }
Vertex Vertex::left() { return Vertex(x - 1, y); }
Vertex Vertex::right() { return Vertex(x + 1, y); }

// Amount of edges needed to get to a discoverable Vertex v
int Vertex::distance(Vertex v) { return abs(x - v.x + y - v.y); }

// Return the formatted coordinates
std::string Vertex::coords()
{
    std::stringstream ss;
    ss << "(" << x << ", " << y << ")";
    std::string coordinates = ss.str();
    return coordinates;
}

// Two vertices are the same if their coordinates are the same, which is their "naming convention"
bool Vertex::operator==(const Vertex &v) const { return (x == v.x && y == v.y); }

#endif