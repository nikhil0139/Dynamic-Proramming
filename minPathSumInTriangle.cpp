// Given a matrix of n rows and ith row contain i+1 elements (right-angled triangle);
// Find min path sum to reach from [0][0] to last row of the matrix.

#include<bits/stdc++.h>
using namespace std;
 
// using simple recursion. TC is 2^(n*n) and SC is (stack space).
int minPathSum_1(int i, int j, vector<vector<int>>arr)
{
	if(i==arr.size()-1)
		return arr[i][j];

	int down = arr[i][j] + minPathSum_1(i+1, j, arr);
	int diagonal = arr[i][j] + minPathSum_1(i+1, j+1, arr);
	return min(down, diagonal);
}

// using memoisation(top-down DP). TC is n * n and SC is (stack space) + n*n(DP array).
int minPathSum_2(int i, int j, vector<vector<int>>arr, vector<vector<int>>&dp)
{
	if(i==arr.size()-1)
		return arr[i][j];

	if(dp[i][j] != -1)
		return dp[i][j];

	int down = arr[i][j] + minPathSum_2(i+1, j, arr, dp);
	int diagonal = arr[i][j] + minPathSum_2(i+1, j+1, arr, dp);
	return dp[i][j] = min(down, diagonal);
}

// using tabulation(bottom-up DP). TC is n * n and SC is n*n(DP array).
int minPathSum_3(vector<vector<int>>arr)
{
	int n = arr.size();

	vector<vector<int>>dp(n, vector<int>(n, 0));
	
	for(int j=0;j<=n;j++){
		dp[n-1][j] = arr[n-1][j];
	}
	for(int i=n-2;i>=0;i--){
		for(int j=i;j>=0;j--){
			int down = arr[i][j] + dp[i+1][j];
			int diagonal = arr[i][j] + dp[i+1][j+1];
			dp[i][j] = min(down, diagonal);
		}
	}
	return dp[0][0];
}

// using space-optmisation(bottom-up). TC is n * n and SC is n(approx constant).
int minPathSum_4(vector<vector<int>>arr)
{
	int n = arr.size();
	
	vector<int>prev(n);
	
	for(int j=0;j<n;j++){
		prev[j] = arr[n-1][j];
	}
	for(int i=n-2;i>=0;i--){
		vector<int>temp(n);
		for(int j=i;j>=0;j--){
			int down = arr[i][j] + prev[j];
			int diagonal = arr[i][j] + prev[j+1];
			temp[j] = min(down, diagonal);
		}
		prev = temp;
	}
	return prev[0];
}



int main(){

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n;
	cin >> n;

	vector<vector<int>>arr(n, vector<int>(n, 0));

	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			cin >> arr[i][j];
		}
	}

	cout << minPathSum_1(0, 0, arr) << endl;
	
	vector<vector<int>>dp(n, vector<int>(n, -1));
	cout << minPathSum_2(0, 0, arr, dp) << endl;

	cout << minPathSum_3(arr) << endl;

	cout << minPathSum_4(arr) << endl;

	return 0;
}