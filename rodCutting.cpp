// Given an array of n prices and a rod of length n, you have to break rod into lengths
// and sell in the market to get maximum price out of it. 


#include<bits/stdc++.h>
using namespace std;

// using simple recursion. TC is exponential and SC is N(stack space).
int maxProfit_1(int index, int N, vector<int>price)
{
	if(index==0){
		return N * price[0];
	}

	int notTake = maxProfit_1(index-1, N, price), take = 0;
	int curRodLen = index + 1;
	if(N >= curRodLen)
		take = price[index] + maxProfit_1(index, N-curRodLen, price);
	return max(notTake, take);
}

// using memoisation(top-down DP). TC is n*n and SC is n(stack space) + dp array.
int maxProfit_2(int index, int N, vector<int>price, vector<vector<int>>&dp)
{
	if(index==0){
		return N * price[0];
	}
	if(dp[index][N] != -1)
		return dp[index][N];

	int notTake = maxProfit_2(index-1, N, price, dp), take = 0;
	int curRodLen = index + 1;
	if(N >= curRodLen)
		take = price[index] + maxProfit_2(index, N-curRodLen, price, dp);
	return dp[index][N] = max(notTake, take);
}

// using tabulation(bottom-up DP). TC is n*n and SC is dp array.
int maxProfit_3(vector<int>price)
{
	int n = price.size(), totalRod = price.size();
 	vector<vector<int>>dp(n, vector<int>(totalRod+1, 0));

 	for(int c = 0;c<=totalRod;c++){
 		dp[0][c] = c * price[0];
 	}

 	for(int i=1;i<n;i++){
 		for(int j=0;j<=totalRod;j++){
 			int notTake = dp[i-1][j], take = 0;
			int curRodLen = i + 1;
			if(j >= curRodLen)
				take = price[i] + dp[i][j-curRodLen];
			dp[i][j] = max(notTake, take);
 		}
 	}
	return dp[n-1][totalRod];
}

// using space optimisation(bottom-up DP). TC is n*n and SC is n.
int maxProfit_4(vector<int>price)
{
 	int n = price.size(), totalRod = price.size();
 	
 	vector<int>prev(totalRod+1, 0);

 	for(int c = 0;c<=totalRod;c++){
 		prev[c] = c * price[0];
 	}

 	for(int i=1;i<n;i++){
 		vector<int>temp(totalRod+1, 0);
 		for(int j=0;j<=totalRod;j++){
 			int notTake = prev[j], take = 0;
			int curRodLen = i + 1;
			if(j >= curRodLen)
				take = price[i] + temp[j-curRodLen];
			temp[j] = max(notTake, take);
 		}
 		prev = temp;
 	}
	return prev[totalRod];
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

 	cout << maxProfit_1(n-1, n, arr) << endl;

 	vector<vector<int>>dp(n, vector<int>(n+1, -1));
 	cout << maxProfit_2(n-1, n, arr, dp) << endl;

 	cout << maxProfit_3(arr) << endl;

 	cout << maxProfit_4(arr) << endl;
	return 0;
} 