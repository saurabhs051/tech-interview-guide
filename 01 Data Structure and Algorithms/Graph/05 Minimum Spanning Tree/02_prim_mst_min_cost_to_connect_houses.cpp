class Solution {
/* Checkout this (better) : https://www.geeksforgeeks.org/dsa/minimum-cost-required-to-connect-all-houses-in-a-city/ [MST : Focus on individual edges only]
* Given a 2D array houses[][] consisting of n 2D coordinates {x, y} where each coordinate represents the location of each house, the task is to find the minimum cost to connect all the houses of the city.
* Note: Cost of connecting two houses is the Manhattan Distance between the two points (xi, yi) and (xj, yj) i.e., |xi - xj| + |yi - yj|, where |p| denotes the absolute value of p.
 * 1. Min cost to connect all the houses (MST) : n-1 edges
 * 2. Prim's like Dijkstra : BFS + MinHeap (Greedy)
 *      2.1 Unlike Dijksta, But we only consider edge weight, not {node cost + edge weight}
 *      2.2 Unlike Dijksta, here we also need a visited vector, since we only want to get N-1 edges (visit N nodes)
 *      2.3 Unlike normal BFS, visited is checked and marked during pop from queue, not during insert
 * 3. Time Complexity : 
 *      3.1 In this example, dense graph(all to all), Building the adjacency list: O(n^2)
 *      3.2 Prim's algorithm using a min-heap : In sparse graph : O((V + E) log V) time
 *      3.3 But in our case, the graph is complete, i.e. V = n, E = n^2. Hence (~O(n² log n))
 *      3.4 Total : O(n²) + O(n² log n) = O(n² log n)
 */
  public:
    int minCost(vector<vector<int>>& houses) {
        // Using Prim's
        //Create adjacency list
        int n = houses.size();
        if (!n)
            return 0;
        unordered_map<int, vector<pair<int, int>>> adj;
        for (int i = 0; i < n - 1; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                int distance = abs(houses[i][0] - houses[j][0]) + abs(houses[i][1] - houses[j][1]);
                adj[i].push_back({j, distance});    //undirected graph
                adj[j].push_back({i, distance});
            }
        }
        
        // Prim's - everytime we choose min weight node from queue, hence use priority queue(minheap)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> visited(n, 0); // Dijksta doesn't need visited, but this does as wee only need to take n-1 edges (visit n nodes)
        vector<int> distance(n, INT_MAX); //min edge from that node
        pq.push({0, 0}); //{distnce, house}

        int minCost = 0;
        while (pq.size())
        {
            auto curHouse = pq.top(); pq.pop();
            if (visited[curHouse.second]) // Beware : unlike normal queue based BFS, here we check and mark visited after popping from queue, since it is allowed to have multiple entries for same node (with different weight) in the minHeap. However, when we jump on the minimum of them, the nodes gets finalized, and we won't process other entries for it anymore
                continue;
            visited[curHouse.second] = 1;
            minCost += curHouse.first; //this was finalized, note its cost
            // Update its neighbours
            for (auto& next : adj[curHouse.second])
            {
                if (distance[next.first] > next.second) // only the edge cost, not {node cost + edge cost, like in Dijkstra)
                {
                    distance[next.first] = next.second;
                    pq.push({distance[next.first], next.first});
                }
                
            }
        }
        return minCost;
    }
};
