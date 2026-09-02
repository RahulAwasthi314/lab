#include <bits/stdc++.h>
#define ll long long
using namespace std;

void f() {
    vector<ll> v(3);
    cin >> v[0] >> v[1] >> v[2];
    sort(v.begin(), v.end());
    ll ans = min(v[2]-v[0], v[1]);
    cout << ans << "\n";
}

int main() {
    int t ;
    cin >> t;
    while (t--) {
        f();


    }
    return 0;
}
