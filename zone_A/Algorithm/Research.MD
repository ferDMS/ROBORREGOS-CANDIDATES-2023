# Algorithm Zone A

## Summary

Zone A is, in very little detail, simply a maze. To earn more points in this zone, one must traverse the entire maze with the objective of identifying the only color that repeats EXACTLY 5 times $(U)$. The size of the maze is always a zone of $3\cdot 5$, $+1$ counting the checkpoint exit square $(E)$. The starting squasre $(S)$ is always positioned in the second row, last column to the right. Additionally, there is a randomly positioned black square $(K)$ that should not be crossed.

Because of this, there are 13 randomly generated colored squares, as follows:

|    Color     |      Appearances      |
| :----------: | :-------------------: |
| Unique $(U)$ |          $5$          |
|     $A$      | $0 \leftrightarrow 8$ |
|     $B$      | $0 \leftrightarrow 8$ |
|              |                       |
|    Total     |         $13$          |

Where the appearance of colors $A+B=8$.

And the 3 constant colors:

|    Color     | Appearances |
| :----------: | :---------: |
| Black $(K)$  |     $1$     |
|  Cyan $(E)$  |     $1$     |
| Yellow $(S)$ |     $1$     |
|              |             |
|    Total     |     $3$     |

The problem lies in possible randomly placed floating walls throughout the maze and possible dead ends. It is ensured that there will always be an exit from the maze without conflict with $K$ or a dead end.

## Questions and Answers

1. What is the minimum and maximum number of appearances of a color in the squares?
    * A color can appear as many times as possible as long as it allows one color to have exactly 5 appearances.
2. Does the random color of the checkpoint at the end of Zone A (start of the ramp) count towards the number of appearances of a color?
    * No, the final checkpoint is always cyan.
3. Does the initial square also change in position every round?
    * No, $S$ and $E$ never change positions

## Algorithmic Approach: Graph

The entire system can be seen as a graph that may or may not have connections between its different vertices, depending on the presence of floating walls. Considering that these walls can exist, each vertex is connected to another always in an octagonal manner, so, by its location on the maze, all vertices will have a maximum of adjacent vertices possible.

![zoneA_maze1](../../media/zoneA_maze1.jpg)
Zone A example maze

![Graph representation of maze](../../media/graph_zone_1.png)
Graph representation of maze with vertex names

An algorithm is needed that explores all vertices, even if the exit square $(E)$ is encountered. This is because the color that occurs exactly 5 times $(U)$ must be determined before exiting the maze. Vertex $K$ should not be accessed, and therefore, there should be no edges to it.

## Depth First Search (DFS)

DFS is an algorithm for traversing or searching vertices through graphs. Unlike other algorithms, such as BFS (Breadth-First Search), it traverses the graph as it encounters new vertices. In other words, when it finds a new vertex, it starts exploring it at that moment and it pauses the exploration of the previous vertex for later.

This pause can be implemented in two different ways:

* Recursion: Through recursion, the process of searching for adjacent vertices is repeated for every non-visited vertex that is encountered.
    1. The search function on a parent vertex finds a child vertex.
    2. Upon being found, the function is called on the child vertex, effectively pausing the one on the parent vertex.
    3. When this child vertex is fully explored, the function ends.
    4. The function of exploring the parent vertex resumes.

* Stack: This stack data structure is created, and vertices are added to and removed from it as vertices are found and explored. When a vertex is added to the stack, its exploration is paused, and when it is removed, it is resumed.

## References

[Official Call](../Candidates%202023.pdf)

[Algorithmic Thinking of DFS & BFS](https://www.youtube.com/watch?v=pcKY4hjDrxk&ab_channel=AbdulBari)

[Iterative DFS](https://www.geeksforgeeks.org/iterative-depth-first-traversal/)
