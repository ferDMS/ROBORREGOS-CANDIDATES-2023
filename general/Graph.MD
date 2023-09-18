# Graph Class

## Basic information

The implementation of classes is vital to solve the problem of saving data in structures that are easy to comprehend and easy to manipulate. By creating a Graph class one can separate all the variables and functions related to the robot's traversal on a single layout, creating multiple objects depending on the zone that the robot is located in.

The basic variables the graph should store are:

* [Number of vertices](#number-of-vertices)
* [Adjacency hashmap](#adjacency-hashmap)

The basic variables and methods that should be stored to explore the graph are:

* [Current vertex location](./Vertex.MD#naming-vertices)
* Zone A graph exploration related structures
  * [Stack](../zone_A/Algorithm/Research.MD#depth-first-search-dfs) (for DFS)
  * [Max edges of vertices](../zone_A/Algorithm/Approach.MD#maximum-possible-edges)
  * [Visited vertices](#visited-hashmap)

In order to correctly store the multiple attributes of the data, as well as operations and methods that can be applied to it, the structures [Vertex](./Vertex.MD) and [Edge](./Edge.MD) are defined. Both structures encompass their own distinctive elements according to what distinguishes them.

## Number of vertices

The total count of vertices can simply be stored as an integer `n`. It is important that this total count is updated continuously for graphs that discover new vertices.

## Adjacency hashmap

The adjacency hashmap `adj` is saved as an unordered map, a structure on C++ that maps keys to values. What is special about a hashmap is that you can input any kind of data type as a key. This works because what really is getting mapped is a the hash digest of the key data, after being passed through a hash function. If the key data changes by even one single bit, the hash digest completely changes.

The key is any vertex $v$, and its value is a vector of $v$'s edges. Using the previously mentioned structures, `adj` can be defined as

```cpp
std::unordered_map<Vertex, std::vector<Edge>> adj;
```

## Visited hashmap

To explore the entire graph, starting at vertex $S$ and ending at vertex $E$, regardless of the exploration algorithm used, a structure for saving already visited vertices is required. This is true as a graph can have loops and vertices which should not be visited more than a single time. A hashmap `visited` is used to fulfill this function.

The key is any vertex $v$, and its value is a boolean value.

- If $v$ has been visited, even if it has not been fully explored, the boolean value is set to $1$.
- If $v$ has not been visited, even if an edge has been found to said vertex, the boolean value is set to $0$

At the start, only the vertex $S$ is set as visited, as it is the starting point from which any exploration algorithm starts. `visited` can be defined as

```cpp
std::unordered_map<Vertex, bool> visited;
```

## [Implementation](./Graph.hpp)
