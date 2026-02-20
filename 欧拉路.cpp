#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 有向
void solve1() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<int> cur(n + 1), d(n + 1);
    for (int i = 0; i < m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        d[u] ++;
        d[v] --;
    }

    int st = -1;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0;
    for (int i = 1; i <= n; i ++) {
        if (d[i] == 1) {
            st = i;
            cnt1 ++;
        } else if (d[i] == -1) {
            cnt2 ++;
        } else if (d[i] != 0) cnt3 ++;
    }

    // 有向图最多只有一个{出度 - 入度 == 1 && 入度 - 出度 == 1}(这两个点分别是起点和终点)
    // 其他的点出度必须等于入度, 否则就不是欧拉路
    if (cnt3 > 0) {
        cout << -1 << "\n";
        return ;
    }

    if (cnt1 == 0 && cnt2 == 0) {
        for (int i = 1; i <= n; i ++) {
            if (!adj[i].empty()) {
                st = i;
                break;
            }
        }
    } else if (cnt1 != 1 || cnt2 != 1) {
        cout << -1 << "\n";
        return ;
    }

    vector<int> ans;
    function<void(int)> dfs = [&](int u) {
        for (int &i = cur[u]; i < adj[u].size();) {
            int v = adj[u][i ++];
            dfs(v);
        }
        ans.push_back(u);
    };

    if (st == -1) st = 1;
    dfs(st);

    if (ans.size() != m + 1) {
        cout << -1 << "\n";
        return ;
    }

    reverse(ans.begin(), ans.end());
    for (int x : ans) cout << x << ' ';
    cout << "\n";
}


// 无向
struct Edge {
    int to, id;
};

void solve2() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    int st = -1, cnt = 0;
    for (int i = 1; i <= n; i ++) {
        if (adj[i].size() & 1) {
            st = i;
            cnt ++;
        }
    }

    if (!cnt) {
        for (int i = 1; i <= n; i ++) {
            if (!adj[i].empty()) {
                st = i;
                break;
            }
        }
    } else if (cnt != 2) {
        cout << -1 << "\n";
        return ;
    }

    vector<int> cur(n + 1), used(m), ans;
    function<void(int)> dfs = [&](int u) {
        for (int &i = cur[u]; i < adj[u].size();) {
            int v = adj[u][i].to, id = adj[u][i].id;
            
            if (used[id]) {
                i ++;
                continue;
            }
            used[id] = 1;
            i ++;
            dfs(v);
        }
        ans.push_back(u);
    };

    if (st == -1) st = 1;
    dfs(st);

    if (ans.size() != m + 1) {
        cout << -1 << "\n";
        return ;
    }

    reverse(ans.begin(), ans.end());
    for (int x : ans) cout << x << " ";
    cout << "\n";
}
