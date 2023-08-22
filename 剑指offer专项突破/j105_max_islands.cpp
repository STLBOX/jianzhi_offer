#include <iostream>
#include <queue>
#include <stack>

#define ll long long  
#define llu unsigned long long

using namespace std;

// BFS breadth first
int getAreaBFS(int grid[4][5], bool* visited, int i, int j, int& row, int& column) {
	int area = 1;
	queue<pair<int, int>> q;
	q.push(make_pair(i, j));
	visited[i , j] = true;
	while (q.size() > 0)
	{
		// 四个方向搜索
		auto p = q.front();
		q.pop();
		if ((p.first - 1 > 0)&&!visited[(p.first - 1) * column + p.second])
		{
			visited[(p.first - 1) * column+p.second] = 1;
			if (grid[p.first - 1][p.second] == 1)
			{
				q.push(make_pair(p.first - 1, p.second));
				area++;
			}
		}
		if (p.second - 1 > 0 && !visited[(p.first) * column + p.second-1])
		{
			visited[(p.first)*column+p.second-1] = 1;
			if (grid[p.first][p.second-1] == 1)
			{
				q.push(make_pair(p.first, p.second-1));
				area++;
			}
		}
		if (p.first + 1 < row && !visited[(p.first + 1) * column + p.second])
		{
			visited[(p.first+1) * column + p.second] = 1;
			if (grid[p.first+1][p.second] == 1)
			{
				q.push(make_pair(p.first+1, p.second));
				area++;
			}
		}
		if (p.second+1 < column && !visited[(p.first) * column + p.second+1])
		{
			visited[(p.first) * column + p.second + 1] = 1;
			if (grid[p.first][p.second + 1] == 1)
			{
				q.push(make_pair(p.first, p.second+1));
				area++;
			}
		}
	}
	return area;
}

int getAreaDFS(int grid[4][5], bool* visited, int i, int j, int& row, int& column) {
	stack<pair<int, int>> s;
	s.push(make_pair(i,j));
	int dirs[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };
	int area = 0;
	while (!s.empty()) {
		pair<int, int> p = s.top();
		s.pop();
		visited[p.first * column + p.second] = 1;
		area++;
		for (int n = 0; n< 4; n++)
		{
			int x = dirs[n][0] + p.first;
			int y = dirs[n][1] + p.second;
			if (x >= 0 && x < row && y >= 0 && y <= column && grid[x][y] == 1 && !visited[x * column + y])
			{
				s.push(make_pair(x, y));
				visited[x * column + y] = 1;
			}
		}
	}

	return area;
}

void getAreaRCS(int grid[4][5], bool* visited, int i, int j, int& row, int& column, int& area) {
	if (visited[i * column + j]) return;
	visited[i * column + j] = true;
	if (grid[i][j] == 0) return;
	else
	{
		area++;
		int dirs[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };
		for (int n = 0; n < 4; n++)
		{
			int x = dirs[n][0] + i;
			int y = dirs[n][1] + j;
			if (x >= 0 && x < row && y >= 0 && y <= column)
			{
				getAreaRCS(grid, visited, x, y, row, column, area);
			}
		}
	}
	return;
}

int getAreaRCS2(int grid[4][5], bool* visited, int i, int j, int& row, int& column) {
	int area = 1;
	if (visited[i * column + j]) return 0;
	visited[i * column + j] = true;
	if (grid[i][j] == 0) return 0;
	else
	{
		int dirs[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };
		for (int n = 0; n < 4; n++)
		{
			int x = dirs[n][0] + i;
			int y = dirs[n][1] + j;
			if (x >= 0 && x < row && y >= 0 && y <= column)
			{
				area += getAreaRCS2(grid, visited, x, y, row, column);
			}
		}
		return area;
	}
}

int maxArea(int grid[4][5], int& row, int& column)
{
	// bool(*visited)[5] = new bool[row][5];
	bool visited[20] = {false};

	int maxArea = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (grid[i][j] == 1 && !visited[i * column + j]) // 新的岛屿
			{
				int area = getAreaRCS2(grid, visited, i, j, row, column);
				maxArea = max(area, maxArea);
			}
		}
	}
	return maxArea;
}

int main() {
	int a[4][5] = { 1, 1, 0, 0, 1,\
					1, 1, 1, 1, 0,\
					1, 1, 0, 1, 0,\
					0, 0, 1, 0, 0 };
	int lines = sizeof(a) / sizeof(a[0][0]);
	int row = sizeof(a) / sizeof(a[0]);
	int column = lines / row;
	int area = maxArea(a, row, column);
	cout << area;
	return 0;
}