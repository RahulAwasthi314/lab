#include <bits/stdc++.h>
using namespace std;

void f() {
    int n;
    cin >> n;
    vector<int> a(n), C, cnt;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Run length encoding
    // 1 1 2 2 2 3 3
    // 1->2   2->3   3->2
    for (int i = 0; i < n; i++) {
        if (C.empty() || a[i] != C.back()) {
            C.push_back(a[i]);
            cnt.push_back(1);
        } else {
            cnt.back()++;
        }
    }

    int k = C.size();
    
    // check for 2 2 length adjacent blocks
    // A A B B
    // A B A B -> k+2
    for (int i = 0; i < k - 1; i++) {
        if (cnt[i] >= 2 && cnt[i+1] >= 2) {
            cout << k + 2 << "\n";
            return;
        }
    }
    
    for (int i = 0; i < k; i++) {
        if (cnt[i] >= 2) {
            bool cl = (i > 0) && (i == 1 || C[i-2] != C[i]);
            bool cr = (i < k - 1) && (i == k - 2 || C[i+2] != C[i]);
            
            if (cl || cr) {
                cout << k + 1 << "\n";
                return;
            }
        }
    }
    cout << k << "\n";
}

int main() {
    
    int t;
    cin >> t;
    while (t--) {
        f();
    }
    
    return 0;
}