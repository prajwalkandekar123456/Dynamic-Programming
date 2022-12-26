// Problem

/*
Given an array Arr of size N containing positive integers. Find the maximum sum of a subsequence such that no two numbers in the sequence should be adjacent in the array.

Example 1:

Input:
N = 6
Arr[] = {5, 5, 10, 100, 10, 5}
Output: 110
Explanation: If you take indices 0, 3
and 5, then Arr[0]+Arr[3]+Arr[5] =
5+100+5 = 110.
*/

// Time Complexity :
// Space Complexity :

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
/*
    // Recursion
    // Time Complexity : O(2^N)
    // Space Complexity : O(N)+O(N)
    int recc(int index,vector<int> &arr)
    {
        if(index == 0) return arr[index];
        if(index<1) return 0;
        int pick = arr[index]+recc(index-2,arr);
        int notPick = 0+recc(index-1,arr);
        return max(pick,notPick);
    }
*/

/*
    // Memoization
    //Time Complexity : O(N)
    // Space Complexity : O(N) + O(N)
    int memo(int index,vector<int> &arr,vector<int>&dp)
    {
        if(index == 0) return arr[index];
        if(index<0)return 0;
        if(dp[index]!=-1) return dp[index];
        int peak = arr[index]+memo(index-2,arr,dp);
        int notPeak = 0+memo(index-1,arr,dp);
        return dp[index] = max(peak,notPeak);
    }
*/

    // Tabulation
    // Time COmplexity : O(N)
    // Space Complexity : O(N)
    int tab(int n,vector<int> &arr)
    {
        vector<int> dp(n+1,-1);
        dp[0] = arr[0];
        for(int i=1;i<n;i++)
        {
            int peak = arr[i];
            if(i>1) peak+=dp[i-2];
            int notPeak = 0 + dp[i-1];
            dp[i] = max(peak,notPeak);
        }
        return dp[n-1];
    }
public:
    int findMaxSum(int n,vector<int> &arr)
    {
        /*
        //Recursion
        int ans = recc(n-1,arr);
        return ans;
        */
       /*
       // Memoization
       vector<int> dp(n,-1);
       int ans = memo(n-1 ,arr,dp);
       return ans;
       */
      // Tabulation
      int ans = tab(n,arr);
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
    Solution obj;
    int ans = obj.findMaxSum(n,arr);
    cout<<ans<<endl;
    return 0;
}