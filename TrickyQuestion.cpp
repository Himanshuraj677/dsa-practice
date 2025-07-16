// 1. Find the Maximum Length of Valid Subsequence I
// This question is bit tricky. We can earlier think to solve it using dp and we can even solve it. But it doesn't follow the required time and memory constraint. Even after doing tabulation approach we can't optimized to pass test case.
// So we notice some pattern. To get same remainder there is 3 possibilities.
// a) All numbers are even
// b) All numbers are odds
// c) There is alternate number i.e. one is even another is odd.


int maximumLength(vector<int>& nums) {
    int countEven = 0, countOdd = 0, countAlternate = 0;
    int parity = nums[0] % 2;
    for (auto num: nums) {
        if (num % 2) countEven++;
        else countOdd++;
        if (num % 2 == parity) {
            countAlternate++;
            parity = 1 - parity;
        }
    }
    
    return max({countEven, countOdd, countAlternate});
}