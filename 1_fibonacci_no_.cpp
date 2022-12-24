#include<bits/stdc++.h>
using namespace std;

/*
// Recursion
// Time Complexity : O(2^N)
// Space Complexity : O(N)

int rec(int n)
{
    if(n<=1) return n;
    return rec(n-1)+rec(n-2);
}
*/


// Memoization
//Time complexity : O(N)
// Space Complexity : O(N)+O(N)

/*

int f(int n,vector<int> &dp)
{
    if(n<=1) return n;
    if(dp[n]!=-1) return dp[n];
    return dp[n] = f(n-1,dp)+f(n-2,dp);
}

*/

// Tabulation
// Time Complexity : O(N)
// Space Complexity : O(N)
int tab(int n,vector<int> &dp)
{
    dp[0] = 0;
    dp[1] = 1;
    for(int i = 2;i<=n;i++)
    {
        dp[i] = dp[i-1]+dp[i-2];
    }
    return dp[n];
}

/*
// Optimized
// Time Complexity : O(N)
// Space Complexity :O(1)

int op(int n)
{
    int prev2 = 0,prev = 1;
    for(int i = 2;i<=n;i++)
    {
        int curr = prev+prev2;
        prev2 = prev;
        prev = curr;
    }
    return prev;
}
*/

int main()
{
    int n;
    cin>>n;
    vector<int> dp(n+1,-1);
    cout<<tab(n,dp)<<endl;
    return 0;
}
