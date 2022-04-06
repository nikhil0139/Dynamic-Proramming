// Ques :- Given an integer n, return the n-th fibonacci number.

#include<bits/stdc++.h>
using namespace std;

// using simple recursion. TC is 2^n & SC is n.
int fibonacci_1(int n)
{
    if(n==0||n==1)
        return n;
    return fibonacci_1(n-1) + fibonacci_1(n-2);
}

// using recursion + memoisation (top-down DP). TC is n & SC is n.
int fibonacci_2(int n, vector<int>dp)
{
    if(n==0||n==1)
        return n;
    if(dp[n]!=-1)
        return dp[n];
    return dp[n] = fibonacci_2(n-1, dp) + fibonacci_2(n-2, dp);
}

// using tabulation (bottom-up DP). TC is n & SC is n.
int fibonacci_3(int n)
{
    vector<int>dp(n+1);
    dp[0] = 0;
    dp[1] = 1;
    for(int i=2;i<=n;i++)
        dp[i] = dp[i-1] + dp[i-2];
    return dp[n];
}

// using three variables inside for loop but for space optimisation. TC is n & SC is 1.
int fibonacci_4(int n)
{
    int a = 0, b = 1, c;
    for(int i=2;i<=n;i++)
    {
        c = a+b;
        a = b;
        b = c;
    }
    return b;
}

int main()
{

    int n;
    cin >> n;

    cout << fibonacci_1(n) << endl;

    vector<int>dp(n+1, -1);
    cout << fibonacci_2(n, dp) << endl;

    cout << fibonacci_3(n) << endl;

    cout << fibonacci_4(n) << endl;

    return 0;
}