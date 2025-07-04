#include<iostream>
#include<vector>
using namespace std;
int main () {
    string s = "223106464654313151456133213132065465464";
    int n = s.size();
    vector<int> dp(n, 0);

    if (s[0] == '0') dp[0] = 0;
    else dp[0] = 1;

    for (int i = 1; i < n; i++) {
        if (s[i] == '0') dp[i] = 0;
        else dp[i] = 1;
        if (s[i - 1] == '1' || ((s[i - 1] == '2') && s[i] <= '6')) {
            dp[i] += 1;
        }
        dp[i] += dp[i - 1];
    }
    cout << dp[n - 1] << endl;
}