// Problem
/*
Given a wooden stick of length n units. The stick is labelled from 0 to n. For example, a stick of length 6 is labelled as follows:


Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.

You should perform the cuts in order, you can change the order of the cuts as you wish.

The cost of one cut is the length of the stick to be cut, the total cost is the sum of costs of all cuts. When you cut a stick, it will be split into two smaller sticks (i.e. the sum of their lengths is the length of the stick before the cut). Please refer to the first example for a better explanation.

Return the minimum total cost of the cuts.

 

Example 1:


Input: n = 7, cuts = [1,3,4,5]
Output: 16
Explanation: Using cuts order = [1, 3, 4, 5] as in the input leads to the following scenario:

The first cut is done to a rod of length 7 so the cost is 7. The second cut is done to a rod of length 6 (i.e. the second part of the first cut), the third is done to a rod of length 4 and the last cut is to a rod of length 3. The total cost is 7 + 6 + 4 + 3 = 20.
Rearranging the cuts to be [3, 5, 1, 4] for example will lead to a scenario with total cost = 16 (as shown in the example photo 7 + 4 + 3 + 2 = 16).

*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Recursion
    // Time Complexity : Exponential
    // Space Complexity : O(N)
    int recc(int i,int j,vector<int> &cuts,int n)
    {
        if(i>j) return 0;
        int mini = 1e9;
        for(int k = i;k<=j;k++)
        {
            int cost = cuts[j+1]-cuts[i-1]+recc(i,k-1,cuts,n)+recc(k+1,j,cuts,n);
            mini = min(mini,cost);
        }
        return mini;
    }
    // Memoization
    // Time Complexity : O(N*N*N)
    // Space Complexity : O(N*N)+O(N)
    int memo(int i,int j,vector<int> &cuts,int n,vector<vector<int>> &dp)
    {
        if(i>j) return 0;
        int mini = 1e9;
        if(dp[i][j]!=-1) return dp[i][j];
        for(int k = i;k<=j;k++)
        {
            int cost = cuts[j+1]-cuts[i-1]+memo(i,k-1,cuts,n,dp)+memo(k+1,j,cuts,n,dp);
            mini = min(mini,cost);
        }
        return dp[i][j] = mini;
    }
    // Tabulation
    // Time Complexity : O(N*N*N)
    // Space Complexity : O(N*N)
    int tab(int n,int c,vector<int> &cuts)
    {
        vector<vector<int>> dp(c+2,vector<int> (c+2,0));
        for(int i = c;i>=1;i--)
        {
            for(int j = 1;j<=c;j++)
            {
                if(i>j) continue;
                int mini = 1e9;
                for(int k = i;k<=j;k++)
                {
                    int cost = cuts[j+1]-cuts[i-1]+dp[i][k-1]+dp[k+1][j];
                    mini = min(mini,cost);
                }
                dp[i][j] = mini;
            }
        }
        return dp[1][c];
    }
public:
    int minCost(int n,int c,vector<int> &cuts)
    {
        cuts.push_back(n);
        cuts.insert(cuts.begin(),0);
        sort(cuts.begin(),cuts.end());
        // Recursion
        // return recc(1,c,cuts,n);
        // Memoization
        vector<vector<int>> dp(c+1,vector<int>(c+1,-1));
        // return memo(1,c,cuts,n,dp);
        // Tabulation
        return tab(n,c,cuts);
    }
};
int main()
{
    int n,c;
    cin>>n>>c;
    vector<int> cuts(c);
    for(int i = 0;i<c;i++)
    {
        cin>> cuts[i];
    }    
    Solution obj;
    int ans = obj.minCost(n,c,cuts);
    cout<<ans<<endl;
    return 0;
}