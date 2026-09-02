#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve() {
    ll x, y;
    cin >> x >> y;

    ll N_max = sqrt(2.0 * (x + y));
    while ((N_max + 1) * (N_max + 2) / 2 <= x + y) {
        N_max++;
    }
    while (N_max * (N_max + 1) / 2 > x + y) {
        N_max--;
    }

    ll best_N = 0;
    ll best_p = 0;
    ll best_cost = -1;

    for (ll N = 0; N <= N_max; ++N) {
        ll S = N * (N + 1) / 2;
        
        ll L = max(0LL, S - y);
        ll R = min(S, x);

        if (L > R) continue;

        ll ideal_p = (x - y + S) / 2;
        ll cands[4] = {L, R, ideal_p, ideal_p + 1};

        for (ll p : cands) {
            if (p >= L && p <= R) {
                ll q = S - p;
                ll cost = (x - p) * (x - p) + (y - q) * (y - q);
                
                if (best_cost == -1 || cost < best_cost) {
                    best_cost = cost;
                    best_N = N;
                    best_p = p;
                }
            }
        }
    }

    string s(best_N, 'Y');
    ll target = best_p;
    
    for (ll i = best_N; i >= 1; --i) {
        if (target >= i) {
            target -= i;
            s[best_N - i] = 'X'; 
        }
    }
    
    cout << s << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
