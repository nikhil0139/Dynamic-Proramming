// Given a matrix of m * n integers, you can start from any col of first row and you have
// to reach any col of last row in the matrix with three movements allowed 
// (down, left-diagonal, right-diagonal). Find the max path sum.

#include<bits/stdc++.h>
using namespace std;

// using simple recursion. TC is 3^(m*n) and SC is (stack space).
int maxPathSum_1(int i, int j, vector<vector<int>>arr)
{
	if(j < 0 || j >= arr[0].size())
		return -1e9;

	if(i == 0)
		return arr[i][j];

	int leftDiagonal = arr[i][j] + maxPathSum_1(i-1, j-1, arr);
	int up = arr[i][j] + maxPathSum_1(i-1, j, arr);
	int rightDiagonal = arr[i][j] + maxPathSum_1(i-1, j+1, arr);
	return max(leftDiagonal, max(up, rightDiagonal));
}

// using memoisation(top-dowm DP). TC is m*n and SC is (stack space) + m*n (DP array) 
int maxPathSum_2(int i, int j, vector<vector<int>>arr, vector<vector<int>>&dp)
{
	if(j < 0 || j >= arr[0].size())
		return -1e9;

	if(i == 0)
		return arr[i][j];

	if(dp[i][j] != -1)
		return dp[i][j];

	int leftDiagonal = arr[i][j] + maxPathSum_2(i-1, j-1, arr, dp);
	int up = arr[i][j] + maxPathSum_2(i-1, j, arr, dp);
	int rightDiagonal = arr[i][j] + maxPathSum_2(i-1, j+1, arr, dp);
	return dp[i][j] = max(leftDiagonal, max(up, rightDiagonal));
}

// using tabulation(bottom-up DP). TC is m*n and SC is m*n (DP array) 
int maxPathSum_3(vector<vector<int>>arr)
{
	int m = arr.size();
	int n = arr[0].size();
	vector<vector<int>>dp(m, vector<int>(n,0));

	for(int j=0;j<n;j++){
		dp[0][j] = arr[0][j];
	}

	for(int i=1;i<m;i++){
		for(int j=0;j<n;j++){
			int up, leftDiagonal = -1e9, rightDiagonal = -1e9;
			if(j >= 1)
				leftDiagonal = arr[i][j] + dp[i-1][j-1];
			up = arr[i][j] + dp[i-1][j];
			if(j < n-1)
				rightDiagonal = arr[i][j] + dp[i-1][j+1];

			dp[i][j] = max(leftDiagonal, max(up, rightDiagonal));
		}
	}
	return *max_element(dp[m-1].begin(), dp[m-1].end());
}

// using space-optimisation(bottom-up DP). TC is m*n and SC is n (approx constant). 
int maxPathSum_4(vector<vector<int>>arr)
{
	int m = arr.size();
	int n = arr[0].size();
	vector<int>prev(n);

	for(int j=0;j<n;j++){
		prev[j] = arr[0][j];
	}

	for(int i=1;i<m;i++){
		vector<int>temp(n);
		for(int j=0;j<n;j++){
			int up, leftDiagonal = -1e9, rightDiagonal = -1e9;
			if(j >= 1)
				leftDiagonal = arr[i][j] + prev[j-1];
			up = arr[i][j] + prev[j];
			if(j < n-1)
				rightDiagonal = arr[i][j] + prev[j+1];

			temp[j] = max(leftDiagonal, max(up, rightDiagonal));
		}
		prev = temp;
	}
	return *max_element(prev.begin(), prev.end());
}


int main(){

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int m, n;
	cin >> m >> n;

	vector<vector<int>>arr(m, vector<int>(n, 0));

	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cin >> arr[i][j];
		}
	}
	// simple recursion
	int maxi_1 = -1e9;
	for(int j=0;j<n;j++)
	{
		maxi_1 = max(maxi_1, maxPathSum_1(m-1, j, arr));
	}
	cout << maxi_1 << endl;

	// memoisation
	vector<vector<int>>dp(m, vector<int>(n,-1));
	int maxi_2 = -1e9;
	for(int j=0;j<n;j++)
	{
		maxi_2 = max(maxi_2, maxPathSum_2(m-1, j, arr, dp));
	}
	cout << maxi_2 << endl;

	// tabulation
	cout << maxPathSum_3(arr) << endl;

	// space optimisation
	cout << maxPathSum_4(arr) << endl;
	
	return 0;
}