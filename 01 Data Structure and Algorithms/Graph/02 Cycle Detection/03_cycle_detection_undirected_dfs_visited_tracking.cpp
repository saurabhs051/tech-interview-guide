
    /* 
    *	Cycle detection in Undirected graph : DFS
    *	1. A node should not be already visited (unless it is the immediate parent of current node)
    *	2. Try from each source node, to tackle case of disjoint graph
    *	3. Return early, as soon as cycle found
    */
class Solution {
    bool isCyclic(unordered_map<int, vector<int>>& adjList, int node, vector<bool>& visited, int parent)
    {
        if (visited[node])
            return true;
            
        visited[node] = true;
        for (auto& dest : adjList[node])
        {
            if (dest != parent) // Don't go ahead for parent neighbour
            {
                if (isCyclic(adjList, dest, visited, node))
                    return true;
            }
        }
        return false;
    }
  public:
    bool isCycle(int V, vector<vector<int>>& edges) {
        if (V == 0)
            return false;
        
        unordered_map<int, vector<int>> adjList;
        for (auto& edge : edges)
        {
            int src = edge[0];
            int dest = edge[1];
            adjList[src].push_back(dest);
            adjList[dest].push_back(src);
        }
        
        vector<bool> visited(V, false);
        for (int src = 0; src < V; ++src)
        {
            if (visited[src])
                continue;
            if (isCyclic(adjList, src, visited, -1))
                return true;
        }
        return false;
    }
};
