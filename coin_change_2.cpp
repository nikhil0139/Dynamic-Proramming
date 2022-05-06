// Given an array of n coins and an integer target, you have to count number of 
// ways to make target if you can use any coin any number of times.


#include<bits/stdc++.h>
using namespace std;

// using simple recursion. TC is exponential and SC is target(stack space).
int noOfWays_1(vector<int>arr, int n, int target)
{
	if(n == 0)
		return target % arr[0] == 0;

	int notTake = noOfWays_1(arr, n-1, target), take = 0;
	if(target >= arr[n])
		take = noOfWays_1(arr, n, target - arr[n]);
	return notTake + take;
}

// using memoisation(top-down DP). TC is n*target and SC is target(stack space) + dp array.
int noOfWays_2(vector<int>arr, int n, int target, vector<vector<int>>&dp)
{
	if(n == 0)
		return target % arr[0] == 0;

	if(dp[n][target] != -1)
		return dp[n][target];

	int notTake = noOfWays_2(arr, n-1, target, dp), take = 0;
	if(target >= arr[n])
		take = noOfWays_2(arr, n, target - arr[n], dp);
	return dp[n][target] = notTake + take;
}

// using tabulation(bottom-up DP). TC is n*target and SC is dp array.
int noOfWays_3(vector<int>arr, int n, int target)
{
	vector<vector<int>>dp(n, vector<int>(target+1, 0));

	for(int t = 0; t <= target; t++){
		if(t%arr[0] == 0)
			dp[0][t] = 1;
	}

	for(int i=1;i<n;i++){
		for(int j=0;j<=target;j++){
			int notTake = dp[i-1][j], take = 0;
			if(j >= arr[i])
				take = dp[i][j - arr[i]];
			dp[i][j] = notTake + take;
		}
	}
	return dp[n-1][target];
}

// using space optimisation(bottom-up DP). TC is n*target and SC is target.
int noOfWays_4(vector<int>arr, int n, int target)
{
	vector<int>prev(target+1, 0);

	for(int t = 0; t <= target; t++){
		if(t%arr[0] == 0)
			prev[t] = 1;
	}

	for(int i=1;i<n;i++){
		vector<int>temp(target+1, 0);
		for(int j=0;j<=target;j++){
			int notTake = prev[j], take = 0;
			if(j >= arr[i])
				take = temp[j - arr[i]];
			temp[j] = notTake + take;
		}
		prev = temp;
	}
	return prev[target];
}


int main(){

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, target;
	cin >> n >> target;

	vector<int>arr(n);

	for(int i=0;i<n;i++){
		cin >> arr[i];
	}

	cout << noOfWays_1(arr, n-1, target) << endl;

	vector<vector<int>>dp(n, vector<int>(target+1, -1));
	cout << noOfWays_2(arr, n-1, target, dp) << endl;

	cout << noOfWays_3(arr, n, target) << endl;

	cout << noOfWays_4(arr, n, target) << endl;

	return 0;
}