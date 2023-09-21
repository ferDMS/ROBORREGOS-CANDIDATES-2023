#ifndef VERTEX
#define VERTEX

#include <cmath>
#include <string>
#include <functional>

struct Vertex {
    // Variables
    int x;
    int y;
    std::string color;  // See documentation for colors table
    // Constructors
    Vertex();
    Vertex(int xIn, int yIn);
    Vertex(int xIN, int yIn, std::string colorIn);
    // Methods
    Vertex up();
    Vertex down();
    Vertex left();
    Vertex right();
    unsigned int distance(Vertex v);
    // Operators
    bool operator==(const Vertex& v) const;
};

template<>
struct std::hash<Vertex> {
    std::size_t operator()(const Vertex& v) const {
        return std::hash<int>()(v.x) ^ std::hash<int>()(v.y);
    }
};

Vertex::Vertex() {
    x = -1;
    y = -1;
    color = "";
}

Vertex::Vertex(int xIn, int yIn) {
    x = xIn;
    y = yIn;
    color = "";
}

Vertex::Vertex(int xIn, int yIn, std::string colorIn) {
    x = xIn;
    y = yIn;
    color = colorIn;
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

bool Vertex::operator==(const Vertex& v) const {
    return (x == v.x && y == v.y);
}

#endif