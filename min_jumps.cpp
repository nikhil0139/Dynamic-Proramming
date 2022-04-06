// Ques:- Given an array of n intergers. You are at starting position and you can take at most arr[i] jumps to reach at next point. You have to reach to the end of the array.
//        Find the minimum no of steps you have to take to reach there.

#include<bits/stdc++.h>
using namespace std;

// using recursion. TC is n^max(arr[i]) and SC is n(stack space).
int minWaysToReachEnd_1(int n, vector<int>arr, int i)
{
    if(i==n-1)
        return 0;

    if(i>=n)
        return INT_MAX;

    int steps = INT_MAX;
    for(int jump = 1;jump<=arr[i];jump++)
    {
        int next = i + jump;
        int substeps = minWaysToReachEnd_1(n, arr, next);
        if(substeps!=INT_MAX)
            steps = min(steps, substeps + 1);
    }
    return steps;
}

// using recursion and memoisation(top-down DP). TC is n*max(arr[i]) and SC is n(stack space).
int minWaysToReachEnd_2(int n, vector<int>arr, int i, vector<int>dp)
{
    if(i==n-1)
        return 0;

    if(i>=n)
        return INT_MAX;

    if(dp[i] != -1)
        return dp[i];

    int steps = INT_MAX;
    for(int jump = 1;jump<=arr[i];jump++)
    {
        int next = i + jump;
        int substeps = minWaysToReachEnd_2(n, arr, next, dp);
        if(substeps!=INT_MAX)
            steps = min(steps, substeps + 1);
    }
    return dp[i] = steps;
}

int main()
{
    int n;
    cin >> n;

    vector<int>arr(n);
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }

    cout << minWaysToReachEnd_1(n, arr, 0) << endl;

    vector<int>dp(n+1, -1);
    cout << minWaysToReachEnd_2(n, arr, 0, dp) << endl;
    return 0;
}