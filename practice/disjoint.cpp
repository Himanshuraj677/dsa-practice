#include<iostream>
#include<vector>

using namespace std;
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

int main () {
    DisjointSet ds(7);

    ds.unionBySize(1, 2);
    ds.unionBySize(2, 3);
    cout << ds.findUParent(1) << " ";
    cout << ds.findUParent(3) << endl;

    ds.unionByRank(4, 5);
    ds.unionByRank(6, 7);
    ds.unionByRank(5, 6);
    cout << ds.findUParent(7) << endl;
    return 0;
}