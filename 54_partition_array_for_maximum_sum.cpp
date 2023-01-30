// Problem
/*
Given an integer array arr, partition the array into (contiguous) subarrays of length at most k. After partitioning, each subarray has their values changed to become the maximum value of that subarray.

Return the largest sum of the given array after partitioning. Test cases are generated so that the answer fits in a 32-bit integer.

 

Example 1:

Input: arr = [1,15,7,9,2,5,10], k = 3
Output: 84
Explanation: arr becomes [15,15,15,9,10,10,10]
Example 2:

Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
Output: 83
Example 3:

Input: arr = [1], k = 1
Output: 1
*/
#include<bits/stdc++.h>
using namespace std;
class Solution {
private:
// Recursion
// Time Complexity : Exponential
// Space COmplexity : O(N)
 int recc(int i,int k,int n,vector<int> &arr)
 {
     if(i == n) return 0;
     int maxAns = INT_MIN;
     int maxi = INT_MIN;
     int len = 0;
     for(int j = i;j<min(n,i+k);j++)
     {
         maxi = max(maxi,arr[j]);
         len++;
         int sum = len*maxi + recc(j+1,k,n,arr);
         maxAns = max(maxAns,sum);
     }
     return maxAns;
 }
 // Memoization
 // Time COmplexity : O(N*K)
 // Space COmplexity : O(N*K)+O(N)
 int memo(int i,int k,int n,vector<int> &arr,vector<int> &dp)
 {
     if(i == n) return 0;
     if(dp[i]!=-1) return dp[i];
     int maxi = INT_MIN;
     int maxAns = INT_MIN;
     int len = 0;
     for(int j = i;j<min(n,i+k);j++)
     {
         len++;
         maxi = max(maxi,arr[j]);
         int sum = len*maxi + memo(j+1,k,n,arr,dp);
         maxAns = max(maxAns,sum);
     }
     return dp[i] = maxAns;
 }
 // Tabulation
 // Time Complexity: O(N*K)
 // Space COmplexity : O(N*K)
 int tab(int n,int k,vector<int> &arr)
 {
     vector<int> dp(n+1,0);
     for(int i = n-1;i>=0;i--)
     {
         int maxi = INT_MIN;
         int maxAns = INT_MIN;
         int len = 0;
         for(int j = i;j<min(n,i+k);j++)
         {
             len++;
             maxi = max(maxi,arr[j]);
             int sum = len*maxi+dp[j+1];
             maxAns = max(maxAns,sum);
         }
         dp[i] = maxAns;
     }
     return dp[0];
 }
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n = arr.size();
        // return recc(0,k,n,arr);
        vector<int> dp(n,-1);
        // return memo(0,k,n,arr,dp);
        return tab(n,k,arr);
    }
};
int main()
{
    int n,k;
    cin>>n>>k;
    vector<int> arr(n);
    for(int i = 0;i<n;i++)
    {
        cin>>arr[i];
    }
    Solution obj;
    int ans = obj.maxSumAfterPartitioning(arr,k);
    cout<<ans<<endl;
    return 0;
}