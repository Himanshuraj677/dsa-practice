// 1. N meetins in 1 room
// Sort the meetings by their end times. Then iterate through the meetings, keeping track of the end time of the last selected meeting. If the start time of the current meeting is greater than or equal to the end time of the last selected meeting, select it and update the end time.

int maxMeetings(vector<int>& start, vector<int>& end) {
    // Your code here
    int n = start.size();
    vector<pair<int, int>> meetings(n);
    for (int i = 0; i < n; ++i)
        meetings[i] = {end[i], start[i]};
    
    sort(meetings.begin(), meetings.end()); // Sort by end time

    int count = 0, lastEnd = -1;
    for (auto it : meetings) {
        int e = it.first, s = it.second;
        if (s > lastEnd) {
            ++count;
            lastEnd = e;
        }
    }
    return count;
}




// 2. Minimum Platforms
// Sort the arrival and departure times. Then iterate through the arrival and departure times, incrementing the count when an arrival occurs and decrementing it when a departure occurs. Keep track of the maximum count during the iteration.

int findPlatform(vector<int>& start, vector<int>& end) {
    // Your code here
    int size = end.size();
    sort(start.begin(), start.end());
    sort(end.begin(), end.end());
    int i = 0, j = 0, count = 0, platform = 0;
    while (i < size) {
        if (start[i] <= end[j]) {
            count++;
            platform = max(platform, count);
            i++;
        }
        else {
            count--;
            j++;
        }
    }
    return platform;
}



// 3. Job Sequencing Problem
// Sort the jobs by their profit in descending order. Then iterate through the jobs, and for each job, find the latest available time slot before its deadline. If a time slot is found, assign the job t o that time slot and update the profit. Use disjoint set union (DSU) to keep track of the available time slots.


class DisjointSet {
    private:
        vector<int> parent;
    
    public:
        DisjointSet (int n) {
            parent.resize(n + 1);
            for (int i = 0; i <= n; i++) parent[i] = i;
        }
        
        int findParent (int node) {
            if (parent[node] == node) return node;
            return parent[node] = findParent(parent[node]);
        }
        
        void merge (int node1, int node2) {
            parent[node1] = findParent(node2);
        }
};

class Solution {
  public:
    static bool comp(pair<int, int> &a, pair<int, int> &b) {
        return a.first > b.first;
    }

    vector<int> jobSequencing(vector<int> &deadline, vector<int> &profit) {
        int size = deadline.size(), slot = 1, maxProfit = 0, taskCount = 0;
        vector<pair<int, int>> v;
        for (int i = 0; i < size; i++) {
            slot = max(slot, deadline[i]);
            v.push_back({profit[i], deadline[i]});
        }

        sort(v.begin(), v.end(), comp);
        DisjointSet d = DisjointSet(slot);

        for (int i = 0; i < size; i++) {
            int maxDeadline = v[i].second;
            int par = d.findParent(maxDeadline);
            if (par != 0) {
                maxProfit += v[i].first;
                taskCount++;
                d.merge(par, par - 1);  // ✅ FIXED LINE
            }
        }

        return {taskCount, maxProfit};
    }
};



// 4. Fractional Knapsack
// Sort the items by their value-to-weight ratio in descending order. Then iterate through the items, adding them to the knapsack until it is full. If the knapsack cannot hold the entire item, add a fraction of it.

static bool comp(pair<double, pair<int, int>> &a, pair<double, pair<int, int>> &b) {
    return a.first > b.first;
}
double fractionalKnapsack(vector<int>& val, vector<int>& wt, int capacity) {
    // code here
    int size = val.size();
    double profit = 0;
    vector<pair<double, pair<int, int>>> v(size);
    for (int i = 0; i < size; i++) {
        v[i] = {1.0 * val[i] / wt[i], {val[i], wt[i]}};
    }
    sort(v.begin(), v.end(), comp);
    for (auto it: v) {
        if (capacity < it.second.second) {
            profit += (1.0 * capacity * it.first);
            break;
        }
        else {
            profit += it.second.first;
            capacity = capacity - it.second.second;
        }
    }
    return profit;
}


// 5. Minimum number of coins
// Sort the coins in descending order. Then iterate through the coins, subtracting their value from the amount until it becomes zero. Keep track of the number of coins used.

void putDenom (vector<int> &ans, int denom, int count) {
    while (count--) ans.push_back(denom);
}
vector<int> minPartition(int N)
{
    int denom[] = {2000, 500, 200, 100, 50, 20, 10, 5, 2, 1};
    int size = sizeof(denom) / 4;;
    vector<int> ans;
    for (int i = 0; i < size; i++) {
        if (N == 0) break;
        int count = N / denom[i];
        putDenom(ans, denom[i], count);
        N %= denom[i];
    }
    return ans;
}



// 6. Assign Cookies
// Sort the children and the cookies in ascending order. Then iterate through the children and the cookies, assigning the largest cookie that is greater than or equal to the child's greed factor.


int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int i = g.size() - 1, j = s.size() - 1;
    int count = 0;
    while (i >= 0 && j >= 0) {
        if (s[j] >= g[i]) {
            count++;
            j--;
        }
        i--;
    }
    return count;
}