// 1. Rotate Linked List
// Firstly find the length of the linked list. Then find the kth node from the end of the linked list. Then reverse the linked list from the kth node to the end of the linked list. Finally reverse the linked list from the head to the kth node and then connect both parts.

ListNode* rotateRight(ListNode* head, int k) {
    if (head == NULL || k == 0) return head;
    int count = 0;
    ListNode *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp -> next;
    }
    k %= count;
    if (k == 0) return head;
    count = 0;
    ListNode *slow = head, *fast = head;
    while (count != k) {
        count++;
        fast = fast -> next; 
    }
    while (fast -> next != NULL) {
        slow = slow -> next;
        fast = fast -> next;
    }
    ListNode *next = slow -> next;
    slow -> next = NULL;
    fast -> next = head;
    return next;
}


// 2. Clone a LL with random and next pointer
// Create a new node for each node in the original linked list and insert it after the original node. Then copy the random pointer of the original node to the new node. Finally, separate the two linked lists.


Node* copyRandomList(Node* head) {
    Node *temp = head;
    while (temp != NULL) {
        Node *newNode = new Node(temp -> val);
        newNode -> next = temp -> next;
        temp -> next = newNode;
        temp = temp -> next -> next;
    }
    temp = head;
    while (temp != NULL) {
        Node *from = temp -> next;
        Node *to = NULL;
        if (temp -> random != NULL) to = temp -> random -> next;
        from -> random = to;
        temp = temp -> next -> next;
    }       
    Node *dummy1 = new Node(-1);
    temp = head;
    Node *temp1 = dummy1;
    while (temp != NULL) {
        Node *copy = temp -> next;
        temp -> next = copy -> next;
        temp1 -> next = copy;
        temp1 = temp1 -> next;
        temp = temp -> next;
    }
    return dummy1 -> next;
}


// 3. Trapping Rainwater
// Use two pointers to find the left and right boundaries of the water. 

int trap(vector<int>& height) {
    int water = 0;
    int left = 0, right = height.size() - 1;
    int leftMax = 0, rightMax = 0;
    while (left <= right) {
        if (height[left] <= height[right]) {
            if (height[left] > leftMax) leftMax = height[left];
            else {
                water += (leftMax - height[left]);
            }
            left++;
        }
        else {
            if (height[right] > rightMax) rightMax = height[right];
            else {
                water += (rightMax - height[right]);
            }
            right--;
        }
    }
    return water;
}


// 3. Remove duplicates from sorted arrays
// Use two pointers to find the unique elements in the array.

int removeDuplicates(vector<int>& nums) {
    int size = nums.size(), lastUniqueIndex = 0;
    if (size == 0) return 0;
    for (int i = 1; i < size; i++) {
        if (nums[i] != nums[lastUniqueIndex]) nums[++lastUniqueIndex] = nums[i];
    }
    return (1 + lastUniqueIndex);
}


// 4. Remove duplicates from sortey arrays II
// Use two pointers to find the unique elements in the array. We can use a counter to keep track of the number of duplicates.


int removeDuplicates(vector<int>& nums) {
    int size = nums.size(), lastUniqueIndex = 1;
    if (size <= 2) return size;
    for (int i = 2; i < size; i++) {
        if (nums[i] != nums[lastUniqueIndex - 1]) nums[++lastUniqueIndex] = nums[i];
    }
    return (1 + lastUniqueIndex);
}


// 5. Rate in a maze
// we visit the cell and mark it as visited. Then we check for all the possible moves. If the move is valid, we make the move and call the function recursively. After that, we backtrack and unmark the cell as visited. We also remove the last character from the path. Finally, we return the answer.


void helper(int i, int j, vector<vector<int>>& maze, vector<string> &ans, string &path) {
    int row = maze.size() - 1, col = maze[0].size() - 1;
    if (i == row && j == col) {
        ans.push_back(path);
        return;
    };
    int dir[4][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
    char move[4] = { 'D', 'L', 'R', 'U'};
    for (int ind = 0; ind < 4; ind++) {
        int x = dir[ind][0] + i, y = dir[ind][1] + j;
        if (x >= 0 && x <= row && y >= 0 && y <= col && maze[x][y] == 1) {
            maze[x][y] = 0;
            path.push_back(move[ind]);
            helper(x, y, maze, ans, path);
            path.pop_back();
            maze[x][y] = 1;
        }
    }
}
vector<string> ratInMaze(vector<vector<int>>& maze) {
    // code here
    vector<string> ans;
    string path;
    if (maze[0][0] == 1) {
        maze[0][0] = 0;
        helper(0, 0, maze, ans, path);
    }
    return ans;
}



// 6. Word Break II
// We will store the words in a hash set. Then we will use a recursive function to find the words in the string. We will use a string to store the words. We will also use a vector to store the final result. We will use a for loop to iterate through the string and check if the word is present in the hash set. If it is present, we will call the function recursively and pass the next index of the string. Finally, we will return the result.
// Note: It can be optimized using memoization. We can use a map to store the result of the function for each index. If the result is already present in the map, we can return it directly. This will reduce the time complexity from O(2^n) to O(n^2).



void helper (int start, string &s, unordered_set<string> &hashDict, vector<string> &ans, string &wordBreak) {
    if (start == s.size()) {
        string result = wordBreak;
        result.pop_back();
        ans.push_back(result);
        return;
    }
    for (int i = start; i < s.size(); i++) {
        string word = s.substr(start, i - start + 1);
        if (hashDict.find(word) != hashDict.end()) {
            int prevSize = wordBreak.size();
            wordBreak += (word + " ");
            helper(i + 1, s, hashDict, ans, wordBreak);
            wordBreak.erase(prevSize);
        }
    }
}
vector<string> wordBreak(vector<string>& dict, string& s) {
    // code here
    unordered_set<string> hashDict(dict.begin(), dict.end());
    vector<string> ans;
    string wordBreak;
    helper(0, s, hashDict, ans, wordBreak);
    return ans;
}

