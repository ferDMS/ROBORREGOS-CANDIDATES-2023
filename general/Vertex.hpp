#ifndef VERTEX
#define VERTEX

#include <cmath>

struct Vertex {
    // Variables
    int x;
    int y;
    // Constructors
    Vertex();
    Vertex(int xIn, int yIn);
    // Methods
    Vertex up();
    Vertex down();
    Vertex left();
    Vertex right();
    unsigned int distance(Vertex v);
    // Operators
    bool operator==(Vertex v);
};

Vertex::Vertex() {}

Vertex::Vertex(int xIn, int yIn) {
    x = xIn;
    y = yIn;
}

Vertex Vertex::up() {
    Vertex v(x, y+1);
    return v;
}

Vertex Vertex::down() {
    Vertex v(x, y-1);
    return v;
}

Vertex Vertex::left() {
    Vertex v(x-1, y);
    return v;
}

Vertex Vertex::right() {
    Vertex v(x+1, y);
    return v;
}

unsigned int Vertex::distance(Vertex v) {
    return abs(x - v.x + y - v.y);
}

bool Vertex::operator==(Vertex v) {
    return (x == v.x && y == v.y);
}

#endif VERTEX