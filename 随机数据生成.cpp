#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int get_rand(int L, int R) {
    return uniform_int_distribution<int>(L, R)(rng);
}

void get_permutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);

    cout << n << "\n";
    for (int v : p) cout << v << " ";
    cout << "\n";
}

void get_rand_arr(int n, int mn, int mx) {
    cout << n << "\n";
    for (int i = 1; i <= n; i ++) {
        cout << get_rand(mn, mx) << " \n"[i == n];
    }
}

void get_tree(int n) {
    cout << n << "\n";
    int type = get_rand(1, 3);
    for (int i = 2; i <= n; i ++) {
        int pa;
        if (type == 1) pa = get_rand(1, i - 1);
        else if (type == 2) pa = 1;
        else pa = i - 1;
        cout << i << ' ' << pa << "\n";
    }
}

void get_DAG(int n = 10000, int m = 15000) {
    ll max_edges = 1ll * n * (n - 1) / 2;
    if (m > max_edges) m = max_edges;

    cout << n << " " << m << "\n";

    // id[1] 到 id[n] 存储的是打乱后的真实输出编号
    vector<int> id(n + 1);
    iota(id.begin(), id.end(), 0);
    shuffle(id.begin() + 1, id.end(), rng); // 把 1~n 打乱

    set<pair<int, int>> edges;
    for (int i = 0; i < m; i ++) {
        int u, v;
        while (true) {
            u = get_rand(1, n - 1);
            v = get_rand(u + 1, n);
            
            if (edges.find({u, v}) == edges.end()) {
                edges.insert({u, v});
                break;
            }
        }
    }

    for (auto edge : edges) {
        int real_u = id[edge.first];
        int real_v = id[edge.second];
        
        cout << real_u << " " << real_v << "\n";
    }
}


void solve() {
    
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T --) {
        solve();
    }
}