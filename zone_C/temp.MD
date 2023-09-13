# Algorithm Zone A
## Summary
Zone A is, in very little detail, simply a maze. To earn more points in this zone, one must traverse the entire maze with the objective of identifying the only color that repeats EXACTLY 5 times $(U)$. The size of the maze is always a zone of $3\cdot 5$, $+1$ counting the checkpoint exit square $(E)$. Additionally, there is a black square $(K)$ that should not be crossed.

Because of this, the color count is as follows:

| Color | Appearances |
| :-: | :-: |
| Unique $(U)$ | $5$ |
| $A$ | $0 \rightarrow 9$ |
| $B$ | $0 \rightarrow 9$ |
| Black $(K)$ | $1$ |
| Start $(S)$ | $1$ |
| | |
| Total | $16$ |

Where the appearance of colors $A+B=9$ and the final checkpoint $E$ can be $E\in A\ |\ E\in B\ |\ E\in C$.

The problem lies in possible randomly placed floating walls throughout the maze and possible dead ends. It is ensured that there will always be an exit from the maze without conflict with $K$ or a dead end.

## Algorithm: Graph

### Approach
The entire system can be seen as a graph that may or may not have connections between its different vertices, depending on the presence of floating walls. Considering that these walls can exist, each vertex is connected to another always in an octagonal manner, so vertices will have a maximum of adjacent vertices possible.

![zoneA_maze1](../media/zoneA_maze1.jpg)
Zone A example maze

![Graph representation of maze with vertex names](../media/example_graph.png)
Graph representation of maze with vertex names


An algorithm is needed that explores all vertices, even if the exit square $(E)$ is encountered. This is because the color that occurs exactly 5 times $(U)$ must first be determined. Vertex $K$ should not be accessed, and therefore, there should be no paths to it.

### Depth First Search (DFS)
DFS is an algorithm for traversing or searching vertices through graphs. Unlike other algorithms, such as BFS (Breadth-First Search), it traverses the graph as it encounters new vertices. In other words, when it finds a new vertex, it starts exploring it at that moment and pauses the exploration of the previous vertex for later.

This pause can be implemented in two different ways:
* Recursion: Through recursion, the process of searching for adjacent vertices is repeated for each vertex it finds.
    1. The search function on a parent vertex finds a child vertex.
    2. Upon being found, the function is called on the child vertex, effectively pausing the one on the parent vertex.
    3. When this child vertex is fully explored, the function ends.
    4. The function of exploring the parent vertex resumes.

* Stack: This stack data structure is created, and vertices are added to and removed from it as vertices are found and explored. When a vertex is added to the stack, its exploration is paused, and when it is removed, it resumes.

### Development of Particular Efficiency
Because we are bound to a physical medium where vertices are encountered as the robot explores the maze, it is preferable to use an algorithm that requires the least number of edges to visit all vertices (i.e., the shortest distance to visit all of them). Therefore, an algorithm that does not backtrack on vertices and edges it has already completely explored is prefered.

Greater efficiency can be achieved by:

1. Saving at the beginning a hashmap of vertices ```max_v``` with the maximum number of edges or connections of each vertex with others (i.e., the maximum number of times a vertex can be found from different vertices), where:
    * Key: vertex $(y)$
    * Value: maximum number of edges $(x)$
2. Saving with each exploration a hashmap of vertices ```found_v``` with the number of edges or connections that each vertex has with others at the moment (i.e., the number of times the vertex has been found from different vertices up to that point), where:
    * Key: vertex $(y)$
    * Value: number of edges found at the moment $(a)$
3. Comparing both values with each visit to $y$.
    * If $x=a$, it is no longer necessary to explore $y$ because it cannot have more connections. $y$ is marked as explored and does not need to be visited in the future.

The ```max_v``` hashmap can be constructed by considering the position of each vertex on the maze:
- Floating squares (squares that are not attached to fixed walls) can have up to 4 connections with other vertices.
- Squares connected to only 1 fixed wall can have up to 3 edges.
- Corner squares (adjacent to 2 fixed walls) only have up to 2 possible edges.

Taking into account each vertex's assigned integer name, ```max_v``` will have the following values:

| Vertex | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
| - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
| Max. Edges | 2 | 3 | 3 | 3 | 3 | 2 | 3 | 4 | 4 | 4 | 3 | 2 | 3 | 3 | 3 | 2 |

Visualizing the maximum amount of edges for each vertex:

![Maze as graph with maximum edges visualized](../media/max_edges.png)

Taking into account the previous reasoning, greater efficiency can be achieved by assigning a weight to each edge that corresponds to the depth level of the graph from right to left and from bottom to top, considering the location of $E$ on the maze. The goal is to mark as visited and explored as many vertices on the right bottom side of the maze before moving to the top left, where the $E$ is located. Therefore, there is a priority in exploring vertices based on the following hierarchy:

| Direction | Weight |
| :-: | :-: |
| Right | $0$ |
| Down | $1$
| Up | $2$ |
| Left | $3$ |

Where numbers with lower weight have higher priority.

Due to the unique considerations mentioned above, it is better to be able to modify the vertices to be explored as needed. Therefore, the algorithm involving a stack is used over the recursive algorithm. The stack can be modified more conveniently, which can consider the priorities of vertex exploration with more ease than the recursive algorithm.


### Implementation of Graph in C++

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

### Scalability

## Questions and Assumptions
1. What is the minimum and maximum number of appearances of a color in the squares? Can a color not appear, or even appear more than 5 times?
    * It is assumed that a color may not appear or appear as many times as possible while allowing another color to have exactly 5 appearances.
2. Does the random color of the checkpoint at the end of Zone A (start of the ramp) count towards the number of appearances of a color? Why does it appear in the call with a lighter blue?
    * It is assumed that it is included in the count, and the color changes to provide contrast with the representation of the cube in the image.

## References

[Official Call](../Candidates%202023.pdf)

[Algorithmic Thinking of DFS & BFS](https://www.youtube.com/watch?v=pcKY4hjDrxk&ab_channel=AbdulBari)

[Iterative DFS](https://www.geeksforgeeks.org/iterative-depth-first-traversal/)
