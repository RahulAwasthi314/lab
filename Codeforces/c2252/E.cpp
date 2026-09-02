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

