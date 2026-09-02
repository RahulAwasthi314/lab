#include <bits/stdc++.h>

#define ll long long
#define vi vector<int>
#define pii pair<int, int>

using namespace std;

const int CF_MOD = 998244353;
const int MOD = (10e9)+7;

void solve() {
    // write solution here
    
    int a, b, c;
    cin >> a >> b >> c;

    int ans = min({abs(a-b), abs(b-c), abs(c-a)});

    cout << ans << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}