#include<bits/stdc++.h>
using namespace std;

int NoOfBSTs_1(int n){
	if(n==0 || n==1)
		return 1;

	int ans = 0;
	for(int i=1;i<=n;i++){
		int x = NoOfBSTs_1(i-1) * NoOfBSTs_1(n-i);
		ans += x;
	}
	return ans;	
}

int NoOfBSTs_2(int n, vector<int>&dp){
	if(n==0 || n==1)
		return 1;

	if(dp[n] != -1)
		return dp[n];

	int ans = 0;
	for(int i=1;i<=n;i++){
		int x = NoOfBSTs_2(i-1, dp) * NoOfBSTs_2(n-i, dp);
		ans += x;
	}
	return dp[n] = ans;	
}

int NoOfBSTs_3(int n){

	vector<int>dp(n+1, 1);

	
	for(int i=2;i<=n;i++){
		int ans = 0;
		for(int j=1;j<=i;j++){
			int x = dp[j-1] * dp[i-j];
			ans += x;
		}
		dp[i] = ans;
	}
	return dp[n];
}


int main(){

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int n;
	cin >> n;

	cout << NoOfBSTs_1(n) << endl;

	vector<int>dp(n+1, -1);
	cout << NoOfBSTs_2(n, dp) << endl;

	cout << NoOfBSTs_1(n) << endl;
	


	return 0;
}