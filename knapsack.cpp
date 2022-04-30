// Given an integer n, two arrays price and weights of size n and the capacity of the
// bag. You have to find out maximum price you can take by taking items such that 
// weight is not exceeding the capacity of the bag. 

#include<bits/stdc++.h>
using namespace std;

// using simple recursion. TC is 2^n and SC is n (stack space).
int solveKnapsack_1(int n, int capacity, vector<int> weight, vector<int> price)
{
	if(n == 0 || capacity == 0)
		return 0;

	int include = -1e9;
	if(capacity >= weight[n-1])
		include = price[n-1] + solveKnapsack_1(n-1, capacity-weight[n-1], weight, price);
	int exclude = solveKnapsack_1(n-1, capacity, weight, price);
	return max(include, exclude);
}

// using memoisation(top-down DP). TC is 2^n and SC is (stack space) + (dp array)
int solveKnapsack_2(int n, int capacity, vector<int> weight, vector<int> price, vector<vector<int>>&dp)
{
	if(n == 0 || capacity == 0)
		return 0;

	if(dp[n][capacity] != -1)
		return dp[n][capacity];

	int include = -1e9;
	if(capacity >= weight[n-1])
		include = price[n-1] + solveKnapsack_2(n-1, capacity-weight[n-1], weight, price, dp);
	int exclude = solveKnapsack_2(n-1, capacity, weight, price, dp);
	return dp[n][capacity] = max(include, exclude);
}
// using tabulation(bottom-up DP). TC is n*capacity and SC is (dp array)
int solveKnapsack_3(int n, int capacity, vector<int> weight, vector<int> price)
{
	vector<vector<int>>dp(n+1, vector<int>(capacity+1, 0));

	for(int i=1;i<=n;i++){
		for(int j=1;j<=capacity;j++){
			int include = -1e9;
			if(j >= weight[i-1])
				include = price[i-1] + dp[i-1][j-weight[i-1]];
			int exclude = dp[i-1][j];
			dp[i][j] =  max(include, exclude);
		}
	}
	return dp[n][capacity];
}

// using space-optimisation(bottom-up DP). TC is n*capacity and SC is capacity vector.
int solveKnapsack_4(int n, int capacity, vector<int> weight, vector<int> price)
{
	vector<int>prev(capacity+1, 0);

	for(int i=1;i<=n;i++){
		vector<int>temp(capacity+1, 0);
		for(int j=1;j<=capacity;j++){
			int include = -1e9;
			if(j >= weight[i-1])
				include = price[i-1] + prev[j-weight[i-1]];
			int exclude = prev[j];
			temp[j] =  max(include, exclude);
		}
		prev = temp;
	}
	return prev[capacity];
}
int main(){

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, capacity;
	cin >> n >> capacity;

	vector<int>price(n), weight(n);

	for(int i=0;i<n;i++){
		cin >> weight[i];
	}

	for(int i=0;i<n;i++){
		cin >> price[i];
	}

	cout << solveKnapsack_1(n, capacity, weight, price) << endl;

	vector<vector<int>>dp(n+1, vector<int>(capacity+1, -1));
	cout << solveKnapsack_2(n, capacity, weight, price, dp) << endl;

	cout << solveKnapsack_3(n, capacity, weight, price) << endl;

	cout << solveKnapsack_4(n, capacity, weight, price) << endl;
	
	return 0;
}