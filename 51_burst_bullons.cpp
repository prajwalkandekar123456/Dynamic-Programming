// Problem
/*
ou are given N balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array arr. You are asked to burst all the balloons.
If you burst the ith balloon, you will get arr[ i - 1 ] * arr[ i ] * arr[ i + 1] coins. If i - 1, or i + 1 goes out of the bounds of the array, consider it as if there is a balloon with a 1 painted on it.
Return the maximum coins you can collect by bursting the balloons wisely.

Example 1:

Input:
N = 4
arr[ ] = {3, 1, 5, 8}
Output: 167
Explanation: 
arr[ ] = {3, 1, 5, 8}  - - > {3, 5, 8} - - > {3, 8} - - > { 8} - -> { }
coins = 3 *1 *5,      +      3*5*8     +   1*3*8   +  1*8*1   = 167
 
 

Example 2:

Input:
N = 2
arr[ ] = {1, 10}
Output: 20
*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
private:
// Recursion
// Time Complexity : Exponential
// Space Complexity : O(N)
    int recc(int i,int j,vector<int> &nums,int n)
    {
        if(i>j) return 0;
        int maxi = INT_MIN;
        for(int k = i;k<=j;k++)
        {
            int cost = nums[i-1]*nums[k]*nums[j+1]+recc(i,k-1,nums,n)+recc(k+1,j,nums,n);
            maxi = max(maxi,cost);
        }
        return maxi;
    }
    // Memoization
    // Time Complexity : O(N*N*N)
    // Space COmplexity : O(N*N)+O(N)
    int memo(int i,int j,vector<int> &nums,vector<vector<int>> &dp)
    {
        if(i>j) return 0;
        if(dp[i][j]!=-1) return dp[i][j];
        int maxi = INT_MIN;
        for(int k = i;k<=j;k++)
        {
            int cost = nums[i-1]*nums[k]*nums[j+1]+memo(i,k-1,nums,dp)+memo(k+1,j,nums,dp);
            maxi = max(maxi,cost);
        }
        return dp[i][j] = maxi;
    }
    // Tabulation
    // Time Complexity : O(N*N*N)
    // Space Complexity : O(N*N)
    int tab(int n,vector<int> &nums)
    {
        vector<vector<int>> dp(n+2,vector<int>(n+2,0));
        for(int i = n;i>=1;i--)
        {
            for(int j = 1;j<=n;j++)
            {
                if(i>j) continue;
                int maxi = INT_MIN;
                for(int k = i;k<=j;k++)
                {
                    int cost = nums[i-1]*nums[k]*nums[j+1]+dp[i][k-1]+dp[k+1][j];
                    maxi = max(maxi,cost);
                }
                dp[i][j] = maxi;
            }
        }
        return dp[1][n];
    }
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(),1);
        nums.push_back(1);
        // Recursion
        // return recc(1,n,nums,n);
        vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
        // Memoization
        // return memo(1,n,nums,dp);
        // Tabulation
        return tab(n,nums);
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
    int ans = obj.maxCoins(arr);
    cout<<ans<<endl;
    return 0;
}