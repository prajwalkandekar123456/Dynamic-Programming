// Problem
/*
Matrix Chain Multiplication | Partition DP Starts

In the coming articles, we will discuss problems related to a new pattern called “Partition DP”.Before proceeding further, let us understand how to identify whether a problem can be solved using this pattern.

Pattern Identification:

Whenever we need to find the answer to a large problem such that the problem can be broken into subproblems and the final answer varies due to the order in which the subproblems are solved, we can think in terms of partition DP.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Time Complexity : Exponential
    // Space Complexity : O(N)
    int recc(int i,int j,vector<int> &arr,int n)
    {
        if(i == j) return 0;
        int mini = 1e9;
        for(int k = i;k<j;k++)
        {
            int steps = arr[i-1]*arr[j]*arr[k]+recc(i,k,arr,n)+recc(k+1,j,arr,n);
            if(steps<mini)
            {
                mini = steps;
            }
        }
        return mini;
    }
    // Memoization
    // Time Complexity : O(N*N*N)
    // Space COmplexity : O(N*N)+O(N)
    int memo(int i,int j,vector<int> &arr,vector<vector<int>> &dp)
    {
        if(i == j) return 0;
        if(dp[i][j]!=-1) return dp[i][j];
        int mini = 1e9;
        for(int k = i;k<j;k++)
        {
            int steps = arr[i-1]*arr[j]*arr[k]+memo(i,k,arr,dp)+memo(k+1,j,arr,dp);
            if(mini>steps)
            {
                mini = steps;
            }
        }
        return dp[i][j] = mini;
    }
    // Tabulation
    // Time COmplexity : O(N*N*N)
    // Space Complexity : O(N*N)
    int tab(int n,vector<int> &arr)
    {
        int dp[n][n];
        for(int i = 0;i<n;i++)
        {
            dp[i][i] = 0;
        }
        for(int i = n-1;i>=1;i--)
        {
            
            for(int j = i+1;j<n;j++)
            {
                int mini = 1e9;
                for(int k = i;k<j;k++)
                {
                    int steps = arr[i-1]*arr[j]*arr[k]+dp[i][k]+dp[k+1][j];
                    if(steps<mini)
                    {
                        mini = steps;
                    }
                }
                dp[i][j] = mini;
            }
        }
        return dp[1][n-1];
    }
public:
    int matrixMultiplication(int n,vector<int> &arr)
    {
        // Recursion
        // return recc(1,n-1,arr,n);
        // Memoization
        vector<vector<int>> dp(n,vector<int>(n,-1));
        // return memo(1,n-1,arr,dp);
        // Tabulation
        return tab(n,arr);
    }
};
int main()
{
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i = 0;i<n;i++)
    {
        cin>>arr[i];
    }
    Solution obj;
    int ans = obj.matrixMultiplication(n,arr);
    cout<<ans<<endl;
    return 0;
}