# Algorithm First Approach

## Particular efficiency

Because we are bound to a physical medium where vertices are encountered as the robot explores the maze, it is preferable to use an algorithm that requires the least number of edges to visit all vertices (i.e., the shortest distance covered to visit all of them). Therefore, an algorithm that does not make the robot backtrack through already visited vertices is opted.

Considering this, greater efficiency can be achieved by:

1. Saving at the beginning a hashmap of vertices `max_v` with the maximum number of edges or connections of each vertex with others (i.e., the maximum number of times a vertex can be found from different vertices), where:
    * Key: vertex $(y)$
    * Value: maximum number of edges $(x)$
2. Saving with each exploration a hashmap of vertices `visits` with the number of edges or connections that have been discovered for each vertex at the moment (i.e., the number of times the vertex has been found from different vertices up to that point), where:
    * Key: vertex $(y)$
    * Value: number of edges found at the moment $(a)$
3. Comparing both values with each visit to $y$.
    * While $a<x$ there are still possible edges to be encountered
    * If $a==x$, it is no longer necessary to explore $y$ as there are no more adjacent vertices left to explore. Thus, $y$ is marked as explored and does not need to be visited at a later time.

The `max_v` hashmap can be constructed by considering the position of each vertex on the maze:

* Floating squares (squares that are not attached to fixed walls) can have up to 4 connections with other vertices.
* Squares connected to only 1 fixed wall can have up to 3 edges.
* Corner squares (adjacent to 2 fixed walls) only have up to 2 possible edges.

The construction of `max_v` will have the following values:

![Maze as graph with maximum edges visualized](../../media/max_edges.png "Maze as graph with maximum edges visualized")
Visualization of maximum edges in the maze graph

Taking into account the previous reasoning, greater efficiency can be achieved by assigning a weight to each edge that corresponds to the depth level of the graph from right to left and from bottom to top.

The primary reason to do this is to visit as many vertices as possible before going to the exit (which is located at the top left corner) not to backtrack squares. So, considering the location of $E$ on the maze, the goal is to mark as visited and explored as many vertices on the right bottom side of the maze before moving to the top left. Therefore, there should be a priority in exploring vertices based on

| Direction | Weight |
| :-------: | :----: |
|   Right   |  $0$   |
|   Down    |  $1$   |
|    Up     |  $2$   |
|   Left    |  $3$   |

, where numbers with lower weight have higher priority.

Due to the unique considerations mentioned above, being able to mark the vertices as explored and pause their exploration on command is desired. This specifications are easier to apply on a stack structure than in a recursive algorithm. Therefore, the approach will address the problem with a stack.

## Graph class in C++

To develop clean code in the main program, a new header file will be created containing the definition of a ```Graph``` class. This structure will be used to store the squares (vertices) that the robot traverses. The basic elements it should contain are:

* Number of vertices
* Graph location of the robot
* Adjacency list
* DFS related data
* Maze specific data

### Naming Vertices

In order to correctly save each vertex as unique, they will be differentiated by their relative location to the initial vertex $S$. Because there might be multiple vertices that are at equal distances from $S$, one would not be able to tell the difference between two same-level vertices from $S$ by using a single integer. As a result, coordinates of 2 integers must be used, one for the $x$ axis, comprising movements to the left and right, and another for the $y$ axis, comprising upwards and downwards movements.

This can be implemented using an array of 2 elements.


### Basic Implementation

```cpp
class Graph {
    private:
        // Number of vertices
        int num_v;
        // Robot's vertex position
        int pos;
        // Adjacency list (edges of each vertex)
        vector<int> adj[num_v];

    public:
        // Constructors
        Graph(int v);
        // Add an undirected edge between two vertices
        void addEdge(int v1, int v2);
};
```

<!-- 
### Integrating DFS

LEFT TO EDIT

The `Graph` class needs to store multiple structures and data types used by the DFS algorithm, which should be initialized with the known values. Since the location of the $S$ square in the maze is unknown, it's more convenient to designate the root vertex as $S$ and label it as 0. The subsequent encountered vertices can be named as consecutive integers ($1, 2, 3, \dots, n-1$), where $n$ represents the total number of vertices in the graph. In the case of Zone A, $n=16$.
 -->

## References

[Official Call](../Candidates%202023.pdf)

[Algorithmic Thinking of DFS & BFS](https://www.youtube.com/watch?v=pcKY4hjDrxk&ab_channel=AbdulBari)

[Iterative DFS](https://www.geeksforgeeks.org/iterative-depth-first-traversal/)
