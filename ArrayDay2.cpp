// 1. Rotate Image
// We first transpose the matrix, then reverse each row to get the rotated image.
// Time complexity: O(n^2), where n is the length of the matrix.
// Space complexity: O(1), we are modifying the matrix in place.

void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    // Transpose of a Matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }

    // Reverse The Matrix
    int jTh = (n - 1) / 2;
    for (int i = 0; i < n; i++) {
        int j = 0, k = n - 1;
        while (j < k) {
            swap(matrix[i][j++], matrix[i][k--]);
        }
    }
}


// 2. Merege Intervals
// We will sort the intervals based on the start time. Then we will iterate through the intervals and merge them if they overlap.
// Time complexity: O(n log n), where n is the number of intervals. We are sorting the intervals first.
// Space complexity: O(n), we are using a vector to store the merged intervals.

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), comparator);
    vector<vector<int>> ans;
    ans.push_back(intervals[0]);
    for (int i = 1; i < intervals.size(); i++) {
        int u = intervals[i][0], v = intervals[i][1];
        if (u <= ans.back()[1]) {
            ans.back()[1] = max(v, ans.back()[1]);
        }
        else {
            ans.push_back({u, v});
        }
    }
    return ans;
}


// 3.Merge Sorted Array
// We will use two pointers to iterate through the two arrays. We will compare the elements and insert the larger one into the first array.
// Finally, we will copy the remaining elements from the second array to the first array.
// Time complexity: O(m + n), where m and n are the lengths of the two arrays.
// Space complexity: O(1), we are modifying the first array in place.
// Note: The first array has enough space to hold the elements of the second array.

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) nums1[k] = nums1[i--];
        else nums1[k] = nums2[j--];
        k--;
    }
    while (j >= 0) nums1[k--] = nums2[j--];
}


// 4. Repeated Number without using extra space
// We will use floyd's cycle detection algorithm to find the repeated number.
// We will use two pointers, slow and fast. The slow pointer will move one step at a time, and the fast pointer will move two steps at a time.
// When they meet, we will reset the fast pointer to the start of the array and move both pointers one step at a time until they meet again.
// Time complexity: O(n), where n is the length of the array.
// Space complexity: O(1), we are using a constant amount of space.

int findDuplicate(vector<int>& nums) {
    int slow = nums[0];
    int fast = nums[0];
    while (true) {
        slow = nums[slow];
        fast = nums[nums[fast]];
        if (slow == fast) break;
    }
    fast = nums[0];
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;
}



// 5. Repeat and Missing Number
// We cam solve using 4 methods:
// 1. Using XOR
// 2. Using Hashing
// 3. Using Sorting
// 4. Using Sum of N numbers


vector<int> Solution::repeatedNumber(const vector<int> &A) {
    int n = A.size();
    long long rdm = 0, sqDiff = 0;
    for (int i = 0; i < n; i++) {
        long long num = i + 1;
        rdm += (long long)A[i] - (num);
        sqDiff += (long long)A[i] * A[i] - (long long)num * num;
    }
    long long rSumM = sqDiff / rdm;
    int r = (int) (rdm + rSumM) / 2;
    int m = r - rdm;
    return {r, m};
}

pair<int,int> missingAndRepeating(vector<int> &arr, int n)
{
	// Write your code here 
	int xorVal = 0;
	for (int i = 0; i < n; i++) {
		xorVal = xorVal ^ arr[i];
		xorVal = xorVal ^ (i + 1);
	}

	int bitNo = 0;
	while ((xorVal & (1 << bitNo)) == 0) {
		bitNo++;
	}

	int group1 = 0, group2 = 0;
	int temp = 1 << bitNo;
	for (int i = 0; i < n; i++) {
		if (arr[i] & temp) {
			group1 = group1 ^ arr[i];
		}
		else group2 = group2 ^ arr[i];
		if ((i + 1) & temp) {
			group1 = group1 ^ (i + 1);
		}
		else group2 =group2 ^ (i + 1);
	}
	int count = 0;
	for (auto it: arr) {
		if (it == group1) count++;
	}
	if (count == 0) return {group1, group2};
	return {group2, group1};
	
}


// 6. InPlace Merge Sort
// We will use the merge sort algorithm to sort the array. We will use a helper function to merge the two halves of the array.
// Time complexity: O(n log n), where n is the length of the array.
// Space complexity: O(n), we are using a vector to store the merged array.

void inPlaceMerged(vector<int> &arr, int low, int mid, int high) {
    int i = mid, j = mid + 1;
    while (i >= low && j <= high) {
        if (arr[i] > arr[j]) swap(arr[i--], arr[j++]);
        else break;
    }
    sort(arr.begin() + low, arr.begin() + mid + 1);
    sort(arr.begin() + mid + 1, arr.begin() + high + 1);
}

void inPlaceMerged(vector<int> &arr, int low, int mid, int high) {
    int gap = (high - low + 2) / 2;
    while (gap > 0) {
        int i = low, j = low + gap;
        while (j <= high) {
            if (arr[i] > arr[j]) swap(arr[i], arr[j]);
            i++;
            j++;
        }
        gap = (gap == 1) ? 0 : ((gap + 1) / 2);
    }
}

void mergeArray(vector<int> &arr, int low, int high) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;
    mergeArray(arr, low, mid);
    mergeArray(arr, mid + 1, high);
    inPlaceMerged(arr, low, mid, high);
}

// 7. Count Inversions
// We will use the merge sort algorithm to count the number of inversions in the array. We will use a helper function to merge the two halves of the array and count the inversions while merging.
// Time complexity: O(n log n), where n is the length of the array.
// Space complexity: O(n), we are using a vector to store the merged array.


long long mergeSort (long long *arr, int low, int high) {
    long long cnt = 0;
    if (low >= high) return cnt;
    
    int mid = low + (high - low) / 2;
    cnt += mergeSort(arr, low, mid);
    cnt += mergeSort(arr, mid + 1,  high);
    cnt += mergeArray(arr, low, mid, high);
    return cnt; 

}

