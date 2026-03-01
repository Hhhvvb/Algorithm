#include <bits/stdc++.h>

using namespace std;
using ll = long long;

//Tarjan 算法对于 low 的极严密数学定义是：一棵子树，只允许使用至多一条返祖边，所能到达的最高祖先的 dfn。

// 边双连通分量(e-DCC)
void solve_e_DCC() {
    int n, m;
    cin >> n >> m;
    vector<vector<array<int, 2>>> adj(n + 1);
    for (int i = 0; i < m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    vector<int> dfn(n + 1), low(n + 1), dcc(n + 1);
    vector<vector<int>> ans;
    stack<int> stk;
    int timestamp = 0, dcc_cnt = 0;
    auto tarjan = [&](auto&& self, int u, int last) -> void {
        dfn[u] = low[u] = ++ timestamp;
        stk.push(u);
        for (int i = 0; i < adj[u].size(); i ++) {
            int v = adj[u][i][0], id = adj[u][i][1];
            if (id == last) continue;
            if (!dfn[v]) {
                self(self, v, id);
                low[u] = min(low[u], low[v]);
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            vector<int> res;
            res.push_back(u);
            dcc[u] = ++ dcc_cnt;
            while (stk.top() != u) {
                int x = stk.top();
                res.push_back(x);
                dcc[x] = dcc_cnt;
                stk.pop();
            }
            stk.pop();
            ans.push_back(res);
        }
    };
    for (int i = 1; i <= n; i ++) {
        if (!dfn[i]) tarjan(tarjan, i, -1);
    }
    cout << ans.size() << endl;;
    for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i].size() << ' ';
        for (int j = 0; j < ans[i].size(); j ++) cout << ans[i][j] << ' ';
        cout << endl;
    }
}

// 点双连通分量(v-DCC)
void solve_v_DCC() {
    int n, m;
    cin >> n >> m;
    vector<vector<array<int, 2>>> adj(n + 1);
    for (int i = 0; i < m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    vector<int> dfn(n + 1), low(n + 1);
    vector<vector<int>> ans;
    stack<int> stk;
    int timestamp = 0, root = 0;
    auto tarjan = [&](auto&& self, int u, int last) -> void {
        dfn[u] = low[u] = ++ timestamp;
        stk.push(u);
        int child = 0;
        for (int i = 0; i < adj[u].size(); i ++) {
            int v = adj[u][i][0], id = adj[u][i][1];
            if (id == last) continue;
            if (!dfn[v]) {
                child ++;
                self(self, v, id);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    vector<int> res;
                    res.push_back(u);
                    while (stk.top() != v) {
                        int x = stk.top();
                        stk.pop();
                        res.push_back(x);
                    }
                    res.push_back(v);
                    stk.pop();
                    ans.push_back(res);
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
        
        // 判断是否是孤点(自环情况)
        if (u == root && !child) {
            ans.push_back({u});
            stk.pop();
        }
    };
    for (int i = 1; i <= n; i ++) {
        if (!dfn[i]) {
            root = i;
            tarjan(tarjan, i, -1);
        }
    }
    cout << ans.size() << endl;;
    for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i].size() << ' ';
        for (int j = 0; j < ans[i].size(); j ++) cout << ans[i][j] << ' ';
        cout << endl;
    }
}

// 判断割点
void judge_cut() {
    int n, m;
    cin >> n >> m;
    vector<vector<array<int, 2>>> adj(n + 1);
    for (int i = 0; i < m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    vector<int> dfn(n + 1), low(n + 1);
    vector<bool> is_cut(n + 1);
    int timestamp = 0, root = 0;
    function<void(int, int)> tarjan = [&](int u, int last) {
        dfn[u] = low[u] = ++ timestamp;
        int child = 0;
        for (int i = 0; i < adj[u].size(); i ++) {
            int v = adj[u][i][0], id = adj[u][i][1];
            if (id == last) continue;
            if (!dfn[v]) {
                child ++;
                tarjan(v, id);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u] && (u != root || child > 1)) {
                    is_cut[u] = true;
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };
    for (int i = 1; i <= n; i ++) {
        if (!dfn[i]) {
            root = i;
            tarjan(i, -1);
        }
    }
    
    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        if (is_cut[i]) ans ++;
    }
    cout << ans << endl;;
    for (int i = 1; i <= n; i ++) {
        if (is_cut[i]) cout << i << " ";
    }
    cout << "\n";
}

// SCC缩点
void SCC() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) cin >> a[i];

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<int> dfn(n + 1), low(n + 1), scc(n + 1);
    int timestamp = 0, scc_cnt = 0;
    stack<int> stk;
    vector<bool> in_stk(n + 1);
    vector<ll> w(n + 1);
    auto tarjan = [&](auto&& self, int u) -> void {
        dfn[u] = low[u] = ++ timestamp;
        stk.push(u);
        in_stk[u] = true;
        for (int v : adj[u]) {
            if (!dfn[v]) {
                self(self, v);
                low[u] = min(low[u], low[v]);
            } else if (in_stk[v]) low[u] = min(low[u], dfn[v]);
        }

        if (low[u] == dfn[u]) {
            ll sum = 0;
            scc_cnt ++;
            while (stk.top() != u) {
                int x = stk.top();
                stk.pop();
                in_stk[x] = false;
                sum += a[x];
                scc[x] = scc_cnt;
            }
            stk.pop();
            in_stk[u] = false;
            sum += a[u];
            scc[u] = scc_cnt;
            w[scc_cnt] = sum;
        }
    };

    for (int i = 1; i <= n; i ++) {
        if (!dfn[i]) {
            tarjan(tarjan, i);
        }
    }

    vector<vector<int>> new_adj(scc_cnt + 1);
    for (int u = 1; u <= n; u ++) {
        for (int v : adj[u]) {
            int id1 = scc[u], id2 = scc[v];
            if (id1 == id2) continue;
            new_adj[id1].push_back(id2);
        }
    }

    // 去重边:
    for (int u = 1; u <= scc_cnt; u ++) {
        sort(new_adj[u].begin(), new_adj[u].end());
        new_adj[u].erase(unique(new_adj[u].begin(), new_adj[u].end()), new_adj[u].end());
    }

    vector<ll> dp(scc_cnt + 1);
    vector<bool> st(scc_cnt + 1);
    auto dfs = [&](auto&& self, int u) -> void {
        st[u] = true;
        dp[u] = w[u];
        for (int v : new_adj[u]) {
            if (!st[v]) self(self, v);
            dp[u] = max(dp[u], dp[v] + w[u]);
        }
    };

    ll ans = 0;
    for (int i = 1; i <= scc_cnt; i ++) {
        if (!st[i]) dfs(dfs, i);
        ans = max(ans, dp[i]);
    }

    cout << ans << "\n";
}