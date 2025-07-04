// 1. Search in a 2D Matrix
// // We will use binary search to search for the target in the matrix. We will treat the matrix as a 1D array and apply binary search on it.
// // Time complexity: O(log(m * n)), where m is the number of rows and n is the number of columns in the matrix.
// // Space complexity: O(1), we are not using any extra space.

bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int row = matrix.size();
    int col = matrix[0].size();
    int low = 0, high = row * col - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        auto ind = findIndex(mid, col);
        if (matrix[ind.first][ind.second] == target) return true;
        else if (matrix[ind.first][ind.second] < target) low = mid + 1;
        else high = mid - 1;
    }
    return false;
}

// 2. Pow(x, n)









// 3. Majority Element
// We will use Boyer-Moore Voting Algorithm to find the majority element in the array. The algorithm works by maintaining a count of the current candidate and updating it based on the elements in the array.
// Time complexity: O(n), where n is the number of elements in the array.
// Space complexity: O(1), we are not using any extra space.

int majorityElement(vector<int>& nums) {
    int num = nums[0];
    int count = 1;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] == num) count++;
        else if (count == 0) {
            count = 1;
            num = nums[i];
        }
        else count--;
    }
    return num;    
}



// 4. Majority Element II
// we will use two counters to keep track of the two candidates and their counts. We will iterate through the array and update the candidates and their counts based on the elements in the array.
// Time complexity: O(n), where n is the number of elements in the array.
// Space complexity: O(1), we are not using any extra space.

vector<int> majorityElement(vector<int>& nums) {
    int num1 = INT_MIN, num2 = INT_MIN, count1 = 0, count2 = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        if (count1 == 0 && nums[i] != num2) {
            count1 = 1;
            num1 = nums[i];
        }
        else if (count2 == 0 && nums[i] != num1) {
            count2 = 1;
            num2 = nums[i];
        }
        else if (nums[i] == num1) count1++;
        else if (nums[i] == num2) count2++;
        else {
            count1--;
            count2--;
        }
    }
    count1 = count2 = 0;
    for (auto it: nums) {
        if (it == num1) count1++;
        else if (it == num2) count2++;
    }
    vector<int> ans;
    if (count1 > (n / 3)) ans.push_back(num1);
    if (count2 > (n / 3)) ans.push_back(num2);
    sort(ans.begin(), ans.end());
    return ans;
}



// 5. Unique Paths
// We will use dynamic dynamic programming.

int helper (int i, int j) {
    if (i == 0 && j == 0) return 1;
    if (i < 0 || j < 0) return 0;
    int left = helper(i, j - 1);
    int up = helper(i - 1, j);
    return left + up;
}
int uniquePaths(int m, int n) {
    return helper(m - 1, n - 1);
}