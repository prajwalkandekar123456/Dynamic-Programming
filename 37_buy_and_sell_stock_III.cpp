// Problem
/*
We are given an array Arr[] of length n. It represents the price of a stock on ‘n’ days. The following guidelines need to be followed:

We can buy and sell the stock any number of times.
In order to sell the stock, we need to first buy it on the same or any previous day.
We can’t buy a stock again after buying it once. In other words, we first buy a stock and then sell it. After selling we can buy and sell again. But we can’t sell before buying and can’t buy before selling any previously bought stock.
We can do at most 2 transactions.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
// Recursion
// Time Complexity : exponential
// Space Complexity : O(N)
int recc(int index,int buy,vector<int> &prices,int cap,int n)
{
    if(cap == 0) return 0;
    if(index == n) return 0;
    if(buy){
        return max(-prices[index]+recc(index+1,0,prices,cap,n),recc(index+1,1,prices,cap,n));
    }
    else{
        return max(prices[index]+recc(index+1,1,prices,cap-1,n),recc(index+1,0,prices,cap,n));
    }
}
// Memoization
// Time Complexity : O(N*2*3)
// Space Complexity : O(N*2*3)+O(N+2+3)
int memo(int index,int buy,vector<int> &prices,int cap,int n,vector<vector<vector<int>>> &dp)
{
    if(cap == 0) return 0;
    if(index == n) return 0;
    if(dp[index][buy][cap]!=-1) return dp[index][buy][cap];
    if(buy)
    {
        return dp[index][buy][cap] = max(-prices[index]+memo(index+1,0,prices,cap,n,dp),memo(index+1,1,prices,cap,n,dp));
    }
    else{
        return dp[index][buy][cap] = max(prices[index]+memo(index+1,1,prices,cap-1,n,dp),memo(index+1,0,prices,cap,n,dp));
    }
}
// Tabulation
// Time Complexity : O(N*2*3)
// Space COmplexity : O(N*2*3)
int tab(int n,vector<int> &prices)
{
    vector<vector<vector<int>>> dp(n+1,vector<vector<int>>(2,vector<int>(3,0)));
    for(int i = n-1;i>=0;i--)
    {
        for(int buy = 0;buy<=1;buy++)
        {
            for(int cap = 1;cap<=2;cap++)
            {
                if(buy)
                {
                    dp[i][buy][cap] = max(-prices[i]+dp[i+1][0][cap],dp[i+1][1][cap]);
                }
                else{
                    dp[i][buy][cap] = max(prices[i]+dp[i+1][1][cap-1],dp[i+1][0][cap]);
                }
            }
        }
    }
    return dp[0][1][2];
    
}
// Time Complexity : O(N*2*3)
// SPace COmplexity : O(2*3)
int opti(int n,vector<int> &prices)
{
    vector<vector<int>> after(2,vector<int>(3,0));
    vector<vector<int>> curr(2,vector<int>(3,0));
    for(int i = n-1;i>=0;i--)
    {
        for(int buy = 0;buy<=1;buy++)
        {
            for(int cap = 1;cap<=2;cap++)
            {
                if(buy)
                {
                    curr[buy][cap] = max(-prices[i]+after[0][cap],after[1][cap]);
                }
                else{
                    curr[buy][cap] = max(prices[i]+after[1][cap-1],after[0][cap]);
                }
            }
            after = curr;
        }
    }
    return after[1][2];
    
}
public:
int maxProfit(vector<int>& prices, int n)
{
//     return recc(0,1,prices,2,n);
    vector<vector<vector<int>>> dp(n,vector<vector<int>>(2,vector<int>(3,-1)));
//     return memo(0,1,prices,2,n,dp);
//     return tab(n,prices);
    return opti(n,prices);
    
}

};
int main()
{
    int n;
    cin>>n;
    vector<int> prices(n);
    for(int i = 0;i<n;i++)
    {
        cin>> prices[i];
    }
    Solution obj;
    int ans = obj.maxProfit(prices,n);
    cout<<ans<<endl;
    return 0;
}
