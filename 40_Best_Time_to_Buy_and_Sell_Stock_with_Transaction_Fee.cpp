// Problem
/*
We are given an array Arr[] of length n. It represents the price of a stock on ‘n’ days. The following guidelines need to be followed:

We can buy and sell the stock any number of times.
In order to sell the stock, we need to first buy it on the same or any previous day.
We can’t buy a stock again after buying it once. In other words, we first buy a stock and then sell it. After selling we can buy and sell again. But we can’t sell before buying and can’t buy before selling any previously bought stock.
After every transaction, there is a transaction fee (‘fee’) associated with it.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Recursion
    // Time COmplexity : Exponential
    // Space Complexity : O(N)
    int recc(int index,int buy,int fee,vector<int> &prices,int n)
    {
        if(index == n) return 0;
        if(buy)
        {
            return max(-prices[index] + recc(index+1,0,fee,prices,n)-fee, recc(index+1,1,fee,prices,n));
        }
        else{
            return max(prices[index]+recc(index+1,1,fee,prices,n),recc(index+1,0,fee,prices,n));
        }
    }
    // Memoization
    // Time Complexity : O(N*2)
    // Space Complexity : O(N*2)+O(N+2)
    int memo(int index,int buy,int fee,vector<int> &prices,int n,vector<vector<int>> &dp)
    {
        if(index == n) return 0;
        if(dp[index][buy]!=-1) return dp[index][buy];
        if(buy)
        {
            return dp[index][buy] = max(-prices[index]+memo(index+1,0,fee,prices,n,dp)-fee,memo(index+1,1,fee,prices,n,dp));
        }
        else{
            return dp[index][buy] = max(prices[index]+memo(index+1,1,fee,prices,n,dp),memo(index+1,0,fee,prices,n,dp));
        }
    }
    // Tabulation
    // Time COmplexity : O(N*2)
    // Space Complexity : O(N*2)
    int tab(int n,int fee,vector<int> &prices)
    {
        if(n == 0) return 0;
        vector<vector<int>> dp(n+1,vector<int>(2,0));
        for(int i = n-1;i>=0;i--)
        {
            for(int j = 0;j<=1;j++)
            {
                if( j == 0)
                {
                    dp[i][j] = max(0+dp[i+1][0],-prices[i]-fee+dp[i+1][1]);
                }
                if(j == 1)
                {
                    dp[i][j] = max(0+dp[i+1][1],prices[i]+dp[i+1][0]);
                }
            }
        }
        return dp[0][0];
    }
    // Optimization
    // Time Complexity : O(N*2)
    // Space Complexity : O(2)
    int opti(int n,int fee,vector<int> &prices)
    {
        if(n == 0) return 0;
        vector<int> curr(2,0),after(2,0);
        for(int i = n-1;i>=0;i--)
        {
            for(int j = 0;j<=1;j++)
            {
                if(j == 0)
                {
                    curr[j] = max(0+after[0],-prices[i]-fee+after[1]);
                }
                if( j== 1)
                {
                    curr[j] = max(0+after[1],prices[i]+after[0]);
                }
            }
            after = curr;
        }
        return after[0];
    }
public:
    int maximumProfit(int n, int fee,vector<int> &prices)
    {
        // Recurion
        // return recc(0,1,fee,prices,n);
        // Memoization
        vector<vector<int>> dp(n,vector<int>(2,-1));
        // return  memo(0,1,fee,prices,n,dp);
        // Tabulation
        // return tab(n,fee,prices);
        // Optimization
        return opti(n,fee,prices);
    }
};

int main()
{
    int n,fee;
    cin>>n>>fee;
    vector<int> prices(n);
    for(int i = 0;i<n;i++)
    {
        cin>>prices[i];
    }
    Solution obj;
    int ans = obj.maximumProfit(n,fee,prices);
    cout<<ans<<endl;
    return 0;
}