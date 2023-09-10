# Zone A Algorithm
## Summary
Zone A is, in very little detail, simply a maze. To earn more points in this zone, one must navigate the entire maze with the goal of identifying the only color that repeats EXACTLY 5 times $(U)$. The size of the maze is always a zone of $3\cdot 5$, $+1$ to count the checkpoint square at the exit $(E)$. Additionally, there is a black square $(K)$ through which one must not pass.

Due to this, the count of the colors are as follows:

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

The entire system can be viewed as a graph that may or may not have connections between its different nodes, depending on the existence of floating walls. Considering that these walls may exist, each node connects to another always in an octagonal manner, so a node can have a maximum of 4 adjacent nodes. Considering the maze in the call:

<div style="text-align: center;">
<img src="../Figures/zoneA_maze1.jpg" width="50%" alt="Original maze design">
<img src="../Figures/IMG_6484.jpg" width="50%" alt="OG maze representation as graph">
</div>

An algorithm is required to explore all nodes, even if the exit square $(E)$ is encountered. This is because the color that has exactly 5 appearances $(U)$ must first be determined. Node $K$ should not be accessed, and therefore, there should be no paths to it.

### Depth First Search (DFS)

### Specific Efficiency Development

Greater efficiency can be achieved by:

1. Saving a hashmap of nodes ```max_v``` with their maximum number of edges (i.e., maximum number of visits from different nodes) at the beginning.
    * Key: node $y$
    * Value: maximum number of edges $x$
2. Saving a hashmap of nodes ```found_v``` with the number of adjacent edges found at the moment (i.e., the number of times it has been found so far from different nodes) with each exploration.
    * Key: node $y$
    * Value: number of edges found at the moment $a$
3. Comparing both values with each node visit.
    * If $x=a$, it is no longer necessary to explore the found node because there is nothing more to find. The found node is marked as explored, and there is no need to pass through it again.

Taking the above reasoning into account, greater efficiency can be achieved by assigning a weight to each edge that corresponds to the depth level from right to left. This is proposed with the aim of marking as visited and explored the largest number of nodes to the right of the maze before moving to the left. Therefore, nodes found are prioritized for exploration with the following hierarchy:

1. Right, with weight $-1$
2. Down or Up, with weight $0$
3. Left, with weight $1$

Where numbers with lower weight have higher priority.

### C++ Implementation

### Scalability

## Questions and Assumptions
1. What is the minimum and maximum number of appearances of a color in the squares? Can a color not appear or even appear more than 5 times?
    * It is assumed that a color may not appear or appear as many times as possible as long as it allows another color to have exactly 5 appearances.
2. Does the random color of the checkpoint at the end of Zone A (start of the ramp) count towards the number of appearances of a color? Why does it appear with a lighter blue in the call?
    * It is assumed that it is included in the count, and the color changes to provide contrast with the cube's representation in the image.

## References

[Official Call](../Candidates%202023.pdf)
[Algorithmic Thinking of DFS & BFS](https://www.youtube.com/watch?v=pcKY4hjDrxk&ab_channel=AbdulBari)
