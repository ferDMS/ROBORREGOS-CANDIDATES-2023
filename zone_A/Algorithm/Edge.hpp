#ifndef EDGE
#define EDGE

#include "Vertex.hpp"

struct Edge {
    // Variables
    Vertex u; // Origin 
    Vertex v; // Destination
    int weight;
    // Constructors
    Edge();
    Edge(Vertex uIn, Vertex vIn);
    Edge(Vertex uIn, Vertex vIn, int weightIn);
    // Methods
    Edge reversed();
    Edge reversed(int weightIn);
    // Operators
    bool operator>(Edge e);
    bool operator<(Edge e);
    bool operator==(Edge e);
};

Edge::Edge() {}

Edge::Edge(Vertex uIn, Vertex vIn) {
    u = uIn;
    v = vIn;
    weight = 0;
}

Edge::Edge(Vertex uIn, Vertex vIn, int weightIn) {
    u = uIn;
    v = vIn;
    weight = weightIn;
}

Edge Edge::reversed() {
    return Edge(v, u, weight);
}

Edge Edge::reversed(int weightIn) {
    return Edge(v, u, weightIn);
}

bool Edge::operator==(Edge e) {
    return ((u == e.u && v == e.v && weight == e.weight) || 
            (u == e.v && v == e.u && weight == e.weight));
}

bool Edge::operator>(Edge e) {
    return weight > e.weight;
}

bool Edge::operator>(Edge e) {
    return weight < e.weight;
}

#endif EDGE