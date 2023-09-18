# Algorithm Second Approach

## Deprecated Approach

This approach was developed contemplating that the position of the initial square $S$ was randomized every round as a fix for Approach 1. Luckily, this is not the case and Approach 1 is still valid.

## ~~Problem with Approach 1~~

~~The primary issue with the initial approach only lies in its dependency on the starting square and on the hash map used to store the maximum potential number of edges for each vertex. The comparison between `max_edges` and `adj[].size()` relies on knowing the specific named vertex that the robot is entering.~~

~~For this to be possible, the robot must possess complete awareness of its position on the maze right from the beginning. Hence, the approach fundamentally depends on the **initial square** maintaining its **position** every round, and, because it **does get randomized**, it is unlikely and demanding for the robot to locate itself on such a fixed structure.~~

## ~~Addressing the issue~~

~~Changing the position of $S$ makes the whole problem more dynamic and case-specific, making it less plausible to be solved through an algorithm that can be as efficient as the one suggested on Approach 1. Nonetheless, everything else can still be implemented, including the weighted edges and graph features.~~

~~Additionally, if the location of $S$ is to the left of the maze, or even right beside $E$, the weighted edges will make sure that the robot still explores all the vertices (assuming that they are all reachable vertices from the root $S$).~~