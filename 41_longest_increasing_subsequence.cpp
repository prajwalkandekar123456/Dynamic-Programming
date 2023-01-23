// Problem
/*
Given an array of integers, find the length of the longest (strictly) increasing subsequence from the given array.

Example 1:

Input:
N = 16
A[]={0,8,4,12,2,10,6,14,1,9,5
     13,3,11,7,15}
Output: 6
Explanation:Longest increasing subsequence
0 2 6 9 13 15, which has length 6
Example 2:

Input:
N = 6
A[] = {5,8,3,7,9,1}
Output: 3
Explanation:Longest increasing subsequence
5 7 9, with length 3
*/

#include<bits/stdc++.h>
using namespace std;
class Solution{
private:
    // Recursion
    // Time Complexity : 2^N
    // Space Complexity : O(N)
    int recc(int index,int prev,int n,int arr[])
    {
        if(index == n) return 0;
        int notTake = recc(index+1,prev,n,arr);
        int take = 0;
        if(prev == -1 || arr[index]>arr[prev]){
            take = 1+recc(index+1,index,n,arr);
        }
        return max(take,notTake);
        
    }
    // Memoization
    // Time Complexity : O(N*M)
    // Space Complexity : O(N*M)+O(N+M)
    int memo(int index,int prev,int n,int arr[],vector<vector<int>> &dp)
    {
        if(index == n) return 0;
        if(dp[index][prev+1]!=-1) return dp[index][prev+1];
        int notTake = memo(index+1,prev,n,arr,dp);
        int take = 0;
        if(prev == -1 || arr[index]>arr[prev])
        {
            take = 1+memo(index+1,index,n,arr,dp);
        }
        return dp[index][prev+1] = max(take,notTake);
    }
    // Tabulation
    // Time Complexity : O(N*M)
    // Space Complexity : O(N*N)
    int tab(int n,int arr[])
    {
        vector<vector<int>> dp(n+1,vector<int>(n+1,0));
        for(int i = n-1;i>=0;i--)
        {
            for(int j = i-1;j>=-1;j--)
            {
                int notTake = dp[i+1][j+1];
                int take = 0;
                if(j == -1 || arr[i]>arr[j])
                {
                    take = 1+dp[i+1][i+1];
                }
                dp[i][j+1] = max(take,notTake);
            }
        }
        return dp[0][0];
    }
    // Optimization
    // Time Complexity : O(N*N)
    // Space Complexity : O(N+N)
    int opti(int n,int arr[])
    {
        vector<int> after(n+1,0),curr(n+1,0);
        for(int i = n-1;i>=0;i--)
        {
            for(int j = i-1;j>=-1;j--)
            {
                int notTake = after[j+1];
                int take = 0;
                if(j == -1 || arr[i]>arr[j])
                {
                    take = 1+after[i+1];
                }
                curr[j+1] = max(take,notTake);
            }
            after = curr;
        }
        return after[0];
    }
public:
    int longestSubsequence(int n,int arr[])
    {
        // Recursion
        // return recc(0,-1,n,arr);
        // Memoization
        vector<vector<int>> dp(n,vector<int>(n+1,-1));
        // return memo(0,-1,n,arr,dp);
        // return tab(n,arr);
        return opti(n,arr);
    }
};
int main()
{
    int n;
    cin>>n;
    int arr[n];
    for(int i = 0;i<n;i++)
    {
        cin>>arr[i];
    }   
    Solution obj;
    int ans = obj.longestSubsequence(n,arr);
    cout<<ans<<endl;
    return 0;
}