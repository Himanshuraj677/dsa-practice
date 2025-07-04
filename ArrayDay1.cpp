// 1. Set Matrix Zeroes
// Firstly we will check if the first row and first column need to be set to zero.
// Then we will use the first row and first column to mark the rows and columns that need to be set to zero.
// Finally, we will set the rows and columns to zero based on the marks we made in the first row and first column.
// At last, we will set the first row and first column to zero if needed.
// Time complexity: O(m*n), where m is the number of rows and n is the number of columns in the matrix.
// Space complexity: O(1), we are using the input matrix to store the marks.

void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    int rowHasZero = 0, colHasZero = 0;
    for (int i = 0; i < m; i++) {
        if (matrix[i][0] == 0) rowHasZero = true;
    }
    for (int i = 0; i < n; i++) {
        if (matrix[0][i] == 0) colHasZero = true;
    }
    for (int i = 1;i < m; i++ ) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][j] == 0) {
                matrix[0][j] = 0;
                matrix[i][0] = 0;
            }
        }
    }
    for (int i = 1; i < m; i++) {
        if (matrix[i][0] == 0) {
            for (int j = 1; j < n; j++) {
                matrix[i][j] = 0;
            }
        }
    }
    for (int i = 1; i < n; i++) {
        if (matrix[0][i] == 0) {
            for (int j = 1; j < m; j++) {
                matrix[j][i] = 0;
            }
        }
    }
    if (rowHasZero) {
        for (int i = 0; i < m; i++) matrix[i][0] = 0;
    }
    if (colHasZero) {
        for (int i = 0; i < n; i++) matrix[0][i] = 0;
    }
}

// 2. Pascal's Triangle
// We will use a 2D vector to store the triangle. The first row will be [1], and each subsequent row will be generated based on the previous row.
// The first and last elements of each row will be 1, and the other elements will be the sum of the two elements above it in the previous row.
// Time complexity: O(numRows^2), where numRows is the number of rows in the triangle.
// Space complexity: O(numRows^2), we are using a 2D vector to store the triangle.

vector<vector<int>> generate(int numRows) {
    vector<vector<int>> ans;
    for (int i = 0; i < numRows; i++) {
        vector<int> temp(i + 1, 1);
        for (int j = 1; j < i; j++) {
            temp[j] = ans[i - 1][j - 1] + ans[i - 1][j];
        }
        ans.push_back(temp);
    }
return ans;
}


// 3. Next Permutation
// We will find the first decreasing element from the end of the array. 
// Then we will find the smallest element from the end that is larger than this element and swap them.
// Finally, we will reverse the elements after the swapped element to get the next permutation.
// Time complexity: O(n), where n is the length of the array.
// Space complexity: O(1), we are modifying the input array in place.

void nextPermutation(vector<int>& nums) {
    int n = nums.size();
    int i = n - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) i--;
    int j = n - 1;
    if (i >= 0) {
        while (nums[i] >= nums[j]) j--;
        swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end());
}


// 4. Kadane's Algorithm (Maximum Subarray)
// We will iterate through the array and keep track of the maximum sum ending at each index.
// We will also keep track of the overall maximum sum. If the maximum sum ending at an index is negative, we will reset it to 0.
// Time complexity: O(n), where n is the length of the array.
// Space complexity: O(1), we are using a constant amount of space.

int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    int maxm = INT_MIN, sum = 0;
    for (int i = 0; i < n; i++) {
        sum += nums[i];
        maxm = max(sum, maxm);
        if (sum < 0) sum = 0;
    }
    return maxm;
}


// 5. Dutch National Flag Algorithm (Sort 0s, 1s and 2s)
// We will use three pointers to keep track of the positions of 0s, 1s and 2s.
// For index 0 - (low -1): 0s
// For index (low) - (mid - 1): 1s
// For index (mid) - (high): 0, 1, 2
// For index (high + 1) - (n - 1): 2s
// We will iterate through the array and swap the elements based on the value of the current element.

void sortColors(vector<int>& nums) {
    int i = 0, j = 0, k = nums.size() - 1;
    while (j <= k) {
        if (nums[j] == 0) swap(nums[i++], nums[j++]);
        else if (nums[j] == 1) j++;
        else swap(nums[j], nums[k--]);
    }
}


// 6. Best Time to Buy and Sell Stock
// We will iterate through the array and keep track of the minimum price and the maximum profit.
// For each price, we will update the minimum price and calculate the profit. If the profit is greater than the maximum profit, we will update it.
// Time complexity: O(n), where n is the length of the array.
// Space complexity: O(1), we are using a constant amount of space.

int maxProfit(vector<int>& prices) {
    int buy = prices[0];
    int profit = 0;
    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] > buy) profit = max(profit, prices[i] - buy);
        if (prices[i] < buy) buy = prices[i];
    }
    return profit;
}













































int main () {

    return 0;
}