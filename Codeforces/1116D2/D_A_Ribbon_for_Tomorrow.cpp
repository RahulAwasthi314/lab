#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MOD = 998244353;
const int MAX = 1000005;

ll factorial[MAX], inversal[MAX];

ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

void compute() {
    factorial[0] = 1;
    inversal[0] = 1;
    for (int i = 1; i < MAX; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    inversal[MAX - 1] = power(factorial[MAX - 1], MOD - 2);
    for (int i = MAX - 2; i >= 1; i--) {
        inversal[i] = (inversal[i + 1] * (i + 1)) % MOD;
    }
}

ll nnCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return factorial[n] * inversal[r] % MOD * inversal[n - r] % MOD;
}

void f() {
    int n;
    string s;
    cin >> n >> s;

    int a = 0, b = 0, c = 0, d = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            a++;
            if (i == 0 || s[i - 1] != '0') c++;
        } else {
            b++;
            if (i == 0 || s[i - 1] != '1') d++;
        }
    }

    ll ways0 = 1;
    if (a > 0 && c > 0) {
        ways0 = nnCr(a - 1, c - 1);
    }

    ll ways1 = 1;
    if (b > 0 && d > 0) {
        ways1 = nnCr(b - 1, d - 1);
    }

    ll ans = (ways0 * ways1) % MOD;
    cout << ans << "\n";
}

int main() {
    compute();
    
    int t;
    cin >> t;
    while (t--) {
        f();
    }
    
    return 0;
}