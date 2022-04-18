// Given an array of length n, find the maximum sum of the subsequece in which
// no two elements are adjacent. 

#include<iostream>
#include <vector>
using namespace std;

// using simple recursion (try every  possibility). TC is 2^n & SC is n(stack space)
int sum_no_adjacent_1(int n, vector<int>v)
{
	if(n < 0)
		return 0;

	if(n == 0)
		return v[0];

	int take = v[n] + sum_no_adjacent_1(n-2, v);
	int doNotTake = 0 + sum_no_adjacent_1(n-1, v);

	return max(take, doNotTake);
}

// using memoisation (top-down DP). TC is n & SC is n(stack space) + n(dp array)
int sum_no_adjacent_2(int n, vector<int>v, vector<int>&dp)
{
	if(n < 0)
		return 0;

	if(n == 0)
		return v[0];

	if(dp[n] != -1)
		return dp[n];

	int take = v[n] + sum_no_adjacent_1(n-2, v);
	int doNotTake = 0 + sum_no_adjacent_1(n-1, v);

	return dp[n] = max(take, doNotTake);
}

// using tabulation (bottom-up DP). TC is n & SC is n(dp array).
int sum_no_adjacent_3(int n, vector<int>v)
{
	vector<int>dp(n);
	dp[0] = v[0];

	for(int i=1;i<=n;i++)
	{
		int take = v[i];
		if(i >= 2)
			take += dp[i-2];
		int doNotTake = 0 + dp[i-1];
		dp[i] = max(take, doNotTake);
	}
	return dp[n];
}

// using space-optimised tabulation (bottom-up DP). TC is n & SC is constant
int sum_no_adjacent_4(int n, vector<int>v)
{
	int a = 0, b = v[0];

	for(int i=1;i<=n;i++)
	{
		int take = v[i];
		if(i >= 2)
			take += a;
		int doNotTake = 0 + b;
		a = b;
		b = max(take, doNotTake);
	}
	return b;
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

	cout << sum_no_adjacent_1(n-1, arr) << endl;

	vector<int>dp(n, -1);
	cout << sum_no_adjacent_2(n-1, arr, dp) << endl;

	cout << sum_no_adjacent_3(n-1, arr) << endl;

	cout << sum_no_adjacent_4(n-1, arr) << endl;



	
	return 0;
}