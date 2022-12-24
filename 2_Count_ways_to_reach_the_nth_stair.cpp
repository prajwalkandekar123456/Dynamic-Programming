// Problem
/*
There are n stairs, a person standing at the bottom wants to reach the top. The person can climb either 1 stair or 2 stairs at a time. Count the number of ways, the person can reach the top (order does matter).

Example 1:

Input:
n = 4
Output: 5
Explanation:
You can reach 4th stair in 5 ways. 
Way 1: Climb 2 stairs at a time. 
Way 2: Climb 1 stair at a time.
Way 3: Climb 2 stairs, then 1 stair
and then 1 stair.
Way 4: Climb 1 stair, then 2 stairs
then 1 stair.
Way 5: Climb 1 stair, then 1 stair and
then 2 stairs.
*/

#include<bits/stdc++.h>
using namespace std;

//Optimal Solution
// Time Complexity : O(N)
// Space Complexity : O(1)
int countWays(int n)
{
    int first = 1,second = 2;
    for(int i = 2;i<n;i++)
    {
        int third = first+second;
        first = second;
        second = third;
    }
    return second;
}

// Tabulation
// Time Complexity : O(N)
// Space Complexity : O(N)

int countWays1(int n)
{
    vector<int> dp(n+1,-1);
    dp[0] = dp[1] = 1;
    for(int i = 2;i<=n;i++)
    {
        dp[i] = dp[i-1]+dp[i-2];
    }
    return dp[n];
}

// Tabulation
// Time Complexity : O(N)
// Space Complesity : O(N)

int countWays3(int n)
{
    if(n<=1) return n;
    vector<int> dp(n+1,-1);
    if(dp[n]!=-1) return dp[n];
    return dp[n] = countWays3(n-1)+countWays3(n-2);
    return dp[n];
}
int main()
{
    int n;
    cin>>n;
    int ans = countWays(n);
    cout<<ans<<endl;
    return 0;
}