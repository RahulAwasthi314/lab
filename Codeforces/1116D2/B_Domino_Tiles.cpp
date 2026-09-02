#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MOD = 998244353;

void solve(int n, string& s, vector<string>& patterns)  {
    int valid = 0;
    for (auto& p : patterns) {
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (s[i] != '?' && s[i] != p[i%4]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            valid++;
        }
    }
    cout << valid % MOD << "\n";
    
}

void f() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<string> pat = {"0011", "0110", "1001", "1100"};

    solve(n, s, pat);
}

int main() {
    int t ;
    cin >> t;
    while (t--) {
        f();


    }
    return 0;
}
