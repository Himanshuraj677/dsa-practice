// 1. Print all Permutation.
// It can be solve using two approaches:
// i) Use a flag array to check if the element is already used or not.
// ii) Use a vector to store the current permutation and swap the elements to generate the next permutation.

void createPermutation(int ind, vector<int> &nums, vector<vector<int>> &ans) {
    if (ind == nums.size()) {
        ans.push_back(nums);
        return;
    }
    for (int i = ind; i < nums.size(); i++) {
        swap(nums[ind], nums[i]);
        createPermutation(ind + 1, nums, ans);
        swap(nums[ind], nums[i]);
    }   
        
}

void createPermutation(vector<int> &nums, vector<int> &temp, vector<int> &used, vector<vector<int>> &ans) {
    if (temp.size() == nums.size()) {
        ans.push_back(temp);
        return;
    }
    for (int i = 0; i < nums.size(); i++) {
        if (used[i]) continue;
        used[i] = true;
        temp.push_back(nums[i]);
        createPermutation(nums, temp, used, ans);
        used[i] = false;
        temp.pop_back();
    }
}



// 3. N-Queens Problem


void helper(int row, vector<vector<string>> &ans, vector<string> &temp, vector<bool> &col, vector<bool> &diag1, vector<bool> &diag2) {
    if (row == temp.size()) {
        ans.push_back(temp);
        return;
    }
    for (int i = 0; i < temp.size(); i++) {
        if(!diag1[row + i] && !diag2[row - i + temp.size() - 1] && !col[i]) {
            temp[row][i] = 'Q';
            diag1[row + i] = diag2[row - i + temp.size() - 1] = col[i] = true;
            helper(row + 1, ans, temp, col, diag1, diag2);
            diag1[row + i] = diag2[row - i + temp.size() - 1] = col[i] = false;
            temp[row][i] = '.';
        }
    }
}
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> ans;
    vector<string> temp(n, string (n, '.'));
    vector<bool> col(n, false);
    vector<bool> diag1(2*n - 1, false);
    vector<bool> diag2(2*n - 1, false);
    helper(0, ans, temp, col, diag1, diag2);
    return ans;
}


// 4. Sudoku Solver
// We will use hash table to check if the number is already present in the row, column or 3x3 grid.
// We will use a vector of vectors to store the numbers in the row, column and 3x3 grid.

bool fillBoard(int ind, vector<vector<char>>& board, vector<vector<bool>>& rowCheck, vector<vector<bool>>& colCheck, vector<vector<bool>>& boxCheck) {
    if (ind == 81) return true;
    int row = ind / 9, col = ind % 9;
    if (board[row][col] != '.') return fillBoard(ind + 1, board, rowCheck, colCheck, boxCheck);
    for (char i = '1'; i <= '9'; i++) {
        int num = i - '1';
        int boxId = (row / 3) * 3 + (col / 3);
        if (!boxCheck[boxId][num] && !rowCheck[row][num] && !colCheck[col][num]) {
            board[row][col] = i;
            boxCheck[boxId][num] = rowCheck[row][num] = colCheck[col][num] = true;
            if (fillBoard(ind + 1, board, rowCheck, colCheck, boxCheck)) return true;
            board[row][col] = '.';
            boxCheck[boxId][num] = rowCheck[row][num] = colCheck[col][num] = false;
        }
    }
    return false;
}
void solveSudoku(vector<vector<char>>& board) {
    vector<vector<bool>> rowCheck(9, vector<bool>(9, false));
    vector<vector<bool>> colCheck(9, vector<bool>(9, false));
    vector<vector<bool>> boxCheck(9, vector<bool>(9, false));
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] != '.') {
                int boxId = (row / 3) * 3 + (col / 3);
                int num = board[row][col] - '1';
                boxCheck[boxId][num] = rowCheck[row][num] = colCheck[col][num] = true;
            }
        }
    }
    fillBoard(0, board, rowCheck, colCheck, boxCheck);
}



// 5. M Coloring Problem
// Starting from the first node, we will try to color the node with the first color and check if it is valid or not. If it is valid, we will move to the next node and repeat the process. If it is not valid, we will try the next color. If we reach the last node and all the colors are valid, we will return true.

bool checkColor(int node, vector<vector<int>> &adj, vector<int> &color) {
    for (auto it: adj[node]) {
        if (color[it] == -1 || it == node) continue;
        if (color[it] == color[node]) return false;
    }
    return true;
}
bool dfs(int node, vector<vector<int>> &adj, int m, vector<int> &color) {
    if (node == color.size()) return true;
    for (int col = 1; col <= m; col++) {
        color[node] = col;
        if (checkColor(node, adj, color)) {
            if(dfs(node + 1, adj, m, color)) return true;
        }
        color[node] = -1;
    }
    return false;
}
bool graphColoring(int v, vector<vector<int>> &edges, int m) {
    // code here
    vector<vector<int>> adj(v);
    for (auto it: edges) {
        adj[it[0]].push_back(it[1]);
        adj[it[1]].push_back(it[0]);
    }
    vector<int> color(v, -1);

    return dfs(0, adj, m, color);
}