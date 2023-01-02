// Problem
/*
We are given an array ‘ARR’ with N positive integers. We need to partition the array into two subsets such that the absolute difference of the sum of elements of the subsets is minimum.

We need to return only the minimum absolute difference of the sum of elements of the two partitions.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Tabulation
    // Time Complexity : O(N*K) + O(K) + O(K)
    // Space Complexity : O(N*K)
    int tab(int n,int k,vector<int> &arr)
    {
        vector<vector<bool>> dp(n,vector<bool>(k+1,false));
        for(int i = 0;i<n;i++)
        {
            dp[i][0] = true;
        }
        if(arr[0]<=k) dp[0][arr[0]] = true;
        for(int i = 1;i<n;i++)
        {
            for(int target = 0;target<=k;target++)
            {
                bool notTake = dp[i-1][target];
                bool take = false;
                if(target>=arr[i]) take = dp[i-1][target-arr[i]];
                dp[i][target] = take || notTake;
            }
        }
        int mini = 1e9;
        for(int s1 = 0;s1<=k;s1++)
        {
            if(dp[n-1][s1] == true){
                int s2 = k-s1;
                mini = min(mini,abs(s1-s2));
            }
        }
        return mini;
    }

    // Optimization
    // Time Complexity : O(N*K)
    // Space Complexity : O(K)
    int opti(int n,int k,vector<int>&arr)
    {
        vector<bool> prev(k+1,false);
        prev[0] = true;
        for(int i = 1;i<n;i++)
        {
            vector<bool> curr(k+1,false);
            for(int target = 0;target<=k;target++)
            {
                bool notTake = prev[target];
                bool take = false;
                if(target>= arr[i]) take = prev[target-arr[i]];
                curr[target] = take || notTake;
            }
            prev = curr;
        }
        int mini = 1e9;
        for(int s1 = 0;s1<=k;s1++)
        {
            if(prev[s1] == true){
                int s2 = k-s1;
                mini = min(mini,abs(s1-s2));
            }
        }
        return mini;
    }
public:
    int minSubsetSumDifference(int n,vector<int> &arr)
    {
        int totalSum = 0;
        for(int i = 0;i<n;i++) totalSum+=arr[i];
        // return tab(n,totalSum,arr); // Tabulation
        // Space Optimization
        return opti(n,totalSum,arr);
    }
};

int main()
{
    int n;
    cin>>n;
    vector<int>arr(n);
    for(int i = 0;i<n;i++)
    {
        cin>>arr[i];
    }
    Solution obj;
    int ans = obj.minSubsetSumDifference(n,arr);
    cout<<ans<<endl;
    return 0;
}