// Ques:- You are given N no of stairs and a integer k. You can climb at most k stairs at a time.
//        Return the total number of ways to reach to the top.

#include<bits/stdc++.h>
using namespace std;

// using recursion. TC is k^n and SC is n(stack space).
int waysToClimbLadder_1(int n, int k)
{
    if(n==0)
        return 1;
    if(n<0)
        return 0;
    
    int ans = 0;
    for(int i=1;i<=k;i++){
        ans += waysToClimbLadder_1(n-i, k);
    }
    return ans;
}

// using recursion and memoisation(top-down DP). TC is n*k and SC is n(stack space).
int waysToClimbLadder_2(int n, int k, vector<int>dp)
{
    if(n==0)
        return 1;
    if(n<0)
        return 0;
    if(dp[n] != -1)
        return dp[n];
    int ans = 0;
    for(int i=1;i<=k;i++){
        ans += waysToClimbLadder_2(n-i, k, dp);
    }
    return dp[n] = ans;
}

// using tabulation(bottom-up DP). TC is n*k and SC is n(for dp array).
int waysToClimbLadder_3(int n, int k)
{
    int ans;
    vector<int>dp(n+1, 0);
    dp[0] = 1;
    for(int i=1;i<=n;i++){
        ans = 0;
        for(int j=1;j<=k;j++)
        {
            if(i-j>=0)
                ans += dp[i-j];
        }
        dp[i] = ans;
    }
    return dp[n];
}

// using tabulation(bottom-up DP) but time-optimised(not using k-th loop). TC is n and SC is n.
// for making space optimised we can use variables similar in fibonacci series.
int waysToClimbLadder_4(int n, int k)
{
    int ans;
    vector<int>dp(n+1, 0);
    dp[0] = 1;
    dp[1] = 1;
    for(int i=2;i<=k;i++){
        dp[i] = 2 * dp[i-1];
    }

    for(int i=k+1;i<=n;i++){
        dp[i] = 2 * dp[i-1] - dp[i-k-1];
    }
    return dp[n];
}

int main()
{
    int n, k;
    cin >> n >> k;

    cout << waysToClimbLadder_1(n, k) << endl;

    vector<int>dp(n+1, -1);
    cout << waysToClimbLadder_2(n, k, dp) << endl;

    cout << waysToClimbLadder_3(n, k) << endl;

    cout << waysToClimbLadder_4(n, k) << endl;
    return 0;
}