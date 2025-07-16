// 1. Clone a Graph
// To clone a graph we can use any one traversal method (BFS or DFS).

// Uising BFS
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return nullptr;
        queue<Node *> q;
        unordered_map<Node*, Node*> um;
        q.push(node);
        Node *newNode = new Node(node -> val);
        um[node] = newNode;
        while (!q.empty()) {
            Node *curr = q.front();
            q.pop();
            for (auto it: curr -> neighbors) {
                if (um.find(it) == um.end()) {
                    um[it] = new Node(it -> val);
                    q.push(it);
                }
                um[curr] -> neighbors.push_back(um[it]);
            }
        }
        return newNode;
    }
};

// Using DFS
class Solution {
private:
    unordered_map<Node *, Node *> um;
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return nullptr;
        if (um.find(node) != um.end()) return um[node];

        um[node] = new Node(node -> val);
        for (auto it: node -> neighbors) {
            um[node] -> neighbors.push_back(cloneGraph(it));
        }
        return um[node];
    }
};

// 2. Course Schedule
// We can use cycle detection method to check if any cycle is present in completing course or not.
// We can use bfs(kahn's Algorithm) or dfs for detecting cycle.


// 3. Bipartite Graph
// We can use coloring method where we use two color and check all adjacent node has different color or not. We can implement it using both bfs and dfs.

