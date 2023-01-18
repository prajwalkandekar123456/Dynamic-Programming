// Problem
/*
We are given an array Arr[] of length n. It represents the price of a stock on ‘n’ days. The following guidelines need to be followed:

We can buy and sell the stock any number of times.
In order to sell the stock, we need to first buy it on the same or any previous day.
We can’t buy a stock again after buying it once. In other words, we first buy a stock and then sell it. After selling we can buy and sell again. But we can’t sell before buying and can’t buy before selling any previously bought stock.

*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
// Recursiom
// Time Complexity : exponential
// SPace Complexity : O(N)
long recc(int index1,int buy,long *price,int n)
{
    if(index1 == n) return 0;
    long profit = 0;
    if(buy)
    {
        profit = max(-price[index1]+recc(index1+1,0,price,n),recc(index1+1,1,price,n));
    }
    else{
        profit = max(price[index1]+recc(index1+1,1,price,n),recc(index1+1,0,price,n));
    }
    return profit;
}
// Memoization
// Time Complexity : O(N*M)
// Space Complexity : O(N*M)+O(N+M)
long memo(int index,int buy,long *price,int n,vector<vector<long>> &dp)
{
    if(index == n) return 0;
    if(dp[index][buy] !=-1) return dp[index][buy];
    long profit = 0;
    if(buy)
    {
        profit = max(-price[index]+memo(index+1,0,price,n,dp),memo(index+1,1,price,n,dp));
    }
    else{
        profit = max(price[index]+memo(index+1,1,price,n,dp),memo(index+1,0,price,n,dp));
    }
    return dp[index][buy] = profit;
}
// Tabulation
// Time Complexity : O(N*M)
// Space COmplexity : O(N*M)
long tab(long* price,int n)
{
    vector<vector<long>> dp(n+1,vector<long>(2,0));
    dp[n][0] = dp[n][1] = 0;
    for(int i = n-1;i>=0;i--)
    {
        for(int j = 0;j<=1;j++)
        {
            long profit = 0;
            if(j)
            {
                profit = max(-price[i]+dp[i+1][0],dp[i+1][1]);
            }
            else{
                profit = max(price[i]+dp[i+1][1],dp[i+1][0]);
            }
            dp[i][j] = profit;
        }
    }
    return dp[0][1];
}
// Optimization
// Time COmplexity : O(N*M)
// Space Complexity : O(2)
long opti(long* price,int n)
{
    vector<long> ahead(2,0),curr(2,0);
    ahead[0] = ahead[1] = 0;
    for(int i = n-1;i>=0;i--)
    {
        for(int j = 0;j<=1;j++)
        {
            long profit = 0;
            if(j)
            {
                profit = max(-price[i]+ahead[0],ahead[1]);
            }
            else{
                profit = max(price[i]+ahead[1],ahead[0]);
            }
            curr[j] = profit;
        }
        ahead = curr;
    }
    return curr[1];
}
public:
long getMaximumProfit(long *values, int n)
{
//     return recc(0,1,values,n);
    vector<vector<long>> dp(n,vector<long>(2,-1));
//     return memo(0,1,values,n,dp);
//     return tab(values,n);
    return opti(values,n);
}
};
int main()
{
    int n;
    cin>>n;
    long *prices;
    for(int i = 0;i<n;i++)
    {
        cin>>prices[i];
    }
    Solution obj;
    int ans = obj.getMaximumProfit(prices,n);
    cout<<ans<<endl;
    return 0;
}