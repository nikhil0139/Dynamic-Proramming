// Given an array of n integers, find the minimum difference between two subsets.

#include<bits/stdc++.h>
using namespace std;

int main(){

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, sum = 0;
	cin >> n;

	vector<int>arr(n);

	for(int i=0;i<n;i++){
		cin >> arr[i];
		sum += arr[i];
	}
	
	vector<bool>prev(sum+1, false), temp(sum+1, false);

	prev[0] = true;
	temp[0] = true;

	if(sum >= arr[0])
		prev[arr[0]] = true;

	for(int i=1;i<n;i++){
		for(int j=1;j<=sum;j++){
			bool notTake = prev[j];
			bool take = false;
			if(j >= arr[i])
				take = prev[j - arr[i]];
			temp[j] = notTake || take;
		}
		prev = temp;
	}

	int ans = 1e9;

	for(int i=0;i<=sum/2;i++){
		if(prev[i] == true)
			ans = min(ans, abs(i-(sum-i)));
	}

	cout << ans << endl;
	return 0;
}