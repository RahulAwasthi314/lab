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

void f() {
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
        f();
    }
    return 0;
}