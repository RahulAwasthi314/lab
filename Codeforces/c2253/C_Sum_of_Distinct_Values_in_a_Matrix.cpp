#include <bits/stdc++.h>
#define ll long long

using namespace std;


void f() {
    ll n,m;
    int x, y;
    cin >> n >> m >> x >> y;
    
    int len_a = x;
    int len_b = y;

    vector<ll> a(x), b(y);
    for (int i = 0; i < x; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < y; i++) {
        cin >> b[i];
    }

    vector<pair<ll, int>> e;
    int i = 0, j = 0;

    while (i < x && j < y) {
        if (a[i] < b[j]) {
            e.push_back({a[i], 1});
            i++;
        }
        else if (a[i] > b[j]) {
            e.push_back({b[j], 2});
            j++;
        }
        else {
            e.push_back({a[i], 3});
            i++, j++;
        }
    }
    while (i < x) {
        e.push_back({a[i], 1}); i++;
    }
    while (j < y) {
        e.push_back({b[j], 2}); j++;
    }

    sort(e.rbegin(), e.rend());

    ll ta = 0, tb = 0, tab = 0;
    ll mxe = n+m-1, t_sum = 0;

    for (auto& p : e) {
        if (ta + tb + tab >= mxe) {
            break;
        }
        ll v = p.first;
        int type = p.second;

        switch (type) {        
            case 1:
                if (ta < n) {
                    ta++;
                    t_sum += v;
                }
                break;
            case 2:
                if (tb < m) {
                    tb++;
                    t_sum += v;
                }
                break;
            case 3:
                tab++;
                t_sum += v;
                break;
        }
    }
    cout << t_sum << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) 
    {
        f();
    }
    return 0;

}