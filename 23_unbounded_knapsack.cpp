// Problem
/*
A thief wants to rob a store. He is carrying a bag of capacity W. The store has ‘n’ items of infinite supply. Its weight is given by the ‘wt’ array and its value by the ‘val’ array. He can either include an item in its knapsack or exclude it but can’t partially have it as a fraction. We need to find the maximum value of items that the thief can steal. He can take a single item any number of times he wants and put it in his knapsack.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Recursion
    // Time Complexity " Exponential"
    // Space COmplexity : O(W)
    int recc(int index,int target,vector<int> &profit,vector<int> &weight)
    {
        if(index == 0)
        {
            return (target/weight[0])*profit[0];
        }
        int notTake = 0+recc(index-1,target,profit,weight);
        int take = INT_MIN;
        if(target>=weight[index]) take = profit[index]+recc(index,target-weight[index],profit,weight);
        return max(take,notTake);
    }
    // Memoization
    // Time Comolexity : O(N*W)
    // Space COmplecity : O(N*W+O(W)
    int memo(int index,int target,vector<int> &profit,vector<int> &weight,vector<vector<int>> &dp)
    {
        if(index == 0)
        {
            return (target/weight[index])*profit[index];
        }
        if(dp[index][target]!=-1) return dp[index][target];
        int notTake = 0+memo(index-1,target,profit,weight,dp);
        int take = INT_MIN;
        if(target>=weight[index]) take = profit[index]+memo(index,target-weight[index],profit,weight,dp);
        return dp[index][target] = max(take,notTake);
    }
    // Tabulation
    // Time Complexity : O(N*W)
    // Space COmplexity : O(N*W)
    int tab(int n,int target,vector<int> &profit,vector<int> &weight)
    {
        vector<vector<int>> dp(n,vector<int>(target+1,0));
        for(int j = 0;j<=target;j++)
        {
            dp[0][j] = (j/weight[0])*profit[0];
        }
        for(int i =1;i<n;i++)
        {
            for(int j = 0;j<=target;j++)
            {
                int notTake = dp[i-1][j];
                int take = INT_MIN;
                if(j>=weight[i]) take = profit[i]+dp[i-1][j-weight[i]];
                dp[i][j] = max(take,notTake);
            }
        }
        return dp[n-1][target];
    }
    // Optimization
    // Time Complexity : O(N*K)
    // Space COmplexity : O(k)
    int opti(int n,int target,vector<int> &profit,vector<int> &weight)
    {
        vector<int> prev(target+1,0),curr(target+1,0);
        for(int j = 0;j<=target;j++)
        {
            prev[j] = (j/weight[0])*profit[0];
        }
        for(int i = 1;i<n;i++)
        {
            for(int j = 0;j<=target;j++)
            {
                int notTake = 0+prev[j];
                int take = INT_MIN;
                if(j>=weight[i]) take = profit[i]+curr[j-weight[i]];
                curr[j] = max(take,notTake);
            }
            prev = curr;
        }
        return prev[target];
    }
public:
     int unboundedKnapsack(int n,int w,vector<int> &profit,vector<int> &weight)
     {
        // Recursion
        return recc(n-1,w,profit,weight);
        // Memoization
        vector<vector<int>> dp(n,vector<int> (w+1,-1));
        // return memo(n-1,w,profit,weight,dp);
        // Tabulation
        // return tab(n,w,profit,weight);
        // Optimization
        // return opti(n,w,profit,weight);
     }
};
int main()
{
    int n,target;
    cin>>n>>target;
    vector<int> profit(n),weight(n);
    for(int i = 0;i<n;i++)
    {
        cin>> profit[i];
    }
    for(int j = 0;j<n;j++)
    {
        cin>>weight[j];
    }
    Solution obj;
    int ans = obj.unboundedKnapsack(n,target,profit,weight);
    cout<<ans<<endl;
    return 0;
}