#include <iostream>
#include <queue>

using namespace std;


void minDistToZero(const int* a, int* dist, int i, int j, const int& column, const int& row) {
	if (*(a + i * column + j) == 0) return;

	int dirs[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };
	int min_dist_to_ij = INT_MAX;
	for (int d = 0; d < 4; ++d)
	{
		int x = i + dirs[d][0];
		int y = j + dirs[d][1];
		if (x >= 0 && y >= 0 && x < row && y < column) 
		{
			minDistToZero(a, dist, x, y, column, row);  // 获得周围的点的最小的距离
			if (*(dist + x * column + y) < min_dist_to_ij) min_dist_to_ij = *(dist + x * column + y);
		}
	}
	*(dist + i * column + j) = min_dist_to_ij + 1;
	return;
}

int main()
{
	int a[3][3] = { {0,0,0},{0,1,0},{1,1,1,} };
	int dist[3][3] = { 0 };
	int element_nums = sizeof(a) / sizeof(a[0][0]);
	int column = sizeof(a[0]) / sizeof(a[0][0]);
	int row = element_nums / column;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; ++j)
		{
			if (dist[i][j] > 0)  continue;
			if (a[i][j] != 0) minDistToZero(&(a[0][0]), &dist[0][0], i, j, column, row);
		}

	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; ++j)
		{
			cout << dist[i][j] << "\t";
		}
		cout << endl;
	}
	return 0;
}