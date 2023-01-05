// Problem
/*
We are given an array ‘ARR’ of size ‘N’ and a number ‘Target’. Our task is to build an expression from the given array where we can place a ‘+’ or ‘-’ sign in front of an integer. We want to place a sign in front of every integer of the array and get our required target. We need to count the number of ways in which we can achieve our required target
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Recursion
    // Time Complexity : O(2^N)
    // Space Complexity : O(N)
    int recc(int index,int target,vector<int> &arr)
    {
        if(index == 0)
        {
            if(target == 0 && arr[0] == 0) return 2;
            if(target == 0 || arr[0] == target ) return 1;
            return 0;
        }
        int notTake = recc(index-1,target,arr);
        int take = 0;
        if(target>=arr[index]) take = recc(index-1,target-arr[index],arr);
        return take+notTake;
    }

    // Memoization
    // Time Complexity : O(N*K)
    // Space Complexity : O(N*k) + O(K)
    int memo(int index,int target,vector<int> &arr,vector<vector<int>> &dp)
    {
        if(index == 0)
        {
            if(target == 0 && arr[0] == 0) return 2;
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
    // Time Complexity : O(N*K)
    // Space Complexity : O(N*K)
    int tab(int n,int target,vector<int> &arr)
    {
        vector<vector<int>>dp(n,vector<int>(target+1,0));
        if(arr[0] == 0) dp[0][arr[0]]= 2;
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
    // Space Complexity : O(K)
    int opti(int n,int target,vector<int> &arr)
    {
        vector<int> prev(target+1,0),curr(target+1,0);
        if(arr[0] == 0) prev[arr[0]] = 2;
        else prev[0] = 1;
        if(arr[0]!=0 && target>=arr[0]) prev[arr[0]] = 1;
        for(int i = 1;i<n;i++)
        {
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
    int targetSum(int n,int k,vector<int> &arr)
    {
        int totalSum = 0 ;
        for(int i = 0;i<n;i++) totalSum+=arr[i];
        if((totalSum-k)%2 == 1) return 0;
        if((totalSum-k) <0) return 0;
        int s2 = (totalSum-k)/2;
        /*
        // Recursion
        return recc(n-1,s2,arr);
        */
       /*
       // Memoization
       vector<vector<int>> dp(n,vector<int> (s2+1,-1));
       return memo(n-1,s2,arr,dp);
       */
      /*
      // Tabulation
      return tab(n,s2,arr);
      */
     // Optimization
     return opti(n,s2,arr);
    }
};
int main()
{
    int n,k;
    cin>>n>>k;
    vector<int>arr(n,0);
    for(int i = 0;i<n;i++)
    {
        cin>>arr[i];
    }
    Solution obj;
    int ans = obj.targetSum(n,k,arr);
    cout<<ans<<endl;
    return 0;
}