#include <bits/stdc++.h>

#define ll long long
#define vi vector<int>
#define pii pair<int, int>

using namespace std;

const int CF_MOD = 998244353;
const int MOD = 10e9+7;

void solve() {
    // write solution here
    string s;
    cin >> s;
    
    // // alice 0 -> large -> left se remove 0
    // // bob -> small -> left se right remove 1
    
    bool f = false, g = false;
    int i = 0;
    while (i < s.size()) {
        if (s[i] == '0' && !f) {
            s[i] = 'x';
            f = true;
        }
        else if (s[i] == '1' && !g) {
            s[i] = 'x';
            g = true;
        }
        i++;
    }

    for (int i = 0; i < s.size(); i++) {
        if (s[i] != 'x') {
            cout << s[i] ;
        }
    }
    cout << "\n";

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