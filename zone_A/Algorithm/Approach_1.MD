# Algorithm First Approach
## Particular efficiency
Because we are bound to a physical medium where vertices are encountered as the robot explores the maze, it is preferable to use an algorithm that requires the least number of edges to visit all vertices (i.e., the shortest distance to visit all of them). Therefore, an algorithm that does not backtrack on vertices and edges it has already completely explored is prefered.

Greater efficiency can be achieved by:

1. Saving at the beginning a hashmap of vertices `max_v` with the maximum number of edges or connections of each vertex with others (i.e., the maximum number of times a vertex can be found from different vertices), where:
    * Key: vertex $(y)$
    * Value: maximum number of edges $(x)$
2. Saving with each exploration a hashmap of vertices `found_v` with the number of edges or connections that each vertex has with others at the moment (i.e., the number of times the vertex has been found from different vertices up to that point), where:
    * Key: vertex $(y)$
    * Value: number of edges found at the moment $(a)$
3. Comparing both values with each visit to $y$.
    * If $x=a$, it is no longer necessary to explore $y$ because it cannot have more connections. $y$ is marked as explored and does not need to be visited in the future.

The `max_v` hashmap can be constructed by considering the position of each vertex on the maze:
- Floating squares (squares that are not attached to fixed walls) can have up to 4 connections with other vertices.
- Squares connected to only 1 fixed wall can have up to 3 edges.
- Corner squares (adjacent to 2 fixed walls) only have up to 2 possible edges.

Taking into account each vertex's assigned integer name, `max_v` will have the following values:

| Vertex | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
| - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| Max. Edges | 2 | 3 | 3 | 3 | 3 | 2 | 3 | 4 | 4 | 4 | 3 | 2 | 3 | 3 | 3 | 2 |

Visualizing the maximum amount of edges for each vertex:

![Maze as graph with maximum edges visualized](../../media/max_edges.png "Maze as graph with maximum edges visualized")

Taking into account the previous reasoning, greater efficiency can be achieved by assigning a weight to each edge that corresponds to the depth level of the graph from right to left and from bottom to top.

The primary reason to do this is to visit as many vertices as possible before going to the exit (which is located at the top left corner) not to backtrack squares. So, considering the location of $E$ on the maze, the goal is to mark as visited and explored as many vertices on the right bottom side of the maze before moving to the top left. Therefore, there should be a priority in exploring vertices based on the following hierarchy:

| Direction | Weight |
| :-: | :-: |
| Right | $0$ |
| Down | $1$
| Up | $2$ |
| Left | $3$ |

Where numbers with lower weight have higher priority.

Due to the unique considerations mentioned above, it is better to be able to modify the vertices to be explored as needed. Therefore, the algorithm involving a stack is preferred over the recursive algorithm. It is easier to implement these specific routes on a stack than on a recursive algorithm.

## Implementation of a Graph in C++

To maintain order in the main program, a new file will be created containing the definition of a ```Graph``` class. This structure will be used to store the squares (vertices) that the robot traverses. The basic elements it should contain are:

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

## References

[Official Call](../Candidates%202023.pdf)

[Algorithmic Thinking of DFS & BFS](https://www.youtube.com/watch?v=pcKY4hjDrxk&ab_channel=AbdulBari)

[Iterative DFS](https://www.geeksforgeeks.org/iterative-depth-first-traversal/)