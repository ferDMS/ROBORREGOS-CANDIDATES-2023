# Algorithmic Approach Zone A

The following is the selected approach to traverse the maze on Zone A with an increased particular efficiency. This approach uses the [Graph](../../general/Graph.MD) class, that consequently uses the [Vertex](../../general/Vertex.MD) and [Edge](../../general/Edge.MD) structures.

Because we are bound to a physical medium where vertices are encountered as the robot explores the maze, it is preferable to use an algorithm that requires the least number of edges to visit all vertices (i.e., the shortest distance covered to visit all of them). Therefore, an algorithm that does not make the robot backtrack through already visited vertices is opted.

## Maximum possible edges

Considering this, greater efficiency can be achieved by:

1. Saving at the beginning a hashmap of vertices `max_edges` with the maximum number of edges or connections of each vertex with others (i.e., the maximum number of times a vertex can be found from different vertices), where:
    * Key: vertex $(y)$
    * Value: maximum number of edges $(x)$
2. Updating with each exploration an adjacency map `adj` that contains the edges that have been found for each vertex, where:
    * Key: vertex $(y)$
    * Value: vector of edges $(e)$
3. The number of elements on the vector $(e\text{.size})$ equals the found edges count for each vertex $(a)$. In other words, the number of times the vertex has been found from different vertices up to that point.
4. Comparing both values every time $y$ is reached from a different edge.
    * While $a < x$ there are possibly more edges to be encountered for vertex $y$
    * If $a==x$, it is no longer necessary to explore $y$ as there are no more possible adjacent vertices left to explore. Thus, $y$ is marked as explored and does not need to be visited at a later time.

The `max_edges` hashmap can be constructed by considering the position of each vertex on the maze:

* Floating squares (squares that are not attached to fixed walls) can have up to 4 connections with other vertices.
* Squares connected to only 1 fixed wall can have up to 3 edges.
* Corner squares that are adjacent to 2 fixed walls can only have up to 2 edges.

The construction of `max_edges`, for Zone A, will have the following values:

![Maze as graph with maximum edges visualized](../media/max_edges.png "Maze as graph with maximum edges visualized")
Visualization of maximum edges on Zona A graph

The definition of the hashmap, using the Vertex structure, should be

```cpp
std::unordered_map<Vertex, int> max_edges;
```

## Weighting edges

Taking into account the previous reasoning, greater efficiency can be achieved by assigning a weight to each edge that corresponds to the depth level of the graph from right to left and from bottom to top.

The primary reason to do this is to visit as many vertices as possible before going to the exit (which is located at the top left corner) in order to avoid backtracking squares. So, considering the location of $E$ on the maze, the goal is to mark as visited (explored) as many vertices on the right bottom side of the maze before moving to the top left. Therefore, there should be a priority in exploring vertices based on

| Direction | Weight |
| :-------: | :----: |
|   Right   |  $0$   |
|   Down    |  $1$   |
|    Up     |  $2$   |
|   Left    |  $3$   |

, where numbers with lower weight have higher priority.

## Selecting a DFS algorithm

Due to the unique considerations mentioned above, being able to mark the vertices as explored and pause their exploration on command is desired. This specifications are easier to apply on a stack structure than in a recursive algorithm. Therefore, the problem will be addressed with a stack structure.

## References

[Official Announcement](../Candidates%202023.pdf)

[Algorithmic Thinking of DFS & BFS](https://www.youtube.com/watch?v=pcKY4hjDrxk&ab_channel=AbdulBari)

[Iterative DFS](https://www.geeksforgeeks.org/iterative-depth-first-traversal/)
