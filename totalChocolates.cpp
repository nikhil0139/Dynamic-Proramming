// Given an matrix of m*n integers, Alice start from [0][0], Bob starts from [0][n-1],
// find the max no of chocolates they both can take together. They both can move 
// left diagonal, down or right diagonal in one step and take that chocolate.

#include<bits/stdc++.h>
using namespace std;

// using simple recursion. TC is 3^n * 3^n and SC is n (stack space).
int maxChocolates_1(int i, int j1, int j2, vector<vector<int>>arr)
{
	if(j1 < 0 || j1 >= arr[0].size() || j2 < 0 || j2 >= arr[0].size())
		return -1e9;

	if(i==arr.size()-1){
		if(j1==j2)
			return arr[i][j1];
		else
			return arr[i][j1] + arr[i][j2];
	}


	int maxi = -1e9;

	for(int x = -1;x <=1;x++){
		for(int y = -1;y <= 1;y++){
			int val = 0;
			if(j1 == j2)
				val = arr[i][j1];
			else
				val += arr[i][j1] + arr[i][j2];
			val += maxChocolates_1(i+1, j1 + x, j2 + y, arr);
			maxi = max(maxi, val);
		
		}
	}
	return maxi;
}

// using memoisation(top-down DP). TC is (m*n*n)*9 and SC is (stack space) + (dp array)
int maxChocolates_2(int i, int j1, int j2, vector<vector<int>>arr,vector<vector<vector<int>>>&dp)
{
	if(j1 < 0 || j1 >= arr[0].size() || j2 < 0 || j2 >= arr[0].size())
		return -1e9;

	if(i==arr.size()-1){
		if(j1==j2)
			return arr[i][j1];
		else
			return arr[i][j1] + arr[i][j2];
	}

	if(dp[i][j1][j2] != -1)
		return dp[i][j1][j2];

	int maxi = -1e9;

	for(int x = -1;x <=1;x++){
		for(int y = -1;y <= 1;y++){
			int val = 0;
			if(j1 == j2)
				val = arr[i][j1];
			else
				val += arr[i][j1] + arr[i][j2];
			val += maxChocolates_2(i+1, j1 + x, j2 + y, arr, dp);
			maxi = max(maxi, val);
		
		}
	}
	return dp[i][j1][j2] = maxi;
}

// using tabulation(bottom-up DP). TC is (m*n*n)*9 and SC is (dp array)
int maxChocolates_3(vector<vector<int>>arr)
{
	int m = arr.size();
	int n = arr[0].size();
	vector<vector<vector<int>>>dp(m, vector<vector<int>>(n, vector<int>(n, 0)));
	for(int x=0;x<n;x++){
		for(int y=0;y<n;y++){
			if(x==y)
				dp[m-1][x][y] = arr[m-1][x];
			else
				dp[m-1][x][y] = arr[m-1][x] + arr[m-1][y];
		}
	}

	for(int i=m-2;i>=0;i--)
	{
		for(int j1=0;j1<n;j1++)
		{
			for(int j2=0;j2<n;j2++)
			{
				int maxi = -1e9;
				for(int x = -1;x <=1;x++){
					for(int y = -1;y <= 1;y++){
						int val = 0;
						if(j1 == j2)
							val = arr[i][j1];
						else
							val += arr[i][j1] + arr[i][j2];
						if(j1 + x >= 0 && j1 + x < n && j2 + y >= 0 && j2 + y < n)
							val += dp[i+1][j1 + x][j2 + y];
						else
							val += -1e9;
						maxi = max(maxi, val);
					}
				}
				dp[i][j1][j2] = maxi;
			}
		}	
	}
	return dp[0][0][n-1];
}

// using space-optimisation(bottom-up DP). TC is (m*n*n)*9 and SC is 2d vector(n*n).
int maxChocolates_4(vector<vector<int>>arr)
{
	int m = arr.size();
	int n = arr[0].size();
	vector<vector<int>>prev(n, vector<int>(n, 0));
	for(int x=0;x<n;x++){
		for(int y=0;y<n;y++){
			if(x==y)
				prev[x][y] = arr[m-1][x];
			else
				prev[x][y] = arr[m-1][x] + arr[m-1][y];
		}
	}

	for(int i=m-2;i>=0;i--)
	{
		vector<vector<int>>temp(n, vector<int>(n, 0));
		for(int j1=0;j1<n;j1++)
		{
			for(int j2=0;j2<n;j2++)
			{
				int maxi = -1e9;
				for(int x = -1;x <=1;x++){
					for(int y = -1;y <= 1;y++){
						int val = 0;
						if(j1 == j2)
							val = arr[i][j1];
						else
							val += arr[i][j1] + arr[i][j2];
						if(j1 + x >= 0 && j1 + x < n && j2 + y >= 0 && j2 + y < n)
							val += prev[j1 + x][j2 + y];
						else
							val += -1e9;
						maxi = max(maxi, val);
					}
				}
				temp[j1][j2] = maxi;
			}
		}
		prev = temp;	
	}
	return prev[0][n-1];
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

	cout << maxChocolates_1(0, 0, n-1, arr) << endl;
	
	vector<vector<vector<int>>>dp(m, vector<vector<int>>(n, vector<int>(n, -1)));
	cout << maxChocolates_2(0, 0, n-1, arr, dp) << endl;

	cout << maxChocolates_3(arr) << endl;

	cout << maxChocolates_4(arr) << endl;

	return 0;
}