// Given a matrix with m rows and n cols, find the no. of ways to reach 
// [m-1][n-1] from [0][0] with only right & down movements allowed.

#include<bits/stdc++.h>
using namespace std;

// using recursion. TC is 2^(m*n) & SC is (stack space)
int noOfWaysToReach_1(int rows, int cols)
{
	if(rows == 0 && cols == 0)
		return 1;
	if(rows < 0 || cols < 0)
		return 0;

	int up = noOfWaysToReach_1(rows - 1, cols);
	int left = noOfWaysToReach_1(rows, cols - 1);

	return up + left;
}


// using memoisation(top-down DP). TC is m*n & SC is m*n(dp array) + n-1 + m-1(stack space)
int noOfWaysToReach_2(int rows, int cols, vector<vector<int>>&dp)
{
	if(rows == 0 && cols == 0)
		return 1;
	if(rows < 0 || cols < 0)
		return 0;

	if(dp[rows][cols] != -1)
		return dp[rows][cols];

	int up = noOfWaysToReach_2(rows - 1, cols, dp);
	int left = noOfWaysToReach_2(rows, cols - 1, dp);

	return dp[rows][cols] = up + left;
}

// using tabulation(bottom-up DP). TC is m*n & SC is m*n(dp array).
int noOfWaysToReach_3(int rows, int cols)
{
	vector<vector<int>>dp(rows, vector<int>(cols, 0));

	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			if(i==0 && j==0)
				dp[i][j] = 1;
			else{
				int up = 0, left = 0;
				if(i > 0)
					up = dp[i-1][j];
				if(j > 0)
					left = dp[i][j-1];
				dp[i][j] = up + left;
			}
		}
	}
	return dp[rows-1][cols-1];
}

// using space-optimisation(bottom-up DP). TC is m*n & SC is constant.
int noOfWaysToReach_4(int rows, int cols)
{
	vector<int>prev(cols, 0);
	for(int i=0;i<rows;i++){
		vector<int>temp(cols, 0);
		for(int j=0;j<cols;j++){
			if(i==0 && j==0)
				temp[j] = 1;
			else{
				int up = 0, left = 0;
				if(i > 0)
					up = prev[j];
				if(j > 0)
					left = temp[j-1];
				temp[j] = up + left;
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

	cout << noOfWaysToReach_1(m-1, n-1) << endl;

	vector<vector<int>>dp(m, vector<int>(n, -1));
	cout << noOfWaysToReach_2(m-1, n-1, dp) << endl;

	cout << noOfWaysToReach_3(m, n) << endl;

	cout << noOfWaysToReach_4(m, n) << endl;


	
	return 0;
}