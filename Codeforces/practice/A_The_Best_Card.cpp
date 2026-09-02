#include <bits/stdc++.h>

#define ll long long
#define vi vector<int>
#define pii pair<int, int>

using namespace std;

const int CF_MOD = 998244353;
const int MOD = 10e9+7;

void solve() {
    // write solution here
    int n;
    cin >> n;
    n++;

    if (n <= 2) {
        cout << "YES\n";
        return;
    }
    
    bool flag = false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            flag = true;
            break;
        }
    }

    cout << (flag ? "NO" : "YES") << "\n";

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