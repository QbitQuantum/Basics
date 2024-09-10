void FloodFill(int row, int col, int max_row, int max_col, char c)
{
    if (row < 0 || row >= max_row || col < 0 || col >= max_col) return;

    matrix[row][col] = c;
    is_visited[row][col] = true;

    int i, new_row, new_col;

    for (i = 0; i < 8; ++i) {
        new_row = row + dx[i];
        new_col = col + dy[i];

        if (!is_visited[new_row][new_col] && matrix[new_row][new_col] == '@')
            FloodFill(new_row, new_col, max_row, max_col, c);
    }
}