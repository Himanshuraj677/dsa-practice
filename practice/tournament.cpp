#include<iostream>
using namespace std;

int main () {
    int t;
    cin >> t;
    while (t--) {
        int n, j, k;
        cin >> n >> j >> k;
        int *strength = new int[n + 1];
        for (int i = 1; i <= n; i++) cin >> strength[i];
        if (k == 1) {
            int max_strength = INT_MIN;
            for (int i = 1; i <= n; i++) max_strength = max(max_strength, strength[i]);
            if (max_strength > strength[j]) cout << "NO" << endl;
            else cout << "YES" << endl;
        }
        else cout << "YES" << endl;
        delete[] strength;
    }
    return 0;
}