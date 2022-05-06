// Given two arrays of n weights and corresponding prices, also given bag capacity,
// find out maximum price you can gain if you can take any item any no. of times.


#include<bits/stdc++.h>
using namespace std;

// using simple recursion. TC is exponential and SC is capacity(stack space).
int maxProfit_1(int n, int capacity, vector<int>weights, vector<int>price)
{
	if(n==0){
		return (capacity / weights[0]) * price[0];
	}

	int notTake = maxProfit_1(n-1, capacity, weights, price), take = 0;
	if(capacity >= weights[n])
		take = price[n] + maxProfit_1(n, capacity-weights[n], weights, price);
	return max(notTake, take);
}

// using memoisation(top-down DP). TC is n*capacity and SC is capacity(stack space) + dp array.
int maxProfit_2(int n, int capacity, vector<int>weights, vector<int>price, vector<vector<int>>&dp)
{
	if(n==0){
		return (capacity / weights[0]) * price[0];
	}

	if(dp[n][capacity] != -1)
		return dp[n][capacity];

	int notTake = maxProfit_2(n-1, capacity, weights, price, dp), take = 0;
	if(capacity >= weights[n])
		take = price[n] + maxProfit_2(n, capacity-weights[n], weights, price, dp);
	return dp[n][capacity] = max(notTake, take);
}

// using tabulation(bottom-up DP). TC is n*capacity and SC is dp array.
int maxProfit_3(int n, int capacity, vector<int>weights, vector<int>price)
{
 	vector<vector<int>>dp(n, vector<int>(capacity+1, 0));

 	for(int c = 0;c<=capacity;c++){
 		dp[0][c] = (c / weights[0]) * price[0];
 	}

 	for(int i=1;i<n;i++){
 		for(int j=0;j<=capacity;j++){
 			int notTake = dp[i-1][j], take = 0;
			if(j >= weights[i])
				take = price[i] + dp[i][j-weights[i]];
			dp[i][j] = max(notTake, take);
 		}
 	}
	return dp[n-1][capacity];
}

// using space optimisation(bottom-up DP). TC is n*capacity and SC is capacity.
int maxProfit_4(int n, int capacity, vector<int>weights, vector<int>price)
{
 	vector<int>prev(capacity+1, 0);

 	for(int c = 0;c<=capacity;c++){
 		prev[c] = (c / weights[0]) * price[0];
 	}

 	for(int i=1;i<n;i++){
 		vector<int>temp(capacity+1, 0);
 		for(int j=0;j<=capacity;j++){
 			int notTake = prev[j], take = 0;
			if(j >= weights[i])
				take = price[i] + temp[j-weights[i]];
			temp[j] = max(notTake, take);
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

 	vector<int>weights(n), price(n);

 	for(int i=0;i<n;i++){
 		cin >> weights[i];
 	}

 	for(int i=0;i<n;i++){
 		cin >> price[i];
 	}

 	cout << maxProfit_1(n-1, capacity, weights, price) << endl;

 	vector<vector<int>>dp(n, vector<int>(capacity+1, -1));
 	cout << maxProfit_2(n-1, capacity, weights, price, dp) << endl;

 	cout << maxProfit_3(n, capacity, weights, price) << endl;

 	cout << maxProfit_4(n, capacity, weights, price) << endl;

 	return 0;
} 