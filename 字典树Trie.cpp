#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int MX = 3000010;

int son[MX][2], mx_idx[MX], tot = 0;;

void init() {
    for (int i = 0; i <= tot; i ++) {
        son[i][0] = son[i][1] = mx_idx[i] = 0;
    }
    tot = 0;
}

void insert(int v, int idx) {
    int p = 0;
    for (int i = 29; i >= 0; i --) {
        int bit = v >> i & 1;
        if (!son[p][bit]) {
            son[p][bit] = ++ tot;
        }
        p = son[p][bit];
        mx_idx[p] = max(mx_idx[p], idx);
    }
}

int query(int v, int lim) {
    int p = 0, res = 0;
    for (int i = 29; i >= 0; i --) {
        int bit_v = v >> i & 1, bit_lim = lim >> i & 1;
        if (bit_lim) {
            // if (son[p][bit_v]) {
            //     res = max(res, mx_idx[son[p][bit_v]]);
            // }
            // if (!son[p][bit_v ^ 1]) return res;
            // p = son[p][bit_v ^ 1];

        } else {
            // if (!son[p][bit_v]) return res;
            // p = son[p][bit_v];
            
        }
    }
    return max(res, mx_idx[p]);
}