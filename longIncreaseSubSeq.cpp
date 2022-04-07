// Ques:- Given an array of n integers, find the length of the longest subsequence such that all the elements
//        are in increasing order

#include<bits/stdc++.h>
using namespace std;

// using tabulation(bottom-up DP). TC is n^2 and Sc is n.
int longest_common_subsequence_1(vector<int>arr){
    vector<int>dp(arr.size(),1);

    for(int i=1;i<arr.size();i++){
        for(int j=0;j<i;j++){
            if(arr[i] > arr[j]){
                dp[i] = max(dp[i], dp[j]+1);
            }
        }
    }
    return *max_element(dp.begin(), dp.end());
}

int main()
{

    int n;
    cin >> n;

    vector<int>arr(n);

    for(int i=0;i<n;i++){
        cin >> arr[i];
    }

    cout << longest_common_subsequence_1(arr) << endl;


    return 0;
}