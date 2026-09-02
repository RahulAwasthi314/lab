#include <bits/stdc++.h>
#define ll long long
#define vi vector<int>
using namespace std;

void solve(ll n, string ans, string s) {
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            int next = (i+1) %n;
            if (s[next] == '0') {
                ans[next] = '1';
            }
            else {
                ans[i] = '1';
            }
        }
    }

    int red = 0, blue = 0;

    for (int i = 0; i < n; i++) {
        if (ans[i] == '1') {
            if (i & 1 == 1) {
                red++;
            }
            else {
                blue++;
            }
        }
        
    }
    cout << red << " " << blue << "\n";
}

void f() {
    ll n, k;
    cin >> n >> k;
    string b;
    cin >> b; // 2n size

    ll n_next = 2*n;
    string ss (n_next, '0');

    solve(n_next, ss, b);

}

int main() {
    int t ;
    cin >> t;
    while (t--) {
        f();
    }
    return 0;
}
