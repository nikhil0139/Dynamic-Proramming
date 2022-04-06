// Ques :- Given an array of n coins and a target, return the min no. of coins that forms the sum as target.
//         You can use a coin infinite no. of times.

#include<bits/stdc++.h>
using namespace std;

// using recursion. TC is more than exponential because we are on same index multiple times, SC is more than
// n as we are calling function for same index again and again. 
int minCoins_1(int n, vector<int>coins, int target)
{
    if(n==0){
        if(target%coins[n] == 0)
            return target / coins[n];
        else
            return 1e9;
    }

    int doNotTake = 0 + minCoins_1(n-1, coins, target);
    int take = INT_MAX;
    if(coins[n] <= target)
        take = 1 + minCoins_1(n, coins, target - coins[n]);

    return min(take, doNotTake);
}

// using recursion + memoisation(top-down dp). TC is n*target, SC is n*target + target(stack space)
int minCoins_2(int n, vector<int>coins, int target, vector<vector<int>>dp)
{
    if(n==0){
        if(target%coins[n] == 0)
            return target / coins[n];
        else
            return 1e9;
    }

    if(dp[n][target] != -1)
        return dp[n][target];

    int doNotTake = 0 + minCoins_2(n-1, coins, target, dp);
    int take = INT_MAX;
    if(coins[n] <= target)
        take = 1 + minCoins_2(n, coins, target - coins[n], dp);

    return dp[n][target] = min(take, doNotTake);
}

// using tabulation(bottom-up dp). TC is n*target, SC is target.
int minCoins_3(int n, vector<int>coins, int target)
{
    vector<int>dp(target+1);
    dp[0] = 0;

    for(int i=1;i<=target;i++)
    {
        dp[i] = INT_MAX;
        for(auto coin : coins)
        {
            if(i-coin >= 0 && dp[i-coin] != INT_MAX)
                dp[i] = min(dp[i], dp[i-coin]+1);
        }
    }
    return dp[target];
}


int main()
{

    int n;
    cin >> n;

    vector<int>coins(n);
    for(int i=0;i<n;i++)
        cin >> coins[i];

    int target;
    cin >> target;

    int ans1 = minCoins_1(n-1, coins, target);
    if(ans1 >= 1e9)
        cout << -1 << endl;
    else
        cout << ans1 << endl;

    vector<vector<int>>dp(n, vector<int>(target+1, -1));
    int ans2 = minCoins_2(n-1, coins, target, dp);
    if(ans2 >= 1e9)
        cout << -1 << endl;
    else
        cout << ans2 << endl;

    int ans3 = minCoins_3(n-1, coins, target);
    if(ans3 == INT_MAX)
        cout << -1 << endl;
    else
        cout << ans3 << endl;

    return 0;
}