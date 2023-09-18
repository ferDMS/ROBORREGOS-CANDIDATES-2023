# Edge Structure

On a graph, an edge is a link or connection between 2 vertices. Its most basic elements are:

* Two connected vertices
* [Direction](#direction)
* [Weight](#weight)

The [Edge](./Edge.MD) structure defines directed edges that can be assigned a weight.

## Direction

When defining a directed edge it is necessary that both endpoints are saved and separated, one as the source vertex `u`, and the other as the destination vertex `v`. These are saved as [Vertex](./Vertex.MD) objects, defined as:

```cpp
Vertex u;  // Source
Vertex v;  // Destination
```

## Weight

If a weight is not assigned when initializing an Edge object, the weight is set to $0$. This is the minimal and highest ranked weight. An [example on weight hierarchy](../zone_A/Approach.MD#weighting-edges) is detailed on Zone A's main approach document. The weight is saved in the structure as:

```cpp
int weight;
```

## Operations

Edges must be able to be sorted by their weight as some should have higher priority over others. Operator overloading of `>` and `<` is implemented on the structure definition in order to achieve this.

Since the majority, if not all, of the competition map graph data structure comprises undirected edges, there should exist a straightforward method for reversing an Edge $e$ and getting the source as the destination and viceversa. The `reversed()` method performs this operation and returns an Edge object with its direction reversed. To reverse a weighted edge, it is as simple as providing a weight argument to assign to the reversed edge object.

```cpp
// Same-weighted reversed edge
Edge reversed();
// Differently-weighted reversed edge
Edge reversed(int weightIn);
```

## [Implementation](./Edge.hpp)
