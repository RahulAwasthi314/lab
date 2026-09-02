#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void f() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<long long> d(n - 1);
    for (int i = 0; i < n - 1; i++) {
        d[i] = a[i + 1] - a[i];
    }

    int i = 0;
    while (i < n - 1) {
        int j = i;
        long long current_parity = abs(d[i]) % 2; 
        
        while (j < n - 1 && abs(d[j]) % 2 == current_parity) {
            j++;
        }
        
        sort(d.begin() + i, d.begin() + j);
        i = j;
    }

    cout << a[0] << " ";
    long long current = a[0];
    for (int k = 0; k < n - 1; k++) {
        current += d[k];
        cout << current << " ";
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