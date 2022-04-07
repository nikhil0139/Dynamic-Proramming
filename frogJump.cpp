// Ques:- Given an array of n integers, a frog has to reach from 0 to n-1 index by taking at most two jumps.
//        In a jump it takes the energy which is abs diff of the values in array of that indices. Find out
//        the minimum energy frog take to reach end.

#include <bits/stdc++.h>
using namespace std;

// using recursion. TC is 2^n and SC is n(more than it : stack space)
int minEnergy_1(int n, vector<int> arr)
{
    if (n == 0)
        return 0;

    /* if frog can take k jumps, then

    int ans = INT_MAX;
    for(int i=1;i<=k;i++){
        if(n-i >= 0){
            int x = minEnergy_1(n-i, arr) + abs(arr[n] - arr[n-i]);
            ans = min(ans, x);
        }
    }
    return ans; */

    int left = minEnergy_1(n - 1, arr) + abs(arr[n] - arr[n - 1]);

    int right = INT_MAX;
    if (n > 1)
        right = minEnergy_1(n - 2, arr) + abs(arr[n] - arr[n - 2]);

    return min(left, right);
}

// using recursion + memoisation (top-down DP). TC is n & SC is n(stack space) + n(dp array).
int minEnergy_2(int n, vector<int> arr, vector<int> dp)
{
    if (n == 0)
        return 0;

    if (dp[n] != -1)
        return dp[n];

    int left = minEnergy_2(n - 1, arr, dp) + abs(arr[n] - arr[n - 1]);

    int right = INT_MAX;
    if (n > 1)
        right = minEnergy_2(n - 2, arr, dp) + abs(arr[n] - arr[n - 2]);

    return dp[n] = min(left, right);
}

// using tabulation (bottom-up DP). TC is n & SC is n.
int minEnergy_3(int n, vector<int> arr)
{

    vector<int> dp(n);
    dp[0] = 0;

    for (int i = 1; i < n; i++)
    {
        int left = dp[i - 1] + abs(arr[i] - arr[i - 1]);

        int right = INT_MAX;
        if (i > 1)
            right = dp[i - 2] + abs(arr[i] - arr[i - 2]);

        dp[i] = min(left, right);
    }
    return dp[n - 1];
}

// using tabulation (bottom-up DP) and space-optimisation. TC is n & SC is 1.
int minEnergy_4(int n, vector<int> arr)
{

    int a = 0, b = 0;

    for (int i = 1; i < n; i++)
    {
        int left = b + abs(arr[i] - arr[i - 1]);

        int right = INT_MAX;
        if (i > 1)
            right = a + abs(arr[i] - arr[i - 2]);

        a = b;
        b = min(left, right);
    }
    return b;
}

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << minEnergy_1(n - 1, arr) << endl;

    vector<int> dp(n + 1, -1);
    cout << minEnergy_2(n - 1, arr, dp) << endl;

    cout << minEnergy_3(n, arr) << endl;

    cout << minEnergy_4(n, arr) << endl;

    return 0;
}