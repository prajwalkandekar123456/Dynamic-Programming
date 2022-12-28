// Problem
/*
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

 

Example 1:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
/*
    //Recursion
    // Time Complexity : 2^N
    // Space Complexity : O(N)+O(N)
    int recc(int index,vector<int> &arr)
    {
        if(index == 0) return arr[index];
        if(index<0) return 0;
        int pick = arr[index]+ recc(index-2,arr);
        int notPick = 0 + recc(index-1,arr);
        return max(pick,notPick);
    }
    */
/*
   // Memoization
   // Time Complexity : O(N)
   // Space Complexity : O(N)+O(N)

   int memo(int index,vector<int> &arr,vector<int> &dp)
   {
        if(index == 0) return arr[index];
        if(index<0) return 0;
        if(dp[index]!=-1) return dp[index];
        int pick = arr[index]+memo(index-2,arr,dp);
        int notPick = 0 + memo(index-1,arr,dp);
        return dp[index] = max(pick,notPick);
   }
*/

/*
    //Tabulation
    // Time Complexity : O(N)
    // Space Complexity : O(N)
    int tab(int n,vector<int> &arr)
    {
        vector<int> dp(n,0);
        dp[0] = arr[0];
        for(int i = 1;i<n;i++)
        {
            int pick = arr[i];
            if(i>1) pick+=dp[i-2];
            int notPick = 0 + dp[i-1];
            dp[i] = max(pick,notPick);
        }
        return dp[n-1];
    }
    */

   //Optimization
   // Time Complexity : O(N)
   // Space Complexity :O(1)
   int opti(int n,vector<int> &arr)
   {
        int prev2 = 0;
        int prev = arr[0];
        for(int i = 1;i<n;i++)
        {
            int pick = arr[i];
            if(i>1) pick+=prev2;
            int notPick = 0+prev;
            int curr = max(pick,notPick);
            prev2 = prev;
            prev = curr;
        }
        return prev;
   }
public:
    int houseRobber(int n,vector<int> &arr)
    {
        if(n == 1) return arr[0];
        vector<int> temp1,temp2;
        for(int i = 0;i<n;i++)
        {
            if(i!=0) temp1.push_back(arr[i]);
            if(i!=n-1) temp2.push_back(arr[i]);
        }
        int m = temp1.size();
        int p = temp2.size();
        /*
        //Recursion
        int ans =  max(recc(m-1,temp1),recc(p-1,temp2));
        return ans;
        */
       /*
       //memoization
       vector<int> dp1(m,-1),dp2(p,-1);
       int ans = max(memo(m-1,temp1,dp1),memo(p-1,temp2,dp2));
       return ans;
       */
      /*
      //tabulation
      int ans = max(tab(m,temp1),tab(p,temp2));
      return ans;
      */
     //Optimization
     int ans = max(opti(m,temp1),opti(p,temp2));
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
        cin>>arr[i];
    }
    Solution obj;
    int ans = obj.houseRobber(n,arr);
    cout<<ans<<endl;
    return 0;
}