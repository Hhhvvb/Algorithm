#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// ```````````````````````````````````````````````````````````````````````````
// 1. 预处理 + 乘法逆元
const int MOD = 1e9 + 7;
const int MAXN = 200005;

ll fact[MAXN], infact[MAXN];

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void init() {
    fact[0] = 1;
    infact[0] = 1;
    for (int i = 1; i < MAXN; i ++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    infact[MAXN - 1] = qpow(fact[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; i --) {
        infact[i] = infact[i + 1] * (i + 1) % MOD;
    }
}

ll C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * infact[k] % MOD * infact[n - k] % MOD;
}


// ```````````````````````````````````````````````````````````````````````````
// 2. 杨辉三角递推
const int N = 2005;
const int MOD = 1e9 + 7;

int c[N][N];

void init() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0) c[i][j] = 1;
            else c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
        }
    }
}


// ```````````````````````````````````````````````````````````````````````````
// 3. Lucas定理(n, k = 1e18, mod = 1e5):
const int p = 100003; // 必须是质数

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

ll C(ll n, ll k) {
    if (k < 0 || k > n) return 0;
    ll a = 1, b = 1;
    for (int i = 0; i < k; i++) {
        a = a * (n - i) % p;
        b = b * (i + 1) % p;
    }
    return a * qpow(b, p - 2) % p;
}

ll lucas(ll n, ll k) {
    if (k == 0) return 1;
    return C(n % p, k % p) * lucas(n / p, k / p) % p;
}
// ```````````````````````````````````````````````````````````````````````````