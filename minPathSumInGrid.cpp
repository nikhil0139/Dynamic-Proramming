// Given a matrix with m rows and n cols, find the min path sum to reach 
// [m-1][n-1] from [0][0] with only right & down movements allowed.

#include<bits/stdc++.h>
using namespace std;

// using recursion. TC is 2^(m*n) & SC is (stack space)
int minSumPath_1(int rows, int cols, vector<vector<int>>mat)
{
	if(rows == 0 && cols == 0)
		return mat[rows][cols];
	if(rows < 0 || cols < 0)
		return 1e9;

	int up = mat[rows][cols] + minSumPath_1(rows - 1, cols, mat);
	int left = mat[rows][cols] + minSumPath_1(rows, cols - 1, mat);

	return min(up, left);
}


// using memoisation(top-down DP). TC is m*n & SC is m*n(dp array) + n-1 + m-1(stack space)
int minSumPath_2(int rows, int cols, vector<vector<int>>mat, vector<vector<int>>&dp)
{
	if(rows == 0 && cols == 0)
		return mat[0][0];
	if(rows < 0 || cols < 0)
		return 1e9;

	if(dp[rows][cols] != -1)
		return dp[rows][cols];

	int up = mat[rows][cols] + minSumPath_2(rows - 1, cols, mat, dp);
	int left = mat[rows][cols] + minSumPath_2(rows, cols - 1, mat, dp);

	return dp[rows][cols] = min(up, left);
}

// using tabulation(bottom-up DP). TC is m*n & SC is m*n(dp array).
int minSumPath_3(int rows, int cols, vector<vector<int>>mat)
{
	vector<vector<int>>dp(rows, vector<int>(cols, 0));

	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			if(i==0 && j==0)
				dp[i][j] = mat[i][j];
			else{
				int up = 1e9, left = 1e9;
				if(i > 0)
					up = mat[i][j] + dp[i-1][j];
				if(j > 0)
					left = mat[i][j] + dp[i][j-1];
				dp[i][j] = min(up, left);
			}
		}
	}
	return dp[rows-1][cols-1];
}

// using space-optimisation(bottom-up DP). TC is m*n & SC is constant.
int minSumPath_4(int rows, int cols, vector<vector<int>>mat)
{
	vector<int>prev(cols, 0);
	for(int i=0;i<rows;i++){
		vector<int>temp(cols, 0);
		for(int j=0;j<cols;j++){
			if(i==0 && j==0)
				temp[j] = mat[i][j];
			else{
				int up = 1e9, left = 1e9;
				if(i > 0)
					up = mat[i][j] + prev[j];
				if(j > 0)
					left = mat[i][j] + temp[j-1];
				temp[j] = min(up, left);
			}
		}
		prev = temp;
	}
	return prev[cols-1];
}

int main(){

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int m, n;
	cin >> m >> n;

	vector<vector<int>>mat(m, vector<int>(n));

	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cin >> mat[i][j];
		}
	}

	cout << minSumPath_1(m-1, n-1, mat) << endl;

	vector<vector<int>>dp(m, vector<int>(n, -1));
	cout << minSumPath_2(m-1, n-1, mat, dp) << endl;

	cout << minSumPath_3(m, n, mat) << endl;

	cout << minSumPath_4(m, n, mat) << endl;

	return 0;
}