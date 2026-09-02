#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void f() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int C0 = 0, C1 = 0;
    for (char c : s) {
        if (c == '0') C0++;
        else C1++;
    }

    // Find longest alternating subsequence starting with '0'
    int len0 = 0;
    char expected = '0';
    for (char c : s) {
        if (c == expected) {
            len0++;
            expected = (expected == '0') ? '1' : '0';
        }
    }

    // Find longest alternating subsequence starting with '1'
    int len1 = 0;
    expected = '1';
    for (char c : s) {
        if (c == expected) {
            len1++;
            expected = (expected == '1') ? '0' : '1';
        }
    }

    for (int L = n; L >= 1; --L) {
        if (L % 2 == 0) {
            int k0 = L / 2;
            int k1 = L / 2;
            if (L <= len0 || L <= len1) {
                if (abs((C0 - k0) - (C1 - k1)) <= 1) {
                    cout << n - L << "\n";
                    return;
                }
            }
        } else {
            // Case 1: Starts with '0' -> k0 = k1 + 1
            int k0 = (L + 1) / 2;
            int k1 = (L - 1) / 2;
            if (L <= len0) {
                if (abs((C0 - k0) - (C1 - k1)) <= 1) {
                    cout << n - L << "\n";
                    return;
                }
            }

            // Case 2: Starts with '1' -> k1 = k0 + 1
            k0 = (L - 1) / 2;
            k1 = (L + 1) / 2;
            if (L <= len1) {
                if (abs((C0 - k0) - (C1 - k1)) <= 1) {
                    cout << n - L << "\n";
                    return;
                }
            }
        }
    }
    
    // Check for length 0
    if (abs(C0 - C1) <= 1) {
        cout << n << "\n";
    } else {
        cout << -1 << "\n";
    }
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