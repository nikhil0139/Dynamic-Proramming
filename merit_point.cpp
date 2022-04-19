// Given a matrix of n X 3 integers, calculate the maximum merit points from the
// activity you can take by not selecting same activity for the consecutive days.

#include<bits/stdc++.h>
using namespace std;

// using recursion. TC is exponential and SC is (stack space). 
int maxMeritPoints_1(int day, vector<vector<int>>arr, int lastTake)
{
	if(day == 0){
		int maxi = 0;
		for(int i=0;i<3;i++){
			if(i!=lastTake)
				maxi = max(maxi, arr[0][i]);
		}
		return maxi;
	}
	int points = 0, maxi = 0;
	for(int i=0;i<3;i++){
		if(i!=lastTake){
			points = arr[day][i];
			points += maxMeritPoints_1(day - 1, arr, i);
			maxi = max(maxi, points);
		}
	}
	return maxi;
}
 
// using memoisation (top-down DP). TC is (N*4)*3 & SC is N(stack) + N*4(dp matrix)
int maxMeritPoints_2(int day, vector<vector<int>>arr, int lastTake, vector<vector<int>>&dp)
{
	if(day == 0){
		int maxi = 0;
		for(int i=0;i<3;i++){
			if(i!=lastTake)
				maxi = max(maxi, arr[0][i]);
		}
		return maxi;
	}

	if(dp[day][lastTake] != -1)
		return dp[day][lastTake];

	int points = 0, maxi = 0;
	for(int i=0;i<3;i++){
		if(i!=lastTake){
			points = arr[day][i];
			points += maxMeritPoints_2(day - 1, arr, i, dp);
			maxi = max(maxi, points);
		}
	}
	return dp[day][lastTake] = maxi;

}

// using tabulation (bottom-up DP). TC is (N*4)*3 & SC is N*4(dp matrix)
int maxMeritPoints_3(int n, vector<vector<int>>arr)
{
		vector<vector<int>>dp(n, vector<int>(4, 0));
		dp[0][0] = max(arr[0][1], arr[0][2]);
		dp[0][2] = max(arr[0][1], arr[0][0]);
		dp[0][1] = max(arr[0][0], arr[0][2]);
		dp[0][3] = max(arr[0][0], max(arr[0][1], arr[0][2]));	

		for(int day = 1; day < n; day++){
			for(int last = 0;last < 4;last++){
				for(int i = 0; i < 3; i++){
					if(i != last){
						int points = arr[day][i];
						points += dp[day-1][i];
						dp[day][last] = max(dp[day][last], points);
					}
				}
			}
		}
	return dp[n-1][3];
}

// using space optimisation (bottom-up DP). TC is ((N*4)*3) & SC is approx constant.
int maxMeritPoints_4(int n, vector<vector<int>>arr)
{
		vector<int>prev(4, 0);
		prev[0] = max(arr[0][1], arr[0][2]);
		prev[1] = max(arr[0][0], arr[0][2]);
		prev[2] = max(arr[0][1], arr[0][0]);
		prev[3] = max(arr[0][0], max(arr[0][1], arr[0][2]));	

		for(int day = 1; day < n; day++){
			vector<int>temp(4, 0);
			for(int last = 0;last < 4;last++){
				for(int i = 0; i < 3; i++){
					if(i != last){
						int points = arr[day][i];
						points += prev[i];
						temp[last] = max(temp[last], points);
					}
				}
			}
			prev = temp;
		}
	return prev[3];
}


int main(){

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int n;
	cin >> n;

	vector<vector<int>>arr(n, vector<int>(3, 0));

	for(int i=0;i<n;i++){
		int x, y, z;
		cin >> x >> y >> z;
		arr[i][0] = x;
		arr[i][1] = y;
		arr[i][2] = z;
	}

	cout << maxMeritPoints_1(n-1, arr, 3) << endl;

	vector<vector<int>>dp(n, vector<int>(4, -1));
	cout << maxMeritPoints_2(n-1, arr, 3, dp) << endl;

	cout << maxMeritPoints_3(n, arr) << endl;

	cout << maxMeritPoints_4(n, arr) << endl;

	return 0;
}