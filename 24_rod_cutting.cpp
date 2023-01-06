// Problem
/*
We are given a rod of size ‘N’. It can be cut into pieces. Each length of a piece has a particular price given by the price array. Our task is to find the maximum revenue that can be generated by selling the rod after cutting( if required) into pieces.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Recursion
    // Time COmplexity : Exponential
    // Space Complexity : O(N)
    int recc(int index,int target,vector<int> &price)
    {
        if(index == 0)
        {
            return target*price[0];
        }
        int notTake = recc(index-1,target,price);
        int take = INT_MIN;
        int rodLength = index+1;
        if(rodLength<=target) take = price[index]+recc(index,target-rodLength,price);
        return max(take,notTake);
    }
    // Memoization
    // Time Complexity : O(N*N)
    // Space Complexity : O(N*N)+O(N)
    int memo(int index,int target,vector<int> &price,vector<vector<int>> &dp)
    {
        if(index == 0)
        {
            return target*price[0];
        }
        if(dp[index][target]!=-1) return dp[index][target];
        int notTake = memo(index-1,target,price,dp);
        int take = INT_MIN;
        int rodLength = index+1;
        if(target>=rodLength) take = price[index]+memo(index,target-rodLength,price,dp);
        return dp[index][target] = max(take,notTake);
    }
    // Tabulation
    // Time Complexity : O(N*N)
    // Space Complexity : O(N*N)
    int tab(int n,int target,vector<int> &price)
    {
        vector<vector<int>> dp(n,vector<int>(target+1,0));
        for(int j = 0;j<=target;j++)
        {
            dp[0][j] = j*price[0];
        }
        for(int i = 1;i<n;i++)
        {
            for(int j = 0;j<=target;j++)
            {
                int notTake = dp[i-1][j];
                int take = INT_MIN;
                int rodLength = i+1;
                if(j>=rodLength) take = price[i]+dp[i][j-rodLength];
                dp[i][j] = max(take,notTake);
            }
        }
        return dp[n-1][target];
    }
    // Optimization
    // Time Complexity : O(N*N)
    // Space Complexity :O(N)
    int opti(int n,int target,vector<int> &price)
    {
        vector<int> prev(target+1,0),curr(target+1,0);
        for(int j = 0;j<=target;j++)
        {
            prev[j] = j*price[0];
        }
        for(int i = 1;i<n;i++)
        {
            for(int j = 0;j<=target;j++){
                int notTake = prev[j];
                int take = INT_MIN;
                int rodLength = i+1;
                if(j>=rodLength) take = price[i]+prev[j-rodLength];
                curr[j] = max(take,notTake);
            }
            prev = curr;
        }
        return prev[target];
    }
public:
    int cutRod(int n,vector<int> &price)
    {
        // Recursion
        // return recc(n-1,n,price);
        // Memoization
        vector<vector<int>> dp(n,vector<int>(n+1,-1));
        // return memo(n-1,n,price,dp);
        // Tabulation
        // return tab(n,n,price);
        // Optimization
        return opti(n,n,price);
    }
};
int main()
{
    int n;
    cin>>n;
    vector<int> price(n);
    for(int i = 0;i<n;i++)
    {
        cin>>price[i];
    }
    Solution obj;
    int ans = obj.cutRod(n,price);
    cout<<ans<<endl;
    return 0;
}