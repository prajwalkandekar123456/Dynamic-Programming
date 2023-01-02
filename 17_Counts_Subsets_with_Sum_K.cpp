// Problem
/*
We are given an array ‘ARR’ with N positive integers and an integer K. We need to find the number of subsets whose sum is equal to K.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Recursion
    // Time Complexity : O(2^n)
    // Space Complexity : O(N)
    int recc(int index,int target,vector<int> &arr)
    {
        sort(arr.begin(),arr.end(),greater<int>());
        if(target == 0) return 1;
        if(index == 0)
        {
            return arr[index] == target;
        }
        int notPick = recc(index-1,target,arr);
        int pick = 0;
        if(arr[index]<=target) pick = recc(index-1,target-arr[index],arr);
        return pick+notPick;
    }
    // Memoization
    // Time Conplexity : O(N*M)
    // Space Complexity : O(N*M)+O(N)
    int memo(int index,int target,vector<int> &arr,vector<vector<int>> &dp)
    {
        sort(arr.begin(),arr.end(),greater<int>());
        if(target == 0) return 1;
        if(index == 0)
        {
            return arr[index] == target;
        }
        if(dp[index][target]!=-1) return dp[index][target];
        int notPick = memo(index-1,target,arr,dp);
        int pick = 0;
        if(target>=arr[index]) pick = memo(index-1,target-arr[index],arr,dp);
        return dp[index][target] = pick+notPick;
    }
    // Tabulation
    // Time Complexity : O(N*K)
    // Space Complexity : O(N*K)
    int tab(int n,int target,vector<int> &arr)
    {
        sort(arr.begin(),arr.end(),greater<int>());
        vector<vector<int>> dp(n,vector<int>(target+1,0));
        for(int i = 0;i<n;i++) dp[i][0] = 1;
        if(arr[0]<=target) dp[0][arr[0]] = 1;
        for(int i = 1;i<n;i++)
        {
            for(int j = 0;j<=target;j++)
            {
                int notPick = dp[i-1][j];
                int pick = 0;
                if(j>=arr[i]) pick = dp[i-1][j-arr[i]];
                dp[i][j] = pick+notPick;
            }
        }
        return dp[n-1][target];
    }
    // Optimization
    // Time Complexity : O(N*M)
    // Space Complexity : O(N);
    int opti(int n,int target,vector<int> &arr)
    {
        sort(arr.begin(),arr.end(),greater<int>());
        vector<int> prev(target+1,0);
        prev[0] = 1;
        if(arr[0]<=target) prev[arr[0]] = 1;
        for(int i = 1;i<n;i++)
        {
            vector<int> curr(target+1,0);
            curr[0] = 1;
            for(int j = 0;j<=target;j++)
            {
                int notPick = prev[j];
                int pick = 0;
                if(j>=arr[i])
                {
                    pick = prev[j-arr[i]];
                }
                curr[j] = pick+notPick;
            }
            prev= curr;
        }
        return prev[target];
    }
public:
    int findWays(int n,int tar,vector<int> &arr)
    {
        // Recursion
        // return recc(n-1,tar,arr);
        /*
        // Memoization
        vector<vector<int>> dp(n,vector<int>(tar+1,-1));
        return memo(n-1,tar,arr,dp);
        */
       /*
       // Tabulation
       return tab(n,tar,arr);
       */
        // Optimization
        return opti(n,tar,arr);
    }
};

int main()
{
    int n,k;
    cin>>n>>k;
    vector<int> arr(n);
    for(int i = 0;i<n;i++)
    {
        cin>>arr[i];
    }
    Solution obj;
    int ans = obj.findWays(n,k,arr);
    cout<<ans<<endl;
    return 0;
}