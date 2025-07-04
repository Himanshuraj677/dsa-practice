// To solve any Dp problem, we need to follow these steps:
// 1. Identify the problem type (e.g., maximum, minimum, count, etc.)
// 2. Identify the state variables (e.g., indices, values, etc.)
// 3. Identify the choices (e.g., take or not take, include or exclude, etc.)
// 4. Identify the base cases (e.g., when to stop recursion, what to return)
// 5. Identify the recurrence relation (how to combine choices to form the solution)
// 6. Implement the solution using recursion, memoization, or tabulation
// 7. Optimize the solution if necessary (e.g., space optimization, time complexity reduction)


// 1. Maximum Product Subarray
// It can be solved using two approaches:
// a. Prefix and Suffix Products
// b. Kadane's Algorithm

int maxProduct(vector<int> &nums)
{
    int pre = 1, suff = 1, ans = INT_MIN;
    int size = nums.size();
    for (int i = 0; i < size; i++)
    {
        if (pre == 0)
            pre = 1;
        if (suff == 0)
            suff = 1;
        pre *= nums[i];
        suff *= nums[size - 1 - i];
        ans = max({pre, suff, ans});
    }
    return ans;
}

int maxProduct(vector<int>& nums) {
    int prod1 = nums[0], prod2 = nums[0], ans = nums[0];
    int size = nums.size();
    for (int i = 1; i < size; i++) {
        int temp = min({prod1 * nums[i], nums[i], prod2 * nums[i]});
        prod2 = max({prod1 * nums[i], nums[i], prod2 * nums[i]});
        prod1 = temp;
        ans = max(ans, prod2);
    }
    return ans;
}

// 2. Longest Increasing Subsequence
// This problem can be solved using two approaches:
// 1. Dynamic Programming with Tabulation
// 2. Using Binary Search

int helper (vector<int> &nums, vector<vector<int>> &dp, int ind, int prevIndex) {
    if (ind == nums.size()) return 0;
    if (dp[ind][prevIndex + 1] != -1) return dp[ind][prevIndex + 1];
    int take = 0;
    if (prevIndex == -1 || nums[prevIndex] < nums[ind]) take = 1 + helper(nums, dp, ind + 1, ind);
    int notTake = helper(nums, dp, ind + 1, prevIndex);
    return dp[ind][prevIndex + 1] = max(take, notTake);
}

int lengthOfLIS(vector<int>& nums) {
    int size = nums.size();
    vector<int> v;
    for (auto key: nums) {
        auto it = lower_bound(v.begin(), v.end(), key);
        if (it == v.end()) v.push_back(key);
        else *it = key;
    }
    return v.size();
}


// 3. Longest Common Subsequence

int longestCommonSubsequence(string text1, string text2) {
    int ind1 = 0, ind2 = 0;
    int size1 = text1.size(), size2 = text2.size();
    vector<vector<int>> dp(size1 + 1, vector<int> (size2 + 1, 0));
    for (int ind1 = size1 - 1; ind1 >= 0; ind1--) {
        for (int ind2 = size2 - 1; ind2 >= 0; ind2--) {
            int take = 0;
            if (text1[ind1] == text2[ind2]) {
                take = 1 + dp[ind1 + 1][ind2 + 1];
            }
            int notTake1 = dp[ind1 + 1][ind2];
            int notTake2 = dp[ind1][ind2 + 1];
            dp[ind1][ind2] = max({take, notTake1, notTake2});
        }
    }
    return dp[0][0];
}


// 4. 0/1 Knapsack Problem

int helper(int W, vector<int> &val, vector<int> &wt, int ind, vector<vector<int>> &dp) {
    if (ind == wt.size()) return 0;
    int take = 0;
    if (dp[W][ind] != -1) return dp[W][ind];
    if (W >= wt[ind]) {
        take = val[ind] + helper(W - wt[ind], val, wt, ind + 1, dp);
    }
    int notTake = helper(W, val, wt, ind + 1, dp);
    return dp[W][ind] = max(take, notTake);
}
int knapsack(int W, vector<int> &val, vector<int> &wt) {
    // code here
    int size = val.size();
    vector<vector<int>> dp(W + 1, vector<int>(size, -1));
    return helper(W, val, wt, 0, dp);
}


// 5. Edit Distance Problem

int helper(string &word1, string &word2, int ind1, int ind2, vector<vector<int>> &dp) {
    if (ind1 == word1.size()) {
        return word2.size() - ind2;
    }
    if (ind2 == word2.size()) {
        return word1.size() - ind1;
    }
    if (dp[ind1][ind2] != -1) return dp[ind1][ind2];
    if (word1[ind1] == word2[ind2]) {
        return helper(word1, word2, ind1 + 1, ind2 + 1, dp);
    }
    int insert = 1 + helper(word1, word2, ind1, ind2 + 1, dp);
    int remove = 1 + helper(word1, word2, ind1 + 1, ind2, dp);
    int replace = 1 + helper(word1, word2, ind1 + 1, ind2 + 1, dp);
    return dp[ind1][ind2] = min({insert, remove, replace});
}


// 6. Matrix Chain Multiplication
// It can be solved using partition DP approach

int helper (vector<int> &arr, int i, int j, vector<vector<int>> &dp) {
    if (i == j) return 0;
    int res = INT_MAX;
    if (dp[i][j] != -1) return dp[i][j];
    for (int k = i; k < j; k++) {
        int opr = helper(arr, i, k, dp) + helper(arr, k + 1, j, dp) + arr[i] * arr[k + 1] * arr[j + 1];
        res = min(res, opr);
    }
    return dp[i][j] = res;
}

// 7. Minimum Path Sum
int minPathSum(vector<vector<int>>& grid) {
    int row = grid.size(), col = grid[0].size();
    vector<int> curr(col, 0);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == 0 && j == 0) {
                curr[j] = grid[0][0];
                continue;
            }
            int left = (j - 1 >= 0) ? curr[j - 1] + grid[i][j] : 1e9;
            int up = (i - 1 >= 0) ? curr[j] + grid[i][j]: 1e9;
            curr[j] = min(left, up);
        }
    }
    return curr[col -1];
}

// 8. Coin Change Problem

int helper (vector<int> &coins, int amount, int ind, vector<vector<int>> &dp) {
    if (amount == 0) return 0;
    if (amount < 0 || ind < 0) return 1e9;
    if (dp[ind][amount] != -1) return dp[ind][amount];
    int take = 1 + helper(coins, amount - coins[ind], ind, dp);
    int notTake = helper(coins, amount, ind - 1, dp);
    return dp[ind][amount] = min(take, notTake);
}
int coinChange(vector<int>& coins, int amount) {
    int size = coins.size();
    vector<vector<int>> dp(size, vector<int>(amount + 1, -1));
    int coin = helper(coins, amount, size - 1, dp);
    return coin >= 1e9 ? -1 : coin;
}


// 9. Partition Equal Subset Sum
// It is similat to find target sum problem. Only difference is that we need to find if we can partition the array into two subsets with equal sum. We can do this by checking if we can find a subset with sum equal to total sum / 2.

int helper(vector<int> &grids, int ind, int target) {
    if (ind == grids.size() || target < 0) return false;
    if (target == 0) return true;
    if (helper(grids, ind + 1, target - grids[ind])) return true;
    if (helper(grids, ind + 1, target)) return true;
    return false;
}
bool canPartition(vector<int>& nums) {
    int sum = 0;
    for (auto it: nums) sum += it;
    if (sum % 2) return false;
    return helper(nums, 0, sum / 2);
}


// 10. Minimum cost to cut a stick
// It can be solved using partition DP approach.
int helper(int rodStart, int rodEnd, int cutsStart, int cutsEnd, vector<int>& cuts) {
    if (cutsStart > cutsEnd) return 0;
    int res = INT_MAX;
    for (int i = cutsStart; i <= cutsEnd; i++) {
        int leftCut = helper(rodStart, cuts[i], cutsStart, i - 1, cuts);
        int rightCut = helper(cuts[i], rodEnd, i + 1, cutsEnd, cuts);
        int cost = rodEnd - rodStart +  leftCut + rightCut;
        res = min(cost, res);
    }
    return res;
}
int minCost(int n, vector<int>& cuts) {
    int size = cuts.size();
    sort(cuts.begin(), cuts.end());
    return helper(0, n, 0, size - 1, cuts);
}



// 11. Egg Dropping Problem
// It is a classic problem that can be solved using dynamic programming and Binary Search.

int helper(int f, int e, vector<vector<int>> &dp) {
    if (e == 1 || f == 0 || f == 1) return f;
    if (dp[f][e] != -1) return dp[f][e];
    int res = INT_MAX;
    int low = 1, high = f;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int eggBreak = helper(mid - 1, e - 1, dp);
        int notBreak = helper(f - mid, e, dp);
        int temp =  1 + max(eggBreak, notBreak);
        res = min(res, temp);
        if (eggBreak > notBreak) {
            high = mid - 1;
        }
        else low = mid + 1;
    }
    return dp[f][e] = res;
}
int superEggDrop(int k, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, -1));
    return helper(n, k, dp);
}

// It can be solved using reverse thinking approach as well. (Reverse DP or Move Based DP)
int superEggDrop(int k, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
    int m = 0;
    while (dp[m][k] < n) {
        m++;
        for (int eggs = 1; eggs <= k; eggs++) {
            dp[m][eggs] = dp[m - 1][eggs - 1] + dp[m - 1][eggs] + 1;
        }
    }
    return m;
}



// 12. Word Break Problem
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    int size = s.size();
    vector<bool> dp(size + 1, false);
    dp[0] = true;
    for (int i = 1; i <= size; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[j] && dict.find(s.substr(j, i - j)) != dict.end()) {
                dp[i] = true;
            }
        }
    }
    return dp[size];
}


// 13. Palindrome Partitioning
// It can be further optimized using tabulation. We can use a 2D array to store the results of whether a substring is a palindrome or not.

bool checkPalindrome(string &s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

void helper(string &s, int ind, vector<vector<string>> &ans, vector<string> &temp) {
    if (ind == s.size()) {
        ans.push_back(temp);
        return;
    }
    for (int partition = ind + 1; partition <= s.size(); partition++) {
        string str = s.substr(ind, partition - ind);
        cout << str << endl;
        if (checkPalindrome(s, ind, partition - 1)) {
            temp.push_back(str);
            helper(s, partition, ans, temp);
            temp.pop_back();
        }
    }
}

vector<vector<string>> partition(string s) {
    vector<vector<string>> ans;
    vector<string> temp;
    helper(s, 0, ans, temp);
    return ans; 
}


// 14. Maximum Profit in Job Scheduling
// It is optimized using Binary Search and Memoization. We can use tabbulation to improve the space complexity.

int helper(int ind, vector<vector<int>> &arr, vector<int> &dp) {
    if (ind == arr.size()) return 0;
    if(dp[ind] != -1) return dp[ind];
    int low = ind + 1, high = arr.size() - 1;
    int nextInd = arr.size();
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[ind][1] <= arr[mid][0] ) {
            nextInd = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    int doJob = helper(nextInd, arr, dp) + arr[ind][2];
    int ignoreJob = helper(ind + 1, arr, dp);
    return dp[ind] = max(doJob, ignoreJob);
}

int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
    int size = profit.size();
    vector<int> dp(size, -1);
    vector<vector<int>> arr;
    for (int i = 0; i < size; i++) {
        arr.push_back({startTime[i], endTime[i], profit[i]});
    }
    sort(arr.begin(), arr.end());
    return helper(0, arr, dp);
}