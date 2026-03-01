#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    string s, p;
    cin >> s >> p;
    int n = s.size(), m = p.size();
    s = " " + s, p = " " + p;

    vector<int> ne(m + 1);      //最长相等前后缀
    for (int i = 2, j = 0; i <= m; i ++) {
        while (j && p[i] != p[j + 1]) j = ne[j];
        if (p[i] == p[j + 1]) j ++;
        ne[i] = j;
    }

    for (int i = 1, j = 0; i <= n; i ++) {
        while (j && s[i] != p[j + 1]) j = ne[j];
        if (s[i] == p[j + 1]) j ++;
        if (j == m) {
            // 数据处理...
            // cout << i - j + 1 << "\n";

            j = ne[j];
        }
    }

    for (int i = 1; i <= m; i ++) cout << ne[i] << " \n"[i == m];
}