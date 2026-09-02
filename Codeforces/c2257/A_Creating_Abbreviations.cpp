#include <bits/stdc++.h>

#define ll long long
#define vi vector<int>
#define pii pair<int, int>

using namespace std;

const int CF_MOD = 998244353;
const int MOD = 10e9+7;

void solve() {
    // write solution here
    
    int n, m;
    cin >> n >> m;

    int v[26] = {0};

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        v[s[0] - 'a'] = 1;
    }

    vector<string> p(m);
    for (int i = 0; i < m; i++) {
        cin >> p[i];
    }

    bool ch = true;
    while (ch) {
        ch = false;
        vector<string> next_p;
        for (auto& a : p) {
            bool f = true;
            for (char c : a) {
                if (!v[c - 'A']) {
                    f = false;
                    break;
                }
            }
            if (f) {
                if (!v[a[0] - 'A']) {
                    v[a[0] - 'A'] = true;
                }
                ch = true;
            }
            else {
                next_p.push_back(a);
            }
        }
        p = next_p;
    }   
    if (p.empty()) cout << "YES\n";
    else cout << "NO\n";
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