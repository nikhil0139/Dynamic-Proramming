// Given an array of n integers and an integer k, count in how many ways the array
// can be partitioned so that the difference is k.

#include<bits/stdc++.h>
using namespace std;

//using simple recursion. TC is 2^n and SC is n(stack space).
int isExist_1(vector<int>arr, int target, int n)
{
	if(target == 0)
		return 1;
	if(n==0)
		return arr[n] == target;

	int notTake = isExist_1(arr, target, n-1);
	int take = 0;
	if(target >= arr[n])
		take = isExist_1(arr, target - arr[n], n-1);
	
	return notTake + take;
}

//using memoisation(top-down DP).TC is n*k and SC is n(stack space) + dp array(n*k).
int isExist_2(vector<int>arr, int target, int n, vector<vector<int>>&dp)
{
	if(target == 0)
		return 1;
	if(n==0)
		return arr[n] == target;

	if(dp[n][target] != -1)
		return dp[n][target];

	int notTake = isExist_2(arr, target, n-1, dp);
	int take = 0;
	if(target >= arr[n])
		take = isExist_2(arr, target - arr[n], n-1, dp);
	
	return dp[n][target] = notTake + take;
}

//using tabulation(bottom-up DP). TC is n*k and SC is dp array(n*k).
int isExist_3(vector<int>arr, int target)
{
	int n = arr.size();

	vector<vector<int>>dp(n+1, vector<int>(target+1, 0));

	for(int i=0;i<n;i++){
		dp[i][0] = 1;
	}

	if(target >= arr[0])
		dp[0][arr[0]] = 1;

	for(int i=1;i<n;i++){
		for(int j=1;j<=target;j++){
			int notTake = dp[i-1][j];
			int take = 0;
			if(j >= arr[i])
				take = dp[i-1][j - arr[i]];
			dp[i][j] = notTake + take;
		}
	}
	return dp[n-1][target];
}

//using space-optimisation(bottom-up DP). TC is n*k and SC is dp array(k).
int isExist_4(vector<int>arr, int target)
{
	int n = arr.size();
	
	vector<int>prev(target+1, 0), temp(target+1, 0);

	prev[0] = 1;
	temp[0] = 1;

	if(target >= arr[0])
		prev[arr[0]] = 1;

	for(int i=1;i<n;i++){
		for(int j=1;j<=target;j++){
			int notTake = prev[j];
			int take = 0;
			if(j >= arr[i])
				take = prev[j - arr[i]];
			temp[j] = notTake + take;
		}
		prev = temp;
	}
	return prev[target];
}

int main(){

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, diff, sum = 0;
	cin >> n >> diff;

	vector<int>arr(n);

	for(int i=0;i<n;i++){
		cin >> arr[i];
		sum += arr[i];
	}

	int target = sum-diff;

	if(sum-diff < 0 || (sum-diff) & 1)
		cout << 0 << endl;
	else{
		cout << isExist_1(arr, target/2, n-1) << endl;

		vector<vector<int>>dp(n+1, vector<int>(target+1, -1));
		cout << isExist_2(arr, target/2, n-1, dp) << endl;

		cout << isExist_3(arr, target/2) << endl;

		cout << isExist_4(arr, target/2) << endl;
	}
	
	

	return 0;
}
