#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 线段树二分
template<typename T>
class SegmentTree {
public:
    struct Node {
        T min_val;
        T max_val;
    };

    int n;
    vector<Node> tree;

    Node merge_node(const Node& a, const Node& b) const {
        return { min(a.min_val, b.min_val), max(a.max_val, b.max_val) };
    }

    void maintain(int node) {
        tree[node] = merge_node(tree[node * 2], tree[node * 2 + 1]);
    }

    void build(const vector<T> &a, int node, int l, int r) {
        if (l == r) {
            tree[node] = { a[l], a[l] };
            return;
        }
        int mid = l + (r - l) / 2;
        build(a, node * 2, l, mid);
        build(a, node * 2 + 1, mid + 1, r);
        maintain(node);
    }

    void update(int node, int l, int r, int i, T val) {
        if (l == r) {
            tree[node] = { val, val };
            return;
        }
        int mid = l + (r - l) / 2;
        if (i <= mid) update(node * 2, l, mid, i, val);
        else update(node * 2 + 1, mid + 1, r, i, val);
        maintain(node);
    }

    Node query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[node];
        }
        int mid = l + (r - l) / 2;
        if (qr <= mid) return query(node * 2, l, mid, ql, qr);
        if (ql > mid) return query(node * 2 + 1, mid + 1, r, ql, qr);
        
        return merge_node(query(node * 2, l, mid, ql, qr), query(node * 2 + 1, mid + 1, r, ql, qr));
    }


    int find_first_ge(int node, int l, int r, int ql, int qr, T target) const {
        if (l > qr || r < ql || tree[node].max_val < target) return -1;
        
        if (l == r) return l;

        int mid = l + (r - l) / 2;
        int res = -1;
        
        if (mid >= ql) res = find_first_ge(node * 2, l, mid, ql, qr, target);
        if (res != -1) return res;
        
        return find_first_ge(node * 2 + 1, mid + 1, r, ql, qr, target);
    }

    int find_last_ge(int node, int l, int r, int ql, int qr, T target) const {
        if (l > qr || r < ql || tree[node].max_val < target) return -1;
        
        if (l == r) return l;

        int mid = l + (r - l) / 2;
        int res = -1;

        if (qr > mid) res = find_last_ge(node * 2 + 1, mid + 1, r, ql, qr, target);
        if (res != -1) return res;

        return find_last_ge(node * 2, l, mid, ql, qr, target);
    }

    int find_first_le(int node, int l, int r, int ql, int qr, T target) const {
        if (l > qr || r < ql || tree[node].min_val > target) return -1;
        
        if (l == r) return l;

        int mid = l + (r - l) / 2;
        int res = -1;

        if (mid >= ql) res = find_first_le(node * 2, l, mid, ql, qr, target);
        if (res != -1) return res;

        return find_first_le(node * 2 + 1, mid + 1, r, ql, qr, target);
    }

    int find_last_le(int node, int l, int r, int ql, int qr, T target) const {
        if (l > qr || r < ql || tree[node].min_val > target) return -1;
        
        if (l == r) return l;

        int mid = l + (r - l) / 2;
        int res = -1;

        if (qr > mid) res = find_last_le(node * 2 + 1, mid + 1, r, ql, qr, target);
        if (res != -1) return res;

        return find_last_le(node * 2, l, mid, ql, qr, target);
    }

public:
    SegmentTree(const vector<T> &a) : n(a.size()), tree(4 * n) {
        build(a, 1, 0, n - 1);
    }
    
    void update(int i, T val) {
        update(1, 0, n - 1, i, val);
    }

    Node query(int l, int r) {
        if (l > r) return {numeric_limits<T>::max(), numeric_limits<T>::min()};
        return query(1, 0, n - 1, l, r);
    }

    int find_first_ge(int l, int r, T val) {
        if (l > r) return -1;
        return find_first_ge(1, 0, n - 1, l, r, val);
    }

    int find_last_ge(int l, int r, T val) {
        if (l > r) return -1;
        return find_last_ge(1, 0, n - 1, l, r, val);
    }

    int find_first_le(int l, int r, T val) {
        if (l > r) return -1;
        return find_first_le(1, 0, n - 1, l, r, val);
    }

    int find_last_le(int l, int r, T val) {
        if (l > r) return -1;
        return find_last_le(1, 0, n - 1, l, r, val);
    }
};