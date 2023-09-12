# Zone A Algorithm
## Summary
Zone A is simply a maze in very little detail. To earn more points in this zone, one must navigate the entire maze with the goal of identifying the only color that repeats EXACTLY 5 times $(U)$. The size of the maze is always a zone of $3\cdot 5$, $+1$ to count the checkpoint square at the exit $(E)$. Additionally, there is a black square $(K)$ through which one must not pass.

Due to this, the count of the colors is as follows:

| Color | Appearances |
| :-: | :-: |
| Unique $(U)$ | $5$ |
| $A$ | $0 \rightarrow 9$ |
| $B$ | $0 \rightarrow 9$ |
| Black $(K)$ | $1$ |
| Start $(S)$ | $1$ |
| | |
| Total | $16$ |

Where the appearance of the colors $A+B=9$, and the final checkpoint $E$ can be $E\in A|E\in B|E\in C$.

The problem lies in the possible randomly placed floating walls throughout the maze. Dead ends may exist. It is ensured that there will always be a way out of the maze without conflict with $K$ or a dead end.

## Algorithm: Graph

### Approach

The entire system can be viewed as a graph that may or may not have connections between its different vertices, depending on the existence of floating walls. Considering that these walls may exist, each vertex connects to another always in an octagonal manner, so a vertex can have a maximum of 4 adjacent vertices. Considering the maze in the call:

<div style="text-align: center;">
<img src="../Figures/zoneA_maze1.jpg" width="50%" alt="Original maze design">
<img src="../Figures/IMG_6484.jpg" width="50%" alt="OG maze representation as graph">
</div>

An algorithm is required to explore all vertices, even if the exit square $(E)$ is encountered. This is because the color that has exactly 5 appearances $(U)$ must first be determined. Vertex $K$ should not be accessed, and therefore, there should be no paths to it.

### Depth First Search (DFS)
DFS is an algorithm for traversing or searching for vertices through graphs. Unlike other algorithms, such as BFS (Breadth-First Search), it traverses the graph as it encounters new vertices. That is, when it finds a new vertex, it starts exploring it immediately and pauses the exploration of the previous vertex for later.

This pause can be implemented in two different ways:
* Recursion: Through recursion, the process of searching for adjacent vertices is repeated for each vertex found.
    1. The search function on a parent vertex finds a child vertex.
    1. Upon being found, the function is called on the child vertex, effectively pausing the parent vertex's exploration.
    2. When this child vertex is fully explored, the function ends.
    3. The parent vertex's exploration function is resumed.

* Stack: This data structure of type *stack* is created, and vertices are added and removed from it as vertices are found and explored: when a vertex is added to the stack, its exploration is paused, and when it is removed, it is resumed.


###  Particular Efficiency Development
Because we are bound to a physical medium where vertices are encountered as the robot explores the maze, it is preferable to use an algorithm that requires the least number of edges to visit all vertices (i.e., cover the shortest distance to visit them all.) Therefore, an algorithm that does not revisit vertices and edges it has already passed through is chosen.

Greater efficiency can be achieved by:

1. Saving a hashmap of vertices ```max_v``` at the beginning, which contains the maximum number of edges or connections each vertex has with others (i.e., the maximum number of times a vertex can be found from different vertices).
    * Key: vertex $y$
    * Value: maximum number of edges $x$
2. Saving a hashmap of vertices ```found_v``` with the number of edges or connections each vertex has with others at the moment (i.e., the number of times the vertex has been found from different vertices up to that moment).
    * Key: vertex $y$
    * Value: number of edges found at the moment $a$
3. Comparing both values with each visit to vertex $y$.
    * If $x=a$, it is no longer necessary to explore vertex $y$ because it cannot have more connections. Vertex $y$ is marked as explored, and it does not need to be visited in the future.

Considering the above reasoning, greater efficiency can be achieved by assigning a weight to each edge corresponding to the depth level of the graph from right to left. The goal is to mark as visited and explored the largest number of vertices to the right of the maze before moving to the left. Therefore, vertices found are prioritized for exploration with the following hierarchy:

| Direction | Weight |
| :-: | :-: |
| Right | $-1$ |
| Down or Up | $0$ |
| Left | $1$ |

Where numbers with lower weight have higher priority.

Due to the unique considerations mentioned above, it is better if the vertices to be explored can be modified as needed. Therefore, the algorithm involving a stack is used over the recursive algorithm. The stack can be modified more easily to suit the exploration priorities of vertices.

### C++ Implementation of Graph
To maintain order in the main program, a new file containing the definition of a ```Graph``` class will be created. This structure will be used to store the squares (vertices) that the robot travels. The basic elements it should contain are:

```cpp
class Graph {
    private:
        // Number of vertices
        int num_v;
        // Robot's current vertex position
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

### Scalability

## Questions and Assumptions
1. What is the minimum and maximum number of appearances of a color in the squares? Can a color not appear, or even appear more than 5 times?
    * It is assumed that a color may not appear or appear as many times as possible as long as it allows another color to have exactly 5 appearances.
2. Does the random color of the checkpoint at the end of Zone A (start of the ramp) count towards the number of appearances of a color? Why does it appear with a lighter blue in the call?
    * It is assumed that it is included in the count, and the color changes to provide contrast with the cube's representation in the image.

## References

[Official Call](../Candidates%202023.pdf)

[Algorithmic Thinking of DFS & BFS](https://www.youtube.com/watch?v=pcKY4hjDrxk&ab_channel=AbdulBari)

[Iterative DFS](https://www.geeksforgeeks.org/iterative-depth-first-traversal/)
