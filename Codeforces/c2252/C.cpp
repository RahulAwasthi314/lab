#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    long long cnt;
    long long sum;
};

void f() {
    int n, m;
    cin >> n >> m;
    
    vector<long long> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    
    vector<vector<long long>> a(n, vector<long long>(m));
    vector<long long> vals;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            vals.push_back(a[i][j]);
        }
    }
    
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int K = vals.size();
    
    vector<Node> tree(4 * K + 1, {0, 0});
    
    auto update = [&](auto& self, int node, int l, int r, int idx, long long val) -> void {
        tree[node].cnt++;
        tree[node].sum += val;
        if (l == r) return;
        int mid = l + (r - l) / 2;
        if (idx <= mid) self(self, node * 2, l, mid, idx, val);
        else self(self, node * 2 + 1, mid + 1, r, idx, val);
    };
    
    auto query = [&](auto& self, int node, int l, int r, long long V) -> long long {
        if (l == r) {
            // Need just enough pieces of this specific value
            return (V + vals[l - 1] - 1) / vals[l - 1]; 
        }
        int mid = l + (r - l) / 2;
        if (tree[node * 2 + 1].sum >= V) {
            return self(self, node * 2 + 1, mid + 1, r, V);
        } else {
            return tree[node * 2 + 1].cnt + self(self, node * 2, l, mid, V - tree[node * 2 + 1].sum);
        }
    };
    
    long long ans = m;
    
    // Process from bottom to top
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < m; ++j) {
            int idx = lower_bound(vals.begin(), vals.end(), a[i][j]) - vals.begin() + 1;
            update(update, 1, 1, K, idx, a[i][j]);
        }
        
        if (tree[1].sum >= v[i]) {
            long long cur = query(query, 1, 1, K, v[i]);
            ans = min(ans, cur);
        }
    }
    
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            f();
        }
    }
    return 0;
}