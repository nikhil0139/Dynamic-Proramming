// Given an array of n integers of profit of wines bottle, you can sell either 
// left most bottle or rightmost bottle in each year and gain a profit according
// to array. In every year, profit of bottle gets multiplied by the year. 
// Find maximum Profit.

#include<bits/stdc++.h>
using namespace std;

// using simple recursion
int maxProfit_1(vector<int>arr, int L, int R, int yr)
{
	if(L > R)
		return 0;

	int left = yr * arr[L] + maxProfit_1(arr, L+1, R, yr+1);
	int right = yr * arr[R] + maxProfit_1(arr, L, R-1, yr+1);

	return max(left, right);
}

// using memoisation(top-down DP)
int maxProfit_2(vector<int>arr, int L, int R, int yr, vector<vector<int>>dp)
{
	if(L > R)
		return 0;

	if(dp[L][R] != -1)
		return dp[L][R];

	int left = yr * arr[L] + maxProfit_2(arr, L+1, R, yr+1, dp);
	int right = yr * arr[R] + maxProfit_2(arr, L, R-1, yr+1, dp);

	return dp[L][R] = max(left, right);
}

// using tabulation(bottom-up DP)
int maxProfit_3(vector<int>arr)
{
	int n = arr.size();
	vector<vector<int>>dp(n+1, vector<int>(n+1, 0));

	for(int i=0;i<n;i++){
		dp[i][i] = arr[i] * n;
	}

	for(int i=1;i<n;i++){
		int x = 0, y = i;
		while(x < n && y < n){
			int yr = n - (y - x);
			int left = yr * arr[x] + dp[x+1][y];
			int right = yr * arr[y] + dp[x][y-1];
			dp[x][y] = max(left, right);
			x++;
			y++;
		}
	}
	return dp[0][n-1];
}

// using space-optimisation(bottom-up DP)
int maxProfit_4(vector<int>arr)
{
	int n = arr.size();
	vector<int>prev(n+1, 0);

	for(int i=0;i<n;i++){
		prev[i] = arr[i] * n;
	}

	for(int i=1;i<n;i++){
		vector<int>temp(n+1, 0);
		int x = 0, y = i;
		while(x < n && y < n){
			int yr = n - (y - x);
			int left = yr * arr[x] + prev[y];
			int right = yr * arr[y] + prev[y-1];
			temp[y] = max(left, right);
			x++;
			y++;
		}
		prev= temp;
	}
	return prev[n-1];
}

int main(){

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n;
	cin >> n;

	vector<int>arr(n);

	for(int i=0;i<n;i++){
		cin >> arr[i];
	}

	cout << maxProfit_1(arr,0, n-1, 1) << endl;

	vector<vector<int>>dp(n+1, vector<int>(n+1, -1));
	cout << maxProfit_2(arr,0, n-1, 1, dp) << endl;

	cout << maxProfit_3(arr) << endl;

	cout << maxProfit_4(arr) << endl;


	
	return 0;
}