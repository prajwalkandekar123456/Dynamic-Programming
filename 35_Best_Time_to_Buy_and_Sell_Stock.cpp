// Problem
/*
We are given an array Arr[] of length n. It represents the price of a stock on ‘n’ days. The following guidelines need to be followed:

We can buy and sell a stock only once.
We can buy and sell the stock on any day but to sell the stock, we need to first buy it on the same or any previous day.
We need to tell the maximum profit one can get by buying and selling this stock.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
// Time Complexity : O(N)
// Space Complexity : O(1)
    int maximumProfit(vector<int> &price)
    {
        int n = price.size();
        int maxProfit = 0;
        int mini = price[0];
        for(int i = 0;i<n;i++)
        {
            int currProfit = price[i]-mini;
            maxProfit = max(maxProfit,currProfit);
            mini = min(mini,price[i]);
        }
        return maxProfit;
    }
};
int main()
{
    int n;
    cin>>n;
    vector<int> prices(n);
    for(int i = 0;i<n;i++)
    {
        cin>>prices[i];
    }
    Solution obj;
    int ans = obj.maximumProfit(prices);
    cout<<ans<<endl;
    return 0;
}