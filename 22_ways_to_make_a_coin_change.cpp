// Problem
/*
We are given an array Arr with N distinct coins and a target. We have an infinite supply of each coin denomination. We need to find the number of ways we sum up the coin values to give us the target.

Each coin can be used any number of times.


*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Recursion
    // Time Complexity : >=O(N)
    // Space COmplexity : )(target)
    int recc(int index,int target,vector<int> &arr)
    {
        if(index == 0)
        {
            return target%arr[index] == 0;
        }
        int notTake = recc(index-1,target,arr);
        int take = 0;
        if(target>=arr[index]) take = recc(index,target-arr[index],arr);
        return take+notTake;
    }
    // Memoization
    // Time Complexity : O(N*target)
    // Space Complexity : O(N*tareget)+O(target)
    int memo(int index,int target,vector<int> &arr,vector<vector<int>> &dp)
    {
        if(index == 0)
        {
            return target%arr[index] == 0;
        }
        if(dp[index][target]!=-1) return dp[index][target];
        int notTake = memo(index-1,target,arr,dp);
        int take = 0;
        if(target>=arr[index]) take = memo(index,target-arr[index],arr,dp);
        return dp[index][target] = take+notTake;
    }
    // Tabulation
    // Time Complexity : O(N*target)
    // Space COmplexity : O(N*target)
    int tab(int n,int target,vector<int> &arr)
    {
        vector<vector<int>> dp(n,vector<int>(target+1,0));
        for(int j = 0;j<=target;j++)
        {
            dp[0][j] = j%arr[0] == 0;
        }
        for(int i =1;i<n;i++)
        {
            for(int j = 0;j<=target;j++)
            {
                int notTake = dp[i-1][j];
                int take = 0;
                if(j>=arr[i]) take = dp[i][j-arr[i]];
                dp[i][j] = take+notTake;
            }
        }
        return dp[n-1][target];
    }
    // Space Optimization
    // Time Complexity : O(N*target)
    // Space OCmplexity : O(target)
    int opti(int n,int target,vector<int> &arr)
    {
        vector<int> prev(target+1,0),curr(target+1,0);
        for(int j = 0;j<=target;j++)
        {
            prev[j] = j%arr[0] == 0;
        }
        for(int i = 1;i<n;i++)
        {
            for(int j = 0;j<=target;j++)
            {
                int notTake = prev[j];
                int take = 0;
                if(j>=arr[i]) take = curr[j-arr[i]];
                curr[j] = take+notTake;
            }
            prev = curr;
        }
        return prev[target];
    }
public:
    int countWaysToMakeChange(vector<int> &arr,int n,int target)
    {
        // Recursion
        // return recc(n-1,target,arr);
        // Memoization
        vector<vector<int>> dp(n,vector<int>(target+1,-1));
        // return memo(n-1,target,arr,dp);
        // Tabulation
        // return tab(n,target,arr);
        // Optimization
        return opti(n,target,arr);
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
    int target;
    cin>>target;
    Solution obj;
    int ans = obj.countWaysToMakeChange(arr,n,target);
    cout<<ans<<endl;
    return 0;
}