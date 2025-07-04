// 1. Subset sum

void findSum(vector<int>& arr, vector<int>& ans, int sum, int ind) {
    if (ind == arr.size()) {
        ans.push_back(sum);
        return;
    }
    findSum(arr, ans, sum, ind + 1);
    findSum(arr, ans, sum + arr[ind], ind + 1);
}
vector<int> subsetSums(vector<int>& arr) {
    // code here
    vector<int> ans;
    findSum(arr, ans, 0, 0);
    return ans;
}


// 2. Subset II
// Sort the array and use recursion to find the subsets. 

void backtrack(int ind, vector<int>& arr, vector<int>& temp, vector<vector<int>>& ans) {
    ans.push_back(temp);
    for (int i = ind; i < arr.size(); i++) {
        if (i > ind && arr[i] == arr[i - 1]) continue; 
        temp.push_back(arr[i]);
        backtrack(i + 1, arr, temp, ans);
        temp.pop_back();
    }
}
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(), nums.end());  // 💡 Sort to group duplicates
    vector<vector<int>> ans;
    vector<int> temp;
    backtrack(0, nums, temp, ans);
    return ans;
}


// 3. Combination Sum

void combinationSum(int ind, vector<int>& candidates, vector<vector<int>> &ans, vector<int> &temp, int sum, int target) {
    if (sum == target) ans.push_back(temp);
    if (sum >= target || ind == candidates.size()) return;
    temp.push_back(candidates[ind]);
    combinationSum(ind, candidates, ans, temp, sum + candidates[ind], target);
    temp.pop_back();
    combinationSum(ind + 1, candidates, ans, temp, sum, target);
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<int> temp;
    vector<vector<int>> ans;
    combinationSum(0, candidates, ans, temp, 0, target);
    return ans;
}


// 4. Combination Sum II
// Sort the array and use recursion to find the combinations. Use a counter to keep track of the duplicates.

void helper(int ind, vector<int>& candidates, vector<int> &temp, vector<vector<int>> &ans, int sum, int &target) {
    if (sum == target) {
        ans.push_back(temp);
        return;
    }
    if (sum > target || ind == candidates.size()) return;
    for (int i = ind; i < candidates.size(); i++) {
        if (i > ind && candidates[i] == candidates[i - 1]) continue;
        temp.push_back(candidates[i]);
        helper(i + 1, candidates, temp, ans, sum + candidates[i], target);
        temp.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<int> temp;
    vector<vector<int>> ans;
    helper(0, candidates, temp, ans, 0, target);
    return ans;
}



// 5. Palindrome Partitioning
// Use recursion to find the partitions. Use a helper function to check if a string is a palindrome.
// Palindrome checking can be optimized using dp.

bool checkPalindrome (string s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) return false;
        start++;
        end--;
    }
    return true;
}
void helper(int ind, string s, vector<string> &temp, vector<vector<string>> &ans) {
    if (ind == s.size()) {
        ans.push_back(temp);
        return;
    }
    for (int i = ind; i < s.size(); i++) {
        if (checkPalindrome(s, ind, i)) {
            string str = s.substr(ind, i - ind + 1);
            temp.push_back(str);
            helper(i + 1, s, temp, ans);
            temp.pop_back();
        }
    }
}
vector<vector<string>> partition(string s) {
    vector<vector<string>> ans;
    vector<string> temp;
    helper(0, s, temp, ans);
    return ans;
}


// 6. Kth Permutation

int factorial(int num) {
    if (num == 1) return 1;
    return num * factorial(num - 1);
}
void kthPermutation(int k, string &ans, vector<int> &digit) {
    int size = digit.size();
    if (size == 1) {
        ans += to_string(digit[0]);
        return;
    }
    int fact = factorial(size);
    int div = fact / size;
    int place = k / div;
    ans += to_string(digit[place]);
    digit.erase(digit.begin() + place);
    k = k % div;
    kthPermutation(k, ans, digit);
}
string getPermutation(int n, int k) {
    string ans;
    vector<int> digit(n);
    for (int i = 1; i <= n; i++) digit[i - 1] = i;
    kthPermutation(k - 1, ans, digit);
    return ans;
}