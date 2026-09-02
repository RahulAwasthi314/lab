To find the number of valid triplets $(a, b, c)$, we can analyze the given conditions using bitwise properties.

### Mathematical Analysis

1. **Arithmetic Progression:**
$b - a = c - b \implies a + c = 2b$.
2. **XOR Condition:**
$a \oplus b \oplus c = 0 \implies a \oplus c = b$.

Let $x = a \ \& \ c$. A well-known identity states that $a + c = (a \oplus c) + 2(a \ \& \ c)$.
Substituting $b = a \oplus c$ into this identity gives:
$a + c = b + 2x$
Since $a + c = 2b$, we get $2b = b + 2x \implies b = 2x$.
This also means $a \oplus c = 2x$.

For $a \ \& \ c = x$ and $a \oplus c = 2x$ to hold simultaneously, $x$ and $2x$ must not share any set bits. This means **$x$ cannot have any consecutive 1s in its binary representation** (i.e., $x \ \& \ (x \ll 1) = 0$).

We can express $a$ and $c$ in terms of $x$ and a mask $y$:

* $a = x + y$
* $c = 3x - y$
where $y$ is formed by a subset of the set bits of $2x$.
For the condition $a < b$ to hold, we need $x + y < 2x \implies y < x$. This happens exactly when the highest set bit of $2x$ is **not** included in $y$.

Since $c$ is strictly determined by $x$ and $y$, and the mapping is bijective, we can just count the number of valid $c \le n$.
By analyzing the bits of $c = 3x - y = x + (2x - y)$, we can determine the $i$-th bit of $c$ (let's call it $c_i$) directly from $x_i$ and $x_{i-1}$:

* If $x_i = 1$, then $c_i = 1$.
* If $x_{i-1} = 1$, then $c_i = d_{i-1} \in \{0, 1\}$. (If $x_{i-1}$ is the highest set bit of $x$, $d_{i-1}$ must be 1).
* If $x_i = 0$ and $x_{i-1} = 0$, then $c_i = 0$.

This allows us to use **Digit DP** from the most significant bit to the least significant bit.

### C++ Solution

```cpp
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

long long dp[65][2][2][2];
long long n;

long long solve(int i, int tight, int started, int prev_x) {
    // Base case: bits exhausted
    if (i == 0) {
        if (!started) return 0; // x must be strictly greater than 0
        int c0 = prev_x;
        int n0 = (n >> 0) & 1;
        if (tight && c0 > n0) return 0;
        return 1;
    }
    
    if (dp[i][tight][started][prev_x] != -1)
        return dp[i][tight][started][prev_x];

    long long ans = 0;
    int ni = (n >> i) & 1;

    // We decide the (i-1)-th bit of x
    for (int x_cur = 0; x_cur <= 1; ++x_cur) {
        // x cannot have consecutive 1s
        if (prev_x == 1 && x_cur == 1) continue; 

        // d represents the choices for y's bits
        for (int d = 0; d <= 1; ++d) {
            if (x_cur == 0 && d == 1) continue; 
            if (x_cur == 1 && !started && d == 0) continue; // Highest bit's rule

            int ci; // The i-th bit of c
            if (prev_x == 1) ci = 1;
            else if (x_cur == 1) ci = d;
            else ci = 0;

            if (tight && ci > ni) continue; // Exceeds n

            int ntight = tight && (ci == ni);
            int nstarted = started | x_cur;
            
            ans = (ans + solve(i - 1, ntight, nstarted, x_cur)) % 1000000007;
        }
    }
    return dp[i][tight][started][prev_x] = ans;
}

void run_test_case() {
    cin >> n;
    memset(dp, -1, sizeof(dp));
    // Start deciding from the 61st bit (safely larger than 10^18 limit)
    cout << solve(61, 1, 0, 0) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            run_test_case();
        }
    }
    return 0;
}

```




#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int LOG = 19;

int n;
int c[MAXN], k[MAXN];
vector<int> adj[MAXN];
vector<int> color_nodes[MAXN];

int depth[MAXN], up[MAXN][LOG], in_time[MAXN], timer;

void dfs_lca(int u, int p, int d) {
    in_time[u] = ++timer;
    depth[u] = d;
    up[u][0] = p;
    for (int i = 1; i < LOG; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (int v : adj[u]) {
        if (v != p) dfs_lca(v, u, d + 1);
    }
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LOG - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = up[u][i];
        }
    }
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

int get_dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
}

int get_kth_ancestor(int u, int k_step) {
    for (int i = 0; i < LOG; i++) {
        if ((k_step >> i) & 1) u = up[u][i];
    }
    return u;
}

void solve() {
    cin >> n;
    timer = 0;
    for (int i = 1; i <= n; i++) {
        color_nodes[i].clear();
        adj[i].clear();
    }
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) cin >> k[i];
    
    for (int i = 1; i <= n; i++) {
        color_nodes[c[i]].push_back(i);
    }
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    dfs_lca(1, 1, 0);
    
    vector<long long> ans(n + 1, -1);
    
    for (int col = 1; col <= n; col++) {
        if (color_nodes[col].empty()) continue;
        
        auto& nodes = color_nodes[col];
        auto cmp = [&](int a, int b) { return in_time[a] < in_time[b]; };
        sort(nodes.begin(), nodes.end(), cmp);
        
        vector<int> v_nodes = nodes;
        int sz = nodes.size();
        for (int i = 0; i < sz - 1; i++) {
            v_nodes.push_back(get_lca(nodes[i], nodes[i + 1]));
        }
        sort(v_nodes.begin(), v_nodes.end(), cmp);
        v_nodes.erase(unique(v_nodes.begin(), v_nodes.end()), v_nodes.end());
        
        vector<int> st;
        vector<pair<int, int>> v_adj[v_nodes.size()];
        auto get_idx = [&](int u) {
            return lower_bound(v_nodes.begin(), v_nodes.end(), u, cmp) - v_nodes.begin();
        };
        
        for (int u : v_nodes) {
            while (!st.empty() && get_lca(st.back(), u) != st.back()) {
                st.pop_back();
            }
            if (!st.empty()) {
                int p = st.back();
                int len = depth[u] - depth[p];
                int p_idx = get_idx(p);
                int u_idx = get_idx(u);
                v_adj[p_idx].push_back({u_idx, len});
                v_adj[u_idx].push_back({p_idx, len});
            }
            st.push_back(u);
        }
        
        vector<int> subtree_c(v_nodes.size(), 0);
        for (int u : nodes) {
            subtree_c[get_idx(u)]++;
        }
        
        int total_c = nodes.size();
        vector<int> max_sub(v_nodes.size(), 0);
        
        auto dfs_size = [&](auto& self, int u, int p) -> void {
            for (auto& edge : v_adj[u]) {
                int v = edge.first;
                if (v != p) {
                    self(self, v, u);
                    subtree_c[u] += subtree_c[v];
                    max_sub[u] = max(max_sub[u], subtree_c[v]);
                }
            }
            max_sub[u] = max(max_sub[u], total_c - subtree_c[u]);
        };
        
        if (!v_nodes.empty()) dfs_size(dfs_size, 0, -1);
        
        int best_node = -1;
        int min_max_sub = total_c + 1;
        
        for (int i = 0; i < v_nodes.size(); i++) {
            if (max_sub[i] <= total_c / 2) {
                if (max_sub[i] < min_max_sub) {
                    min_max_sub = max_sub[i];
                    best_node = i;
                }
            }
        }
        
        int root_virt = best_node;
        if (root_virt == -1) root_virt = 0; 
        
        int root_orig = v_nodes[root_virt];
        
        // Find if the true median lies on an edge
        for (int i = 0; i < v_nodes.size(); i++) {
            if (i == root_virt) continue;
            for (auto& edge : v_adj[i]) {
                int v = edge.first;
                if (depth[v_nodes[i]] > depth[v_nodes[v]]) continue; // only check parent-child
                int c_down = subtree_c[v];
                if (c_down == total_c / 2 && total_c % 2 == 0) {
                    int dist = depth[v_nodes[v]] - depth[v_nodes[i]];
                    if (dist > 1) {
                        root_orig = get_kth_ancestor(v_nodes[v], dist / 2);
                    }
                }
            }
        }
        
        vector<int> cur_subtree(v_nodes.size(), 0);
        for (int u : nodes) cur_subtree[get_idx(u)] = 1;
        
        long long base_cost = 0;
        vector<pair<int, int>> weights;
        
        auto dfs_weights = [&](auto& self, int u, int p, int d_to_r) -> void {
            for (auto& edge : v_adj[u]) {
                int v = edge.first;
                int len = edge.second;
                if (v != p) {
                    self(self, v, u, d_to_r + len);
                    cur_subtree[u] += cur_subtree[v];
                    weights.push_back({cur_subtree[v], len});
                }
            }
            if (cur_subtree[u] > 0 && find(nodes.begin(), nodes.end(), v_nodes[u]) != nodes.end()) {
                 base_cost += d_to_r;
            }
        };
        
        if (!v_nodes.empty()) dfs_weights(dfs_weights, root_virt, -1, 0);
        
        long long total_dist = 0;
        for (int u : nodes) total_dist += get_dist(u, root_orig);
        
        weights.clear();
        fill(cur_subtree.begin(), cur_subtree.end(), 0);
        for (int u : nodes) cur_subtree[get_idx(u)] = 1;
        
        // Re-root virtually strictly around root_orig
        // For simplicity and to not exceed limits under stress, weights derivation is bounded to actual subtree topology 
        auto dfs_w2 = [&](auto& self, int u, int p) -> void {
            for (auto& edge : v_adj[u]) {
                int v = edge.first;
                int len = edge.second;
                if (v != p) {
                    self(self, v, u);
                    cur_subtree[u] += cur_subtree[v];
                    weights.push_back({cur_subtree[v], len});
                }
            }
        };
        
        fill(cur_subtree.begin(), cur_subtree.end(), 0);
        for (int u : nodes) cur_subtree[get_idx(u)] = 1;
        dfs_w2(dfs_w2, get_idx(v_nodes[0]), -1); // Just need sizes of subtrees towards true root!
        
        // Weights respect relative edges bounding root_orig
        vector<pair<int, int>> final_w;
        for (auto& edge : weights) {
            int w = edge.first;
            if (w > total_c / 2) w = total_c - w;
            if (w > 0) final_w.push_back({w, edge.second});
        }
        
        sort(final_w.rbegin(), final_w.rend());
        
        long long subtract = 0;
        int rem = k[col] - 1;
        for (auto& p : final_w) {
            if (rem == 0) break;
            int take = min(rem, p.second);
            subtract += 1LL * take * p.first;
            rem -= take;
        }
        ans[col] = total_dist - subtract;
    }
    
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}