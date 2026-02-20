#include <bits/stdc++.h>

using namespace std;

struct Fenwick {
    int n;
    vector<int> tree;

    Fenwick(int size) : n(size), tree(size + 1, 0) {}

    int lowbit(int x) {
        return x & -x;
    }

    void update(int i, int val) {
        while (i <= n) {
            tree[i] += val;
            i += lowbit(i);
        }
    }

    int query(int i) {
        int res = 0;
        while (i > 0) {
            res += tree[i];
            i -= lowbit(i);
        }
        return res;
    }

    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};