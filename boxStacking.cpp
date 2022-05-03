// Given a vector of n boxes, each box has length, width and height. Determine the 
// maximum possible stack you can make by placing one book over other.
// Condition is that upper book has strictly smaller dimensions over lower book. 

#include<bits/stdc++.h>
using namespace std;

bool comp(vector<int>b1, vector<int>b2){
	return b1[2]<b2[2];
}

bool Place(vector<int>b1, vector<int>b2){
	if(b1[0] < b2[0] && b1[1] < b2[1] && b1[2] < b2[2])
		return true;
	return false;
}

int maxHeight(vector<vector<int>>arr, int n){

	sort(arr.begin(), arr.end(), comp);

	vector<int>dp(n+1, 0);
	dp[0] = arr[0][2];

	for(int i=1;i<n;i++){
		dp[i] = arr[i][2];
		int maxi = 0;
		for(int j=0;j<i;j++){
			if(Place(arr[j], arr[i])){
				maxi = max(maxi, dp[j] + dp[i]);
			}
		}
		dp[i] = max(maxi, dp[i]);
		//cout << dp[i] << " ";
	}
	return *max_element(dp.begin(), dp.end());
}

int main(){

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n;
	cin >> n;

	vector<vector<int>>arr(n, vector<int>(3, 0));

	int x, y, z;
	for(int i=0;i<n;i++){
		cin >> x >> y >> z;
		arr[i][0] = x;
		arr[i][1] = y;
		arr[i][2] = z;
	}

	cout << maxHeight(arr, n) << endl;
	
	return 0;
}
