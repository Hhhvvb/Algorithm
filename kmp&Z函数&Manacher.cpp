#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// kmp
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

// 扩展kmp(Z函数)
void solve() {
    int n;
    string s;
    cin >> n >> s;

    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i ++) {
        if (i < r) z[i] = min(z[i - l], r - i);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i] ++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
}

// 马拉车算法(Manacher)
void solve() {
    int n;
    string s;
    cin >> n >> s;

    string t = "^#";
    for (char c : s) t += c, t += '#';
    t += '$';

    int m = t.size();
    vector<int> p(m);
    int c = 0, r = 0;
    for (int i = 1; i < m - 1; i ++) {
        if (i < r) p[i] = min(p[2 * c - i], r - i);
        while (t[i - p[i] - 1] == t[i + p[i] + 1]) p[i] ++;
        if (i + p[i] > r) c = i, r = i + p[i];
    }
}