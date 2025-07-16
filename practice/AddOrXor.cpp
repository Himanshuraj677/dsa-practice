#include<iostream>
using namespace std;

int main () {
    int t;
    cin >> t;
    while (t--) {
        int a, b, x, y;
        cin >> a >> b >> x >> y;
        int diff = a - b;
        if (diff > 1) return -1;
        if (diff == 1) {
            if (a % 2) return y;
            else return -1;
        }
        else if (a == b) return 0;
        else {
            if (x <= y) return diff * x;
            else {
                
            }
        }
        
    }
    return 0;
}