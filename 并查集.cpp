#include <bits/stdc++.h>

using namespace std;

struct DSU {
    vector<int> parent;
    
    DSU(int n) {
        parent.resize(n + 1);
        for(int i = 0; i <= n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }

    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }
};