// Given an array of n integers and an integer k, return true if there is a subset
// or subsequence whose sum equals to k.

#include<bits/stdc++.h>
using namespace std;

//using simple recursion. TC is 2^n and SC is n(stack space).
bool isExist_1(vector<int>arr, int target, int n)
{
	if(target == 0)
		return true;
	if(n==0)
		return arr[n] == target;

	bool notTake = isExist_1(arr, target, n-1);
	bool take = false;
	if(target >= arr[n])
		take = isExist_1(arr, target - arr[n], n-1);
	
	return notTake || take;
}

//using memoisation(top-down DP).TC is n*k and SC is n(stack space) + dp array(n*k).
bool isExist_2(vector<int>arr, int target, int n, vector<vector<int>>&dp)
{
	if(target == 0)
		return true;
	if(n==0)
		return arr[n] == target;

	if(dp[n][target] != -1)
		return dp[n][target];

	bool notTake = isExist_2(arr, target, n-1, dp);
	bool take = false;
	if(target >= arr[n])
		take = isExist_2(arr, target - arr[n], n-1, dp);
	
	return dp[n][target] = notTake || take;
}

//using tabulation(bottom-up DP). TC is n*k and SC is dp array(n*k).
bool isExist_3(vector<int>arr, int target)
{
	int n = arr.size();

	vector<vector<bool>>dp(n+1, vector<bool>(target+1, false));

	for(int i=0;i<n;i++){
		dp[i][0] = true;
	}

	if(target >= arr[0])
		dp[0][arr[0]] = true;

	for(int i=1;i<n;i++){
		for(int j=1;j<=target;j++){
			bool notTake = dp[i-1][j];
			bool take = false;
			if(j >= arr[i])
				take = dp[i-1][j - arr[i]];
			dp[i][j] = notTake || take;
		}
	}
	return dp[n-1][target];
}

//using space-optimisation(bottom-up DP). TC is n*k and SC is dp array(k).
bool isExist_4(vector<int>arr, int target)
{
	int n = arr.size();
	
	vector<bool>prev(target+1, false), temp(target+1, false);

	prev[0] = true;
	temp[0] = true;

	if(target >= arr[0])
		prev[arr[0]] = true;

	for(int i=1;i<n;i++){
		for(int j=1;j<=target;j++){
			bool notTake = prev[j];
			bool take = false;
			if(j >= arr[i])
				take = prev[j - arr[i]];
			temp[j] = notTake || take;
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
	
	cout << isExist_1(arr, target, n-1) << endl;

	vector<vector<int>>dp(n+1, vector<int>(target+1, -1));
	cout << isExist_2(arr, target, n-1, dp) << endl;

	cout << isExist_3(arr, target) << endl;

	cout << isExist_4(arr, target) << endl;

	return 0;
}