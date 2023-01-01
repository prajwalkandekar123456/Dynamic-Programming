// Problem
/*
We are given an array ‘ARR’ with N positive integers. We need to find if there is a subset in “ARR” with a sum equal to K. If there is, return true else return false.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Recursion
    // Time COmplexity : O(2^N)
    // Space Complexity : O(N)
    bool recc(int index,int target,vector<int> &arr)
    {
        if(target == 0) return true;
        if(index == 0) return arr[index] == target;
        bool notTake = recc(index-1,target,arr);
        bool take = false;
        if(target>=arr[index])
        {
            take = recc(index-1,target-arr[index],arr);
        }
        return take||notTake;
    }

    // Memoization
    // Time Complexity : O(N*K)
    // Space Complexity : O(N*K)+O(N)
    bool memo(int index,int target,vector<int> &arr,vector<vector<int>> &dp)
    {
        if(target == 0) return true;
        if(index == 0) return arr[index]==target;
        if(dp[index][target]!=-1) return dp[index][target];
        bool notTake = memo(index-1,target,arr,dp);
        bool take = false;
        if(target>=arr[index])
        {
            take = memo(index-1,target-arr[index],arr,dp);
        }
        return dp[index][target] = take || notTake;
    }

    // Tabulation
    // Time Complexity : O(N*K)
    // Space Complexity : O(N*K)
    bool tab(int n,int k,vector<int> &arr)
    {
        vector<vector<bool>> dp(n,vector<bool>(k+1,false));
        for(int i=0; i<n; i++){
            dp[i][0] = true;
         }
    
        if(arr[0]<=k)
            dp[0][arr[0]] = true;
        for(int index = 1;index<n;index++)
        {
            for(int target = 1;target<=k;target++)
            {
                bool notTake = dp[index-1][target];
                bool take = false;
                if(target>=arr[index])
                {
                    take = dp[index-1][target-arr[index]];
                }
                dp[index][target] = take||notTake;
            }
        }
        return dp[n-1][k];
    }

    // Space Optimization
    // Time Complexity :O(N*K)
    // Space COmplexity : O(N)
    int opti(int n,int k,vector<int> &arr)
    {
        vector<bool> prev(k+1,0);
        prev[0] = true;
        if(arr[0]<=k)
            prev[arr[0]] = true;
        for(int index = 1;index<n;index++)
        {
            vector<bool> curr(k+1,false);
            curr[0] = true;
            for(int target = 1;target<=k;target++)
            {
                bool notTake = prev[target];
                bool take = false;
                if(target>=arr[index])
                {
                    take = prev[target-arr[index]];
                }
                curr[target] = take || notTake;
            }
            prev = curr;
        }
        return prev[k];
    }
public:
    bool subsetSumToK(int n,int k,vector<int> &arr)
    {
        /*
        // Recursion
        return recc(n-1,k,arr);
        */
       /*
       // Memoization
       vector<vector<int>> dp(n,vector<int>(k+1,-1));
       return memo(n-1,k,arr,dp);
        */
       /*
       // Tabulation
       return tab(n,k,arr);
       */
      // Optimization
      return opti(n,k,arr);
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
    cout<<obj.subsetSumToK(n,k,arr)<<endl;
    return 0;
}