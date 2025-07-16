/*
=====================================================
🌐 Important Graph Algorithms for Coding Interviews
=====================================================

🔰 1. Traversal Algorithms
--------------------------
- BFS (Breadth-First Search): Shortest path in unweighted graphs, level-order traversal.
- DFS (Depth-First Search): Path finding, component detection, cycle checks.

Variants: Recursive and Iterative | Works for both directed and undirected graphs.

-----------------------------------------------------

🔗 2. Cycle Detection
---------------------
- DFS + Parent Check (Undirected)
- DFS with Recursion Stack (Directed)
- Disjoint Set Union (DSU) — for Undirected graphs (using union-find)

-----------------------------------------------------

🔁 3. Shortest Path Algorithms
------------------------------
- Dijkstra’s Algorithm: Weighted graph, no negative weights (uses min-heap).
- Bellman-Ford Algorithm: Can handle negative weights, detects negative cycles.
- Floyd-Warshall Algorithm: All-pairs shortest paths, O(V³).
- 0-1 BFS: For graphs with edge weights 0 and 1 (uses deque).

-----------------------------------------------------

🛣️ 4. Minimum Spanning Tree (MST)
----------------------------------
- Kruskal’s Algorithm: Edge-based, uses DSU.
- Prim’s Algorithm: Node-based, uses min-heap (priority queue).

-----------------------------------------------------

🔄 5. Topological Sort (DAG only)
---------------------------------
- DFS + Stack Method
- Kahn’s Algorithm (BFS with in-degree array)

Use Cases: Task scheduling, course prerequisite checking, dependency resolution.

-----------------------------------------------------

🧩 6. Strongly Connected Components (SCC)
-----------------------------------------
- Kosaraju’s Algorithm: 2 DFS passes (original + transposed graph).
- Tarjan’s Algorithm: 1 DFS pass, uses low-link values.

-----------------------------------------------------

🧠 7. Disjoint Set Union (DSU / Union-Find)
-------------------------------------------
Use Cases:
- Cycle detection in undirected graphs
- Kruskal’s MST
- Connected components

Optimizations:
- Path Compression
- Union by Rank / Size

-----------------------------------------------------

🗺️ 8. Graph Representations
----------------------------
- Adjacency List: Best for sparse graphs.
- Adjacency Matrix: Best for dense graphs or when using Floyd-Warshall.

-----------------------------------------------------

🔥 9. Advanced / Special Algorithms
-----------------------------------
- Bridges and Articulation Points (Tarjan's extension)
- Euler Path / Circuit (Hierholzer’s or Fleury’s algorithm)
- Hamiltonian Path (Backtracking)
- Bipartite Graph Check (2-coloring via BFS/DFS)
- Lowest Common Ancestor (LCA) – Binary Lifting / Euler Tour
- Tree Views: Top/Bottom view via BFS or DFS with horizontal distance

-----------------------------------------------------

📚 Recommended Practice Problems
-------------------------------
- LC 200 – Number of Islands (DFS/BFS)
- LC 695 – Max Area of Island (DFS)
- LC 743 – Network Delay Time (Dijkstra)
- LC 787 – Cheapest Flights Within K Stops (Bellman-Ford)
- LC 1584 – Min Cost to Connect All Points (Kruskal)
- LC 207 – Course Schedule (Topological Sort)
- LC 1192 – Critical Connections in a Network (Tarjan’s Algorithm)

-----------------------------------------------------

🧭 Study Strategy
-----------------
1. Start with BFS/DFS (master traversal)
2. Learn cycle detection (undirected & directed)
3. Master shortest path algorithms
4. Understand MST (Kruskal, Prim)
5. Practice Topological Sort and SCC
6. Solve problems using DSU
7. Explore advanced graph topics for hard problems

-----------------------------------------------------
*/


// 1. Breadth First Search (BFS) Algorithm

vector<int> bfs(vector<vector<int>> &adj) {
    // Code here
    int v = adj.size();
    vector<int> ans;
    vector<bool> isVisited(v, false);
    queue<int> q;
    q.push(0);
    isVisited[0] = true;
    while (!q.empty()) {
        int node = q.front();
        ans.push_back(node);
        q.pop();
        for (auto it: adj[node]) {
            if (!isVisited[it]) {
                q.push(it);
                isVisited[it] = true;
            }
        }
    }
    return ans;    
}


// 2. Depth First Search (DFS) Algorithm 
// a) Using Recursion

void helper(int node, vector<vector<int>>& adj, vector<int> &ans, vector<bool> &isVisited) {
    isVisited[node] = true;
    ans.push_back(node);
    for (auto it: adj[node]) {
        if (!isVisited[it]) helper(it, adj, ans, isVisited);
    } 
}
vector<int> dfs(vector<vector<int>>& adj) {
    // Code here
    int v = adj.size();
    vector<int> ans;
    vector<bool> isVisited(v, false);
    helper(0, adj, ans, isVisited);
    return ans;
}

// b) Using Stack
vector<int> dfs(vector<vector<int>>& adj) {
    // Code here
    int v = adj.size();
    vector<int> ans;
    vector<bool> isVisited(v, false);
    stack<int> st;
    st.push(0);
    while (!st.empty()) {
        int node = st.top();
        st.pop();
        if (!isVisited[node]) {
            ans.push_back(node);
            isVisited[node] = true;
            for (int i = adj[node].size() - 1; i >= 0; i--) {
                int neighbour = adj[node][i];
                if (!isVisited[neighbour]) {
                    st.push(neighbour);
                }
            }    
        }
    }
    return ans;
}


// 3. Cycle Detection in undirected Graph 
//  a) Using BFS

bool checkCycle (int start, vector<vector<int>> &adj, vector<int> &isVisited) {
    queue<pair<int, int>> q;
    q.push({start, -1});
    isVisited[start] = true;
    while (!q.empty()) {
        auto it = q.front();
        int node = it.first, parent = it.second;
        q.pop();
        for (auto neighbour: adj[node]) {
            if (!isVisited[neighbour]) {
                isVisited[neighbour] = true;
                q.push({neighbour, node});
            }
            else if (neighbour != parent) return true;
        }
    }
    return false;
}
bool isCycle(int V, vector<vector<int>>& edges) {
    // Code here
    vector<vector<int>> adj(V);
    vector<int> isVisited(V, false);
    for (auto it: edges) {
        int u = it[0], v = it[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < V; i++) {
        if (!isVisited[i] && checkCycle(i, adj, isVisited)) return true;
    }
    return false;
}

// b) Using DFS

bool checkCycle (int node, int parent, vector<vector<int>> &adj, vector<int> &isVisited) {
    isVisited[node] = true;
    for (auto neighbour: adj[node]) {
        if (!isVisited[neighbour]) {
            if (checkCycle(neighbour, node, adj, isVisited)) return true;
        }
        else if (neighbour != parent) return true;
    }
    return false;
}

// 4. Cycle Detection in Directed Graph using DFS
// a) Using Recursion
// b) Using Topological Sort (Kahn's Algorithm)

bool checkCycle(int node, vector<vector<int>> &adj, vector<bool> &isVisited, vector<bool> &track) {
    isVisited[node] = true;
    track[node] = true;
    for (auto neighbour: adj[node]) {
        if (!isVisited[neighbour]) {
            if (checkCycle(neighbour, adj, isVisited, track)) return true;
        }
        else if (track[neighbour]) return true;
    }
    track[node] = false;
    return false;
}
bool isCyclic(int V, vector<vector<int>> &edges) {
    // code here
    vector<vector<int>> adj(V);
    for (auto it: edges) {
        int u = it[0], v = it[1];
        adj[u].push_back(v);
    }
    vector<bool> isVisited(V, false), track(V, false);
    for (int i = 0; i < V; i++) {
        if (!isVisited[i] && checkCycle(i, adj, isVisited, track)) {
            return true;
        }
    }
    return false;
}


// 5. Topological Sort
// a) Using DFS

void helper(int start, vector<vector<int>> &adj, vector<int> &visited, stack<int> &st) {
    visited[start] = 1;
    for (auto it: adj[start]) {
        if (!visited[it]) helper(it, adj, visited, st);
    }
    st.push(start);
}

vector<int> topoSort(int V, vector<vector<int>>& edges) {
    // code here
    vector<vector<int>> adj(V + 1);
    for (auto it: edges) {
        int u = it[0], v = it[1];
        adj[u].push_back(v);
    }
    stack<int> st;
    vector<int> visited(V, 0), ans;
    for (int node = 0; node < V; node++) {
        if (!visited[node]) helper(node, adj, visited, st);
    }
    while (!st.empty()) {
        ans.push_back(st.top());
        st.pop();
    }
    return ans;
}


// b) Using Kahn's Algorithm (BFS)

vector<int> topoSort(int V, vector<vector<int>>& edges) {
    // code here
    vector<vector<int>> adj(V);
    vector<int> ans, inDegree(V, 0);
    for (auto it: edges) {
        int u = it[0], v = it[1];
        adj[u].push_back(v);
        inDegree[v]++;
    }
    
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (inDegree[i] == 0) q.push(i);
    }
    
    while (!q.empty()) {
        int front = q.front();
        q.pop();
        ans.push_back(front);
        for (auto it: adj[front]) {
            inDegree[it]--;
            if (inDegree[it] == 0) q.push(it);
        }
    }
    
    return ans;
}


// 6. Shortest Path Algorithms
// a) Dijkstra's Algorithm (for weighted graphs with non-negative weights)
// This algorithm finds the shortest path from a source node to all other nodes in a graph.
// It can be implemented using two approaches:

// i) Using Priority Queue (Min-Heap)
// This is the most efficient way to implement Dijkstra's algorithm, as it allows us to always expand the least costly node next.

vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
    // Code here
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<vector<pair<int, int>>> adj(V);
    vector<int> distance(V, 1e9);
    for (auto it: edges) {
        int u = it[0], v = it[1], dist = it[2];
        adj[u].push_back(make_pair(v, dist));
        adj[v].push_back(make_pair(u, dist));
    }
    pq.push({0, src});
    distance[src] = 0;
    while (!pq.empty()) {
        int dist = pq.top().first, node = pq.top().second;
        pq.pop();
        for (auto it: adj[node]) {
            int neighbor = it.first;
            int newDistance = dist + it.second;
            if (newDistance < distance[neighbor]) {
                distance[neighbor] = newDistance;
                pq.push({newDistance, neighbor});
            }
        }
        
    }
    return distance;
}

// ii) Using Set (Ordered Set)

vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
    // Code here
    set<pair<int, int>> st;
    vector<vector<pair<int, int>>> adj(V);
    vector<int> distance(V, 1e9);
    for (auto it: edges) {
        int u = it[0], v = it[1], dist = it[2];
        adj[u].push_back(make_pair(v, dist));
        adj[v].push_back(make_pair(u, dist));
    }
    st.insert({0, src});
    distance[src] = 0;
    while (!st.empty()) {
        int dist = (*st.begin()).first, node = (*st.begin()).second;
        st.erase(st.begin());
        for (auto it: adj[node]) {
            int neighbor = it.first;
            int newDistance = dist + it.second;
            if (newDistance < distance[neighbor]) {
                st.erase({distance[neighbor], neighbor});
                distance[neighbor] = newDistance;
                st.insert({newDistance, neighbor});
            }
        }
        
    }
    return distance;
}


// 7. Bellman-Ford Algorithm
// This algorithm can handle negative weights and can also detect negative cycles in the graph.

vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
    // Code here
    vector<int> ans(V, 1e8);
    ans[src] = 0;
    for (int i = 1; i < V; i++) {
        for (auto it: edges) {
            int u = it[0], v = it[1], distance = it[2];
            if (ans[u] != 1e8) ans[v] = min(ans[v], ans[u] + distance);
        }
    }
    bool isCycle = false;
    for (auto it: edges) {
        int u = it[0], v = it[1], distance = it[2];
        if (ans[u] != 1e8 && ans[v] > ans[u] + distance) {
            isCycle = true;
            break;
        }
    }
    if (isCycle) return {-1};
    return ans;
}


// 8. Floyd Warsahll Algorithm

vector<vector<int>> floydWarshall(vector<vector<int>> &dist) {
    // Code here
    int V = dist.size();
    vector<vector<int>> temp();
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != 1e8 && dist[k][j] != 1e8) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            // Negative cycle detected
            return {{-1}};
        }
    }
    return dist;
}




// 9. Disjoint Set Union
class DisjointSet {
    vector<int> parent, size, rank;
    public:
    DisjointSet (int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        rank.resize(n + 1, 0);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }

    }

    int findUParent (int node) {
        if (parent[node] == node) return node;
        return parent[node] = findUParent(parent[node]);
    }

    void unionByRank (int u, int v) {
        int ulpU = findUParent(u);
        int ulpV = findUParent(v);
        if (ulpU == ulpV) return;
        if (rank[ulpU] < rank[ulpV]) {
            parent[ulpU] = ulpV;
        }
        else if (rank[ulpU] > rank[ulpV]) {
            parent[ulpV] = ulpU;
        }
        else {
            parent[ulpU] = ulpV;
            rank[ulpV]++;
        }
    }

    void unionBySize (int u, int v) {
        int ultU = findUParent(u);
        int ultV = findUParent(v);
        if (ultU == ultV) return;
        if (size[ultU] > size[ultV]) {
            parent[ultV] = ultU;
            size[ultU] += size[ultV];
        }
        else {
            parent[ultU] = ultV;
            size[ultV] += size[ultU];
        }
    }
};

// 10. Kosaraju Algorithm
// It is used to find the number of strongly connected component in the graph
// Firstly find the order in which graph is getting visited. Use stack to store it. (can say topo sort)
// Reverse the graph
// Find no of componets in a graph


