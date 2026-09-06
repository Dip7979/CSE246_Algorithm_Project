# CSE246_Algorithm_Project
Dhaka Ride is a C++ ride-pooling system that uses Dijkstra’s Algorithm to find the shortest routes between locations and groups passengers with similar routes. It models Dhaka as a weighted graph and applies route similarity analysis to optimize car assignments and reduce unnecessary trips.


# Dhaka Ride – Algorithm-Based Ride Pooling System

Dhaka Ride is a C++-based ride-pooling and route optimization system developed as an Algorithm course project. The system represents selected locations of Dhaka City as a weighted, undirected graph, where locations are represented as vertices and roads are represented as edges with distance-based weights.

The main objective of the project is to find the shortest and most efficient route for each passenger and then group passengers who have sufficiently similar travel routes into the same car. This demonstrates the practical application of graph algorithms and route similarity analysis in a real-world transportation scenario.

The project primarily uses **Dijkstra’s Shortest Path Algorithm** to calculate the shortest route between a passenger’s pickup and drop-off locations. The algorithm maintains the minimum distance from the source location to every other location and uses a priority-based set to efficiently select the next closest node. A predecessor map is also maintained to reconstruct the final shortest path.

After calculating individual routes, the system applies a **Jaccard Similarity-based route comparison method**. The locations included in two passengers’ routes are converted into sets, and their intersection and union are calculated. If the similarity score reaches or exceeds the predefined threshold of **0.6**, the passengers are assigned to the same ride pool.

The system includes several important features such as passenger information input, pickup and drop-off validation, shortest-route calculation, route distance calculation, route similarity analysis, automatic ride-pool formation, and car assignment. It also provides a simple text-based visualization of the Dhaka road network to make the system easier to understand.

The project demonstrates practical concepts including **Graph Representation, Dijkstra’s Algorithm, Set Operations, Jaccard Similarity, Path Reconstruction, and Greedy-style Group Assignment**. Overall, Dhaka Ride shows how fundamental algorithmic techniques can be combined to develop a simple transportation optimization solution for ride-sharing and route-based car pooling.
