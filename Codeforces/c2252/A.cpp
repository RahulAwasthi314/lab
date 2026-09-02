#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void f() {
    int n;
    cin >> n;
    
    map<int, int> counts;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        counts[a]++;
    }
    
    long long max_damage = 0;
    
    // Test all possible number of cards played (from 1 to n)
    for (int S = 1; S <= n; S++) {
        int limit = S / 2 + 1; // max allowed frequency for length S
        vector<int> pool;
        
        // Build the available pool strictly abiding by the limit
        for (auto const& [val, count] : counts) {
            int allowed_take = min(count, limit);
            for (int i = 0; i < allowed_take; i++) {
                pool.push_back(val);
            }
        }
        
        // If we have enough cards to form a sequence of length S
        if (pool.size() >= S) {
            sort(pool.rbegin(), pool.rend()); // Sort descending to greedily maximize damage
            long long current_sum = 0;
            for (int i = 0; i < S; i++) {
                current_sum += pool[i];
            }
            max_damage = max(max_damage, current_sum);
        }
    }
    
    cout << max_damage << "\n";
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