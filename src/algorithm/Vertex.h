#ifndef VERTEX
#define VERTEX

struct Vertex
{
    // Variables
    int x;
    int y;

    // Variables with default values
    String color;       // Square color
    bool visited;      // Has the vertex been visited?

    // Variables always initialized with default values
    // Array of size 4 of pointers to vertices, each for a direction to other adjacent vertices objects
    // [0] - right, [1] - up, [2] - left, [3] - down
    Vertex *adj[4] = {nullptr, nullptr, nullptr, nullptr};

    // Constructors
    Vertex(int xIn, int yIn, String colorIn);
    Vertex(int xIn, int yIn);
    Vertex();

    // Methods
    Vertex up();
    Vertex down();
    Vertex left();
    Vertex right();
    String direction(Vertex &v);
    void addEdge(Vertex *v, String direction);

    int distance(Vertex v);
    String coords();

    // Operators
    bool operator==(const Vertex &v) const;
};

// Constructor specifying coordinates and color of the vertex
Vertex::Vertex(int xIn, int yIn, String colorIn) : x(xIn), y(yIn), color(colorIn), visited(false) {}

// Constructor specifying only the coordinates of the vertex
Vertex::Vertex(int xIn, int yIn) : x(xIn), y(yIn), color(""), visited(false) {}

// Default constructor that initializes default values for every attribute
Vertex::Vertex() : x(0), y(0), color(""), visited(false) {}

// The up(), down(), left(), and right() methods return a Vertex object of coordinates in that direction
Vertex Vertex::up() { return Vertex(x, y + 1); }
Vertex Vertex::down() { return Vertex(x, y - 1); }
Vertex Vertex::left() { return Vertex(x - 1, y); }
Vertex Vertex::right() { return Vertex(x + 1, y); }

// Specify an adjacent vector and return the direction to which it is found
String Vertex::direction(Vertex &v)
{
    if (left() == v) {
        return "left";
    } else if (up() == v) {
        return "up";
    } else if (right() == v) {
        return "right";
    } else if (down() == v) {
        return "down";
    } else {
        return "";
    }
}

// Add an undirected edge between the object and a Vertex v
void Vertex::addEdge(Vertex *v, String direction)
{
    if (direction == "right") {
        adj[0] = v;
        v->adj[2] = this;
    } else if (direction == "up") {
        adj[1] = v;
        v->adj[3] = this;
    } else if (direction == "left") {
        adj[2] = v;
        v->adj[0] = this;
    } else if (direction == "down") {
        adj[3] = v;
        v->adj[1] = this;
    }
}

// Amount of edges needed to get to a discoverable Vertex v
int Vertex::distance(Vertex v)
{
    int dist = x - v.x + y - v.y;
    if (dist < 0) {
        return dist * (-1);
    } else {
        return dist;
    }
}

// Return the formatted coordinates
String Vertex::coords()
{
    String str;
    str.concat("(");
    str.concat(x);
    str.concat(", ");
    str.concat(y);
    str.concat(")");
    return str;
}

// Two vertices are the same if their coordinates are the same, which is their "naming convention"
bool Vertex::operator==(const Vertex &v) const
{
    return (x == v.x && y == v.y);
}

#endif