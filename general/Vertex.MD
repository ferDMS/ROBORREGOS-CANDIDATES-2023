# Vertex Structure

The only basic elements of a vertex are its name and its color. Its name is used to distinguish it from other vertices and the color for multiple tasks throughout the round.

## Naming Vertices

Vertices on a [Graph](Graph.MD) are usually named consequently after the root vertex, or in an arbitrary way. In the case of a regular graph, these names could be simple integer values that keep increasing for each vertex that is discovered or explored. This makes sense on graph structures that have a set amount of vertices to explore. However, on graphs that are continuously expanding, the task of naming newly discovered vertices can be demanding, especially when they have edges that create loops with already known vertices.

Solving this naming problem is easy when considering the general structure of the competition map. All vertices, even ones that are being constantly discovered and explored, always have octagonal edges (connections of $90\degree$). Considering this, the graph structure can be represented as a plane in two dimensions (2D), with values for the $x$ and $y$ axis. This way, a vertex is named as a coordinate system of both values.

Now, as the graph is being explored, through these $x$ and $y$ values it is easy to identify if the robot is returning to a known vertex, according to its coordinate name and edge direction on these axis. The coordinate name can be defined as a relative position to the origin of the 2D plane, which is the point of coordinates $(0,0)$. This origin can effectively be the starting point from which a graph is explored, and thus, the name of the starting vertex $S$ will always be set to $x=0$, $y=0$, and the remaining vertices according to their relative positioning.

## Saving names

Two variables are saved to represent the name of a vertex, one for each axis on the 2D plane:

```cpp
int x;
int y;
```

## Saving colors

A string variable `color` saves the name of the color according to the possible appearances in the different zones. The complete list of colors, with their corresponding color code values is defined below:

| Color String |   R   |   G   |   B   |  HEX   |
| :----------: | :---: | :---: | :---: | :----: |
|    white     |  255  |  255  |  255  | #FFFFF |

## Adjacent vertices

Because the graph is octogonal, an arbitrary vertex $v$ could have up to 4 adjacent vertices. These vertices can be defined in terms of $v$ as lower or higher on the $x$ and $y$ axis, as follows:

```cpp
v.up();  // Vertex(v.x, v.y+1)
v.down();  // Vertex(v.x, v.y-1)
v.left();  // Vertex(v.x-1, v.y)
v.right();  // Vertex(v.x+1, v.y)
```

## Distance between vertices

Obtaining the distance between a vertex $v$ and another reachable vertex can be helpful. For example, to obtain at which depth level a vertex is located with respect to the origin vertex $S$. The returned value is only the magnitude of the distance, represented as a single unsigned integer.

```cpp
unsigned int distance(Vertex v);
```

## Hash function definition

Since the [Graph](./Graph.MD) class uses hashmaps with Vertex objects as keys, the objects must be passed through a hashing function in order to convert them to a usable hash digest key. The [C++ standard library's hash structure](https://en.cppreference.com/w/cpp/utility/hash) requires that every hashed data type describes its precise attributes that should be used to construct the hash. Because vertices will never have the same `x` and `y` locations (unless if they are in different graph objects), these two variables are selected as the attributes to fulfill this purpose.

A new specialization is defined for the std's hash structure `std::hash()` that can perform operations with the `<Vertex>` data type. 

```cpp
template<>
struct std::hash<Vertex> {
```

This specialization will give C++ directions on how to approach the hashing process when applied to a custom created structure. Inside of the structure should be a function `operator() const` which performs the hashing process of the object in *read mode* (const part). Thus, inside of our own definition we equal the `Vertex` hash to be a combination of the object's `x` and `y` hashes

```cpp
std::size_t operator()(const Vertex& v) const {
        return std::hash<int>()(v.x) ^ std::hash<int>()(v.y);
    }
};
```

## [Implementation](./Vertex.hpp)
