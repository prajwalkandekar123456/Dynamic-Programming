// Problem 
/*
Given an array arr, partition it into two subsets(possibly empty) such that their union is the original array. Let the sum of the element of these two subsets be S1 and S2. 

Given a difference d, count the number of partitions in which S1 is greater than or equal to S2 and the difference S1 and S2 is equal to d. since the answer may be large return it modulo 109 + 7.

Example 1:

Input:
n = 4, d = 3
arr[] =  { 5, 2, 6, 4}
Output:
1
Explanation:
There is only one possible partition of this array. Partition : {6, 4}, {5, 2}. The subset difference between subset sum is: (6 + 4) - (5 + 2) = 3.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Recursion
    // Time complexity : O(2^n)
    // Space complexity : O(N)

    int recc(int index,int target,vector<int> &arr)
    {
        if(index == 0)
        {
            if(target == 0 && arr[0] == 0) return 2;
            if(target == 0 || target == arr[0]) return 1;
            return 0;

        }
        int notPick = recc(index-1,target,arr);
        int pick = 0;
        if(target>=arr[index]) pick = recc(index-1,target - arr[index],arr);
        return pick + notPick;
    }
    // Memoization
   // Time Complexity : O(N*M)
   // Space Complexity : O(N*M) + O(N)

   int memo(int index,int target,vector<int> &arr,vector<vector<int>> &dp)
   {
        if(index == 0)
        {
            if(target  == 0 && arr[0] == 0) return 2;
            if(target == 0 || target == arr[0]) return 1;
            return 0;
        }
        if(dp[index][target]!=-1) return dp[index][target];
        int notTake = memo(index-1,target,arr,dp);
        int take = 0;
        if(target>=arr[index]) take = memo(index-1,target-arr[index],arr,dp);
        return dp[index][target] = take+notTake;
   }

   // Tabulation
   // Time Complexity: O(N*K)
   // Space Complexity : O(N*K)
   int tab(int n,int target,vector<int> &arr)
   {
        vector<vector<int>> dp(n+1,vector<int>(target+1,0));
        if(arr[0] == 0) dp[0][arr[0]] = 2;
        else dp[0][0] = 1;
        if(arr[0]!=0 && arr[0]<=target) dp[0][arr[0]] = 1;
        for(int i = 1;i<n;i++)
        {
            for(int j = 0;j<=target;j++)
            {
                int notTake = dp[i-1][j];
                int take = 0;
                if(j>=arr[i]) take = dp[i-1][j-arr[i]];
                dp[i][j] = take+notTake;
            }
        }
        return dp[n-1][target];

   }
   // Optimization
   // Time Complexity : O(N*K)
   // Space  Complexity : O(K)
   int opti(int n,int target,vector<int> &arr)
   {
        vector<int> prev(target+1,0);
        if(arr[0] == 0) prev[arr[0]] = 2;
        else prev[0] = 1;
        if(arr[0]!=0 && arr[0]<=target) prev[arr[0]] = 1;
        for(int i = 1;i<n;i++)
        {
            vector<int> curr(target+1,0);
            for(int j = 0;j<=target;j++)
            {
                int notTake = prev[j];
                int take = 0;
                if(j>=arr[i]) take = prev[j-arr[i]];
                curr[j] = take+notTake;
            }
            prev = curr;
        }
        return prev[target];
   }
public:
    int findWays(int n,vector<int> &arr,int d)
    {
        int totalSum = 0;
        for(int i = 0;i<n;i++)
        {
            totalSum+=arr[i];
        }
        int s2 = (totalSum-d)/2;
        if((totalSum - d)<0) return 0;
        if((totalSum -d)%2 == 1) return 0;
        // int ans = recc(n-1,s2,arr);
        vector<vector<int>> dp(n,vector<int>(s2+1,-1));
        // int ans = memo(n-1,s2,arr,dp);
        // int ans = tab(n,s2,arr);
        int ans = opti(n,s2,arr);
        return ans;
   }
   
};
int main()
{
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i = 0;i<n;i++)
    {
        cin>> arr[i];
    }
    int k;
    cin>>k;
    Solution obj;
    int ans = obj.findWays(n,arr,k);
    cout<<ans<<endl;
    return 0;
}