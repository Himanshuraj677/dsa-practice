// 1. Find nth Root of M
// We will use binary search to find the nth root of m. We will use a while loop to find the mid value. We will check if the mid value is equal to m. If it is, we will return the mid value. If it is less than m, we will set the low value to mid + 1. If it is greater than m, we will set the high value to mid - 1. Finally, we will return -1 if the nth root is not found.


int findPower(int base, int pwr) {
    int ans = 1;
    for (int i = 1; i <= pwr; i++) ans *= base;
    return ans;
}
int nthRoot(int n, int m) {
    // Code here.
    int low = 1, high = m;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        // cout << mid << endl;
        int res = findPower(mid, n);
        if (res == m) return mid;
        if (res < m) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}


// 2. Matrix Median
// We will use binary search to find the median of the matrix. We will first find the minimum and maximum values in the matrix. Then we will use binary search to find the median. We will count the number of elements less than or equal to mid. If the count is less than desired, we will set low to mid + 1. If it is greater than desired, we will set high to mid - 1. Finally, we will return low as the median.



int countLess(vector<int> &matrix, int key) {
    int i = 0, j = matrix.size() - 1, ans = 0;
    while (i <= j) {
        int mid = (i + j) / 2;
        if (matrix[mid] <= key) {
            i = mid + 1;
        }
        else {
            j = mid - 1;
        }
    }
    return i;
}

int helper(vector<vector<int>> &matrix, int key) {
    int count = 0, row = matrix.size();
    for (int i = 0; i < row; i++) {
        count += countLess(matrix[i], key);
    }
    return count;
}

int getMedian(vector<vector<int>> &matrix)
{
    // Write your code here.
    int row = matrix.size(), col = matrix[0].size();
    int desired = ((row * col) / 2) + 1;
    int low = INT_MAX, high = INT_MIN;
    for (int i = 0; i < row; i++) {
        low = min(low, matrix[i][0]);
        high = max(high, matrix[i][col - 1]);
    }
    int ans = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int count = helper(matrix, mid);
        if (count < desired) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return low;
}


// 3. Single Element in a Sorted Array
// We will use binary search to find the single element in the sorted array. We will check if the mid index is even or odd. If it is even, we will check if the mid element is equal to the next element. If it is, we will set low to mid + 1. If it is not, we will set high to mid - 1. If the mid index is odd, we will check if the mid element is equal to the previous element. If it is, we will set low to mid + 1. If it is not, we will set high to mid - 1. Finally, we will return nums[low].


int singleNonDuplicate(vector<int>& nums) {
    int low = 0, high = nums.size() - 2;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == nums[mid ^ 1]) {
            cout << low;
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return nums[low];
}


// 4. Search in Rotated Sorted Array


int search(vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] >= nums[low]) {
            if (target >= nums[low] && target < nums[mid]) {
                high = mid - 1;
            }
            else low = mid + 1;
        }
        else {
            if (target > nums[mid] && target <= nums[high]) {
                low = mid + 1;
            }
            else high = mid - 1;
        }
    }
    return -1;
}

// 5. Median of two sorted Arrays

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    if (m > n) return findMedianSortedArrays(nums2, nums1);
    int totalElement = m + n;
    int low = 0, high = m;
    while (low <= high) {
        int cut1 = (low + high) / 2;
        int cut2 = (m + n + 1) / 2 - cut1;
        int left1 = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1];
        int left2 = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1];
        int right1 = (cut1 == m) ? INT_MAX : nums1[cut1];
        int right2 = (cut2 == n) ? INT_MAX : nums2[cut2];
        if (left1 <= right2 && left2 <= right1) {
            if ((m + n) % 2 == 0) return (max(left1, left2) + min(right1, right2)) / 2.0;
            else return max(left1, left2);
        }
        else {
            if (left1 > right2) high = cut1 - 1;
            else low = cut1 + 1;
        }
    }
    return 0.0;
}


// 6. Kth Smallest Element in a Sorted array

// It is similar to the median of two sorted arrays problem.

int kthElement(vector<int>& a, vector<int>& b, int k) {
    // code here
    int m = a.size(), n = b.size();
    if (m > n) return kthElement(b, a, k);
    int low = max(0, k - n);
    int high = min(k, m);
    while (low <= high) {
        int cut1 = (low + high) / 2;
        int cut2 = k - cut1;
        int left1 = (cut1 == 0) ? INT_MIN : a[cut1 - 1];
        int left2 = (cut2 == 0) ? INT_MIN : b[cut2 - 1];
        int right1 = (cut1 == m) ? INT_MAX : a[cut1];
        int right2 = (cut2 == n) ? INT_MAX : b[cut2];
        if (left1 <= right2 && left2 <= right1) return max(left1, left2);
        else {
            if (left1 > right2) {
                high = cut1 - 1;
            }
            else {
                low = cut1 + 1;
            }
        }
    }
    return 0;
}


// 7. Allocate Minimum pages
// We use binary search on the answer space — ranging from the largest book (minimum possible max) to the sum of all pages (maximum possible max). For each mid-value, we greedily check if books can be split among ≤ k students without exceeding mid pages per student. If possible, we try a smaller value; otherwise, we increase it. This works because the condition is monotonic — if a value works, all larger values will too — allowing us to find the minimum feasible maximum efficiently.

int findPages(vector<int> &arr, int k) {
    // code here
    if (arr.size() < k) return -1;
    int low = INT_MIN, high = 0;
    for (auto it: arr) {
        low = max(low, it);
        high += it;
    }
    
    int mid = 0;
    while (low <= high) {
        mid = low + (high - low) / 2;
        int i = 0, j = 1, sum = 0;
        while (i != arr.size()) {
            sum += arr[i];
            if (sum > mid) {
                sum = arr[i];
                j++;
            }
            i++;
        }
        if (j <= k) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return low;
}


// 8. Aggressive Cows
// To solve the Aggressive Cows problem, we aim to maximize the minimum distance between any two cows placed in sorted stalls. This is a classic binary search on answer problem. We first sort the stall positions and define our search space between the smallest adjacent difference (as the lower bound) and the maximum possible distance (between the first and last stall). For each mid-distance guess, we greedily place cows in stalls, ensuring each is at least mid units apart. If we can place all k cows this way, the distance is feasible, and we try for a larger value; otherwise, we reduce the range. The goal is to return the largest minimum distance that still allows all cows to be placed.


    int aggressiveCows(vector<int> &stalls, int k) {

        // Write your code here
        sort(stalls.begin(), stalls.end());
        int size = stalls.size();
        int low = INT_MAX, high = stalls[size - 1] - stalls[0];
        for (int i = 1; i < size; i++) low = min(low, stalls[i] - stalls[i - 1]);
        if (k == size) return low;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int count = 1;
            int earlier = 0;
            for (int i = 1; i < size; i++) {
                if (count == k) break;
                if (stalls[i] - stalls[earlier] >= mid) {
                    earlier = i;
                    count++;
                }
            }
            if (count == k) low = mid + 1;
            else high = mid - 1;
        }
        return high;
    }