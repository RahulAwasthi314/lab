#include <bits/stdc++.h>

#define ll long long
#define vi vector<int>
#define vll vector<long long>
#define pii pair<int, int>

using namespace std;

const int CF_MOD = 998244353;
const int MOD = 10e9+7;

void solve() {
    // write solution here
    ll n, m;
    cin >> n >> m;

    vll v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    vll u(m);
    for (int i = 0; i < m; i++) {
        cin >> u[i];
    }
    

    ll hb = v[0] + n-1;
    ll bu = u[0] + m -1;

    if (hb >= bu) {
        cout << "1\n";
    }
    else {
        cout << "2\n";
    }

    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}