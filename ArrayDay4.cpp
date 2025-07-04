// 1. Two Sum
// We will use a hash map to store the indices of the elements in the array. For each element, we will check if the complement (target - element) exists in the hash map. If it does, we will return the indices of the two elements.  
// Time complexity: O(n), where n is the number of elements in the array.
// Space complexity: O(n), we are using a hash map to store the indices of the elements.

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> um;
    for (int i = 0; i < nums.size(); i++) {
        if (um.find(target - nums[i]) != um.end()) {
            ans.push_back(i);
            ans.push_back(um[target - nums[i]]);
            break;
        }
        um[nums[i]] = i;
    }
    return ans;
}



// 2. 4-Sum
// It can be solved with two complexity.
// We will use two nested loops to fix the first two elements and then use the two-pointer technique to find the other two elements.
// Time complexity: O(n^3), where n is the number of elements in the array.
// Space complexity: O(1), we are not using any extra space.
// Another method is to use a hash map to store the pairs of elements and their indices. For each pair, we will check if the complement exists in the hash map. If it does, we will return the indices of the four elements.
// Time complexity: O(n^2), where n is the number of elements in the array.
// Space complexity: O(n^2), we are using a hash map to store the pairs of elements and their indices.

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    for (int i = 0; i < nums.size(); i++) {
        if (i != 0 && nums[i] == nums[i - 1]) continue;
        for (int j = i + 1; j < nums.size(); j++) {
            if (j != i + 1 && nums[j] == nums[j - 1]) continue;
            int low = j + 1, high = nums.size() - 1;
            while (low < high) {
                long long sum = 1LL * nums[i] + nums[j] + nums[low] + nums[high];
                if (sum == target) {
                    ans.push_back({nums[i], nums[j], nums[low++], nums[high--]});
                    while (low < high && nums[low] == nums[low - 1]) low++;
                    while (low < high && nums[high] == nums[high + 1]) high--;
                }
                else if (sum < target) low++;
                else high--;
            }
        }
    }
    return ans;
}

// 3. Longest Consecutive Sequence
// We will use unordered_set to store the elements of the array. For each element, we will check if it is the start of a sequence. If it is, we will keep checking for the next elements in the sequence and update the maximum length accordingly.
// Time complexity: O(n), where n is the number of elements in the array.
// Space complexity: O(n), we are using a hash set to store the elements of the array.

int longestConsecutive(vector<int>& nums) {
    unordered_set<int> um(nums.begin(), nums.end());
    int ans = 0;
    for (auto num: um) {
        if (um.find(num - 1) == um.end()) {
            int number = num;
            int currentStreak = 1;
            while (um.find(number + 1) != um.end()) {
                number++;
                currentStreak++;
            }
            ans = max(ans, currentStreak);
        }
    }
    return ans;
}



// 4. Largest subarray with 0 sum (Prefix sum)
// We will use a hash map to store the sum of the elements and their indices. For each element, we will check if the sum exists in the hash map. If it does, we will update the maximum length accordingly.
// Time complexity: O(n), where n is the number of elements in the array.
// Space complexity: O(n), we are using a hash map to store the sum of the elements and their indices.

int maxLen(vector<int>& arr) {
    // code here
    unordered_map<int, int> um;
    int len = 0, sum = 0;
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
        if (sum == 0) len = i + 1;
        else if (um.find(sum) != um.end()) {
            int ind = um[sum];
            // cout << i << " " << ind << " " << sum << endl;
            len = max(len, i - ind);
        }
        else um[sum] = i;
    }
    return len;
}


// 5. Subarray with given xor
// We will use a hash map to store the xor of the elements and their indices. For each element, we will check if the xor exists in the hash map. If it does, we will update the maximum length accordingly.
// Time complexity: O(n), where n is the number of elements in the array.
// Space complexity: O(n), we are using a hash map to store the xor of the elements and their indices.

int Solution::solve(vector<int> &A, int B) {
    unordered_map<int, int> um;
    int sum = 0, len = 0;
    um[0]++;  // for the case when xor is equal to B
    for (auto it: A) {
        sum ^= it;
        len += um[sum ^ B];
        um[sum]++;
    }
    return len;
}



// 6. Longest Substring without Repeating Characters
// We will use a hash map to store the last index of each character. For each character, we will check if it exists in the hash map. If it does, we will update the start index accordingly. We will also update the maximum length accordingly.
// Time complexity: O(n), where n is the number of characters in the string.
// Space complexity: O(n), we are using a hash map to store the last index of each character.

int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> um;
    int len = 0, left = 0, right = 0;
    while (right < s.size()) {
        if (um.find(s[right]) != um.end())  {
            left = max(left, um[s[right]] + 1);
        }
        len = max(len, right - left + 1);
        um[s[right]] = right;
        right++;
    }
    return len;
}

