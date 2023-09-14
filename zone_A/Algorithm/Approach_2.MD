# Algorithm Second Approach

## Problem with Approach 1

The primary issue with the initial approach only lies in its dependency on the starting square and on the hash map used to store the maximum potential number of edges for each vertex. The comparison between `max_v` and `found_v` relies on knowing the specific named vertex that the robot is entering.

For this to be possible, the robot must possess complete awareness of its position right from the beginning. Hence, the approach fundamentally depends on the **initial square** maintaining its **position** every round, and, because it **does get randomized**, it is unlikely and demanding for the robot to locate itself on such a fixed structure.

## Addressing the issue

Changing the position of $S$ makes the whole problem more dynamic and case-specific, making it less plausible to be solved through an algorithm that can be as efficient as the one suggested on Approach 1. Nonetheless, everything else can still be implemented, including the weighted edges and graph features.

Additionally, if the location of $S$ is to the left of the maze, or even right beside $E$, the weighted edges will make sure that the robot still explores all the vertices (assuming that they are all reachable vertices from the root $S$).

## Integrating DFS into Graph class

The `Graph` class needs to store multiple structures and data types used by the DFS algorithm, which should be initialized with the known values. Since the location of the $S$ square in the maze is unknown, it's more convenient to designate the root vertex as $S$ and label it as 0. The subsequent encountered vertices can be named as consecutive integers ($1, 2, 3, \dots, n-1$), where $n$ represents the total number of vertices in the graph. In the case of Zone A, $n=16$.

[Graph class](./Graph.h)

## References

[Official Call](../Candidates%202023.pdf)

[Algorithmic Thinking of DFS & BFS](https://www.youtube.com/watch?v=pcKY4hjDrxk&ab_channel=AbdulBari)

[Iterative DFS](https://www.geeksforgeeks.org/iterative-depth-first-traversal/)