void topoSort(int node, vector<vector<int>> &adj, vector<bool> &isVisited, stack<int> &s) {
    isVisited[node] = true;
    for (auto nbr: adj[node]) {
        if (!isVisited[nbr]) {
            topoSort(nbr, adj, isVisited, s);
        }
    }
    s.push(node);
}

void dfs (int node, vector<vector<int>> &adj, vector<bool> &isVisited) {
    isVisited[node] = true;
    for (auto nbr: adj[node]) {
        if (!isVisited[nbr]) {
            dfs(nbr, adj, isVisited);
        }
    }
}

int kosaraju(vector<vector<int>> &adj) {
    // code here
    int n = adj.size();
    vector<bool> isVisited(n, false);
    stack<int> s;
    for (int i = 0; i < n; ++i) {
        if (!isVisited[i]) {
            topoSort(i, adj, isVisited, s);
        }
    }
    vector<vector<int>> revGraph(n);
    for (int i = 0; i < n; i++) {
        for (auto it: adj[i]) {
            revGraph[it].push_back(i);
        }
    }
    int count = 0;
    fill(isVisited.begin(), isVisited.end(), false);
    while (!s.empty()) {
        int node = s.top();
        s.pop();
        if (!isVisited[node]) {
            dfs(node, revGraph, isVisited);
            count++;
        }
    }
    return count;
}


// Tarjan's Algorithm


// Tarjan’s Algorithm uses DFS to find bridges or strongly connected
// components. It tracks discovery time disc[] and the lowest reachable
// ancestor low[]. If low[v] > disc[u], edge (u,v) is a bridge. For SCCs, if low[u] == disc[u], it marks the root of an SCC. Time: O(V + E).

bool dfs(int node, int parent, vector<vector<int>> &adj, int clock, vector<int> &time, vector<int> &low, vector<int> &isVisited, int &c, int &d) {
        isVisited[node] = 1;
        low[node] = time[node] = clock++;
        for (auto nbr: adj[node]) {
            if (nbr == parent) continue;
            if (!isVisited[nbr]) {
                if (dfs(nbr, node, adj, clock, time, low, isVisited, c, d)) return true;
                low[node] = min(low[node], low[nbr]);
                if (time[node] < low[nbr] && min(node, nbr) == min(c, d) && max(node, nbr) == max(c, d)) return true;
            }
            else{
                low[node] = min(low[node], low[nbr]);
            }
        }
        return false;
    }
    bool isBridge(int V, vector<vector<int>> &edges, int c, int d) {
        // Code here
        vector<vector<int>> adj(V);
        for (auto it: edges) {
            int u = it[0], v = it[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
            
        }
        
        vector<int> time(V), low(V), isVisited(V, 0);
        int clock = 0;
        for (int i = 0; i < V; i++) {
            if (!isVisited[i]) {
                if (dfs(i, -1, adj, clock, time, low, isVisited, c, d)) {
                    return true;
                }
            }
        }
        return false;
    }


// Articulation Point (Rohit Negi Video)

class Solution {
  private:
    int timer = 0;
  public:
    void dfs(int node, int parent, vector<int> &isVisited, vector<int> &disc, vector<int> &low, vector<vector<int>> &adj, vector<int> &isArticulation) {
        disc[node] = low[node] = timer++;
        isVisited[node] = 1;
        int childCount = 0;
        for (auto nbr: adj[node]) {
            if (nbr == parent) continue;
            if (!isVisited[nbr]) {
               dfs(nbr, node, isVisited, disc, low, adj, isArticulation);
               if (low[nbr] >= disc[node] && parent != -1) {
                   isArticulation[node] = 1;
               }
               low[node] = min(low[node], low[nbr]);
               childCount++;
            }
            else {
                low[node] = min(low[node], disc[nbr]);
            }
        }
        if (parent == -1 && childCount >= 2) isArticulation[node] = 1;
    }
    vector<int> articulationPoints(int V, vector<vector<int>>& edges) {
        // Code here
        vector<vector<int>> adj(V);
        // Create Adjacency List
        for (auto it: edges) {
            int u = it[0], v = it[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> isVisited(V, 0), isArticulation(V, 0), disc(V), low(V);
        // DFS Traversal to find articulation point
        for (int i = 0; i < V; i++) {
            if (!isVisited[i]) {
                dfs(i, -1, isVisited, disc, low, adj, isArticulation);
            }
        }
        vector<int> ans;
        for (int i = 0; i < V; i++) {
            if (isArticulation[i]) {
                ans.push_back(i);
            }
        }
        if (!ans.empty()) return ans;
        else return {-1};
    }
};