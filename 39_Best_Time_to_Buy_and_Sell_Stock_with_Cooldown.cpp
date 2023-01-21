// problem
/*
We are given an array Arr[] of length n. It represents the price of a stock on ‘n’ days. The following guidelines need to be followed:

We can buy and sell the stock any number of times.
In order to sell the stock, we need to first buy it on the same or any previous day.
We can’t buy a stock again after buying it once. In other words, we first buy a stock and then sell it. After selling we can buy and sell again. But we can’t sell before buying and can’t buy before selling any previously bought stock.
We can’t buy a stock on the very next day of selling it. This is the cooldown clause.
*/
#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
// Recursion
// Time Complexity : exponential
// Space COmplexity : O(N)
int recc(int index,int buy,vector<int> &prices,int n)
{
    if(index >= n) return 0;
    if(buy == 1)
    {
        return max(-prices[index]+recc(index+1,0,prices,n),recc(index+1,1,prices,n));
    }
    else {
        return max(prices[index] + recc(index+2,1,prices,n),recc(index+1,0,prices,n));
    }
}
// Memoization
// Time Complexity : O(N*M)
// Space Complexity : O(N*M) + O(N+M)
int memo(int index,int buy,vector<int> &prices,int n,vector<vector<int>> &dp)
{
    if(index>=n) return 0;
    if(dp[index][buy]!=-1) return dp[index][buy];
    if(buy)
    {
        return dp[index][buy] = max(-prices[index]+memo(index+1,0,prices,n,dp),memo(index+1,1,prices,n,dp));
    }
    else{
        return dp[index][buy] = max(prices[index]+memo(index+2,1,prices,n,dp),memo(index+1,0,prices,n,dp));
    }
}
// Tabulation
// Time Complexity : O(N*M)
// Space Compelxity : O(N*M)
int tab(int n,vector<int> &prices)
{
    vector<vector<int>> dp(n+2,vector<int>(2,0));
    for(int i = n-1;i>=0;i--)
    {
        for(int j = 0;j<=1;j++)
        {
            if(j)
            {
                dp[i][j] = max(-prices[i]+dp[i+1][0],dp[i+1][1]);
            }
            else{
                dp[i][j] = max(prices[i]+dp[i+2][1],dp[i+1][0]);
            }
        }
    }
    return dp[0][1];
}
public:
int stockProfit(vector<int> &prices){
    int n = prices.size();
//     return recc(0,1,prices,n);
    vector<vector<int>> dp(n,vector<int>(2,-1));
//     return memo(0,1,prices,n,dp);
    return tab(n,prices);
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
    int ans = obj.stockProfit(arr);
    cout<<ans<<endl;
    return 0;
}