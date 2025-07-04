#include<iostream>
using namespace std;

int main () {
    int n, t;
    cin >> t;
    string winner[] = {"Alice", "Bob"};
    while (t--) {
        cin >> n;
        n--;
        if (n % 4 == 3) cout << winner[1] << endl;
        else cout << winner[0] << endl;
    }
}


/*
0 -> 3
1 -> 2

4 -> 7
5 -> 6

8 -> 11
9 -> 10

12 -> 15
13 -> 14
*/ 