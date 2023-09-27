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

    // Variables always initialized with default values
    // Map of 4 pointers that point to connected vertices on all directions
    std::map<int, Vertex *> adj;

    // Constructors
    Vertex(int xIn, int yIn, std::string colorIn);
    Vertex(int xIn, int yIn);
    Vertex();

    // Methods
    Vertex up();
    Vertex down();
    Vertex left();
    Vertex right();
    int dir(Vertex v);
    void addEdge(Vertex *v, int direction);

    int distance(Vertex v);
    std::string coords();

    // Operators
    bool operator==(const Vertex &v) const;
};

// Constructor specifying coordinates and color of the vertex
Vertex::Vertex(int xIn, int yIn, std::string colorIn) : x(xIn), y(yIn), color(colorIn), visited(false) {}

// Constructor specifying only the coordinates of the vertex, uses the constructor above
Vertex::Vertex(int xIn, int yIn) : x(xIn), y(yIn), color(""), visited(false) {}

// Default constructor that initializes default values for every attribute
Vertex::Vertex() : x(0), y(0), color(""), visited(false) {}

// The up(), down(), left(), and right() methods return a Vertex object of coordinates in that direction
Vertex Vertex::up() { return Vertex(x, y + 1); }
Vertex Vertex::down() { return Vertex(x, y - 1); }
Vertex Vertex::left() { return Vertex(x - 1, y); }
Vertex Vertex::right() { return Vertex(x + 1, y); }

// Specify an adjacent vector and return the direction to which it is found
int Vertex::dir(Vertex v)
{
    if (left() == v)
    {
        return 180;
    }
    else if (up() == v)
    {
        return 90;
    }
    else if (right() == v)
    {
        return 0;
    }
    else if (down() == v)
    {
        return 270;
    }
    else
    {
        return 1;
    }
}

// Add an undirected edge between the object and a Vertex v
void Vertex::addEdge(Vertex *v, int direction) {
    adj[direction] = v;
    v->adj[(direction + 180) % 360] = this;
}

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
bool Vertex::operator==(const Vertex &v) const
{
    return (x == v.x && y == v.y);
}

#endif