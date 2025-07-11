#include <iostream>
#include <queue>
using namespace std;

class Pair {
public:
    int row, col;
    Pair(int r, int c) : row(r), col(c) {}
};

bool is_valid(int row, int col, int grid[10][10]) {
    return row >= 0 && row < 10 && col >= 0 && col < 10 && grid[row][col] == 0;
}

int main() {
    int grid[10][10] = {0};
    int start_row, start_col;
    int fill_value = 1;

    cout << "Enter starting row (0–9): ";
    cin >> start_row;
    cout << "Enter starting column (0–9): ";
    cin >> start_col;

    if (!is_valid(start_row, start_col, grid)) {
        cout << "Invalid start position." << endl;
        return 1;
    }

    queue<Pair> q;
    q.push(Pair(start_row, start_col));

    while (!q.empty()) {
        Pair current = q.front();
        q.pop();

        int r = current.row;
        int c = current.col;

        if (!is_valid(r, c, grid)) continue;

        grid[r][c] = fill_value++;
        
        q.push(Pair(r - 1, c)); // North
        q.push(Pair(r, c + 1)); // East
        q.push(Pair(r + 1, c)); // South
        q.push(Pair(r, c - 1)); // West
    }

    cout << "\nFlood-filled grid:\n";
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout.width(3);
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}