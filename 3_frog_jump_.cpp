// Problem

/*
 Geek wants to climb from the 0th stair to the (n-1)th stair. At a time the Geek can climb either one or two steps. A height[N] array is also given. Whenever the frog jumps from stair i to stair j, the energy consumed in the jump is abs(height[i]- height[j]), where abs() means the absolute difference. return the minimum energy that can be used by the Geek to jump from stair 0 to stair N-1.

Example:
Input:
n = 4
height = {10 20 30 10}
Output:
20
Explanation:
Geek jump from 1st to 2nd stair(|20-10| = 10 energy lost).
Then a jump from the 2nd to the last stair(|10-20| = 10 energy lost).
so, total energy lost is 20 which is the minimum.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Recursion
    // Time Complexity :
    // Space complexity :
    int recc(int index,vector<int> & heights)
    {
        if(index == 0) return 0;
        int left = recc(index-1,heights)+abs(heights[index-1]-heights[index]);
        int right = INT_MAX;
        if(index>1) right = recc(index-2,heights)+abs(heights[index-2]-heights[index]);
        return min(left,right);
    }

    // Memoization
    // Time Complexity : O(N)
    // Space Complexity : O(N) + O(N)

    int memo(int index,vector<int> &heights,vector<int> &dp)
    {
        if(index == 0) return 0;
        if(dp[index]!=-1) return dp[index];
        int left = memo(index-1,heights,dp)+abs(heights[index-1]-heights[index]);
        int right = INT_MAX;
        if(index>1) right = memo(index-2,heights,dp)+abs(heights[index-2]-heights[index]);
        return dp[index] = min(left,right);
    }

    // Tabulation
    // Time Complexity : O(N)
    // Space Complexity : O(N)

    int tab(int n,vector<int> &heights)
    {
        vector<int> dp(n,0);
        dp[0] = 0;
        for(int i = 1;i<n;i++)
        {
            int fs = dp[i-1]+abs(heights[i-1]-heights[i]);
            int ss = INT_MAX;
            if(i>1) ss = dp[i-2]+abs(heights[i-2]-heights[i]);
            dp[i] = min(ss,fs);
        }
        return dp[n-1];
    }

    // Optimization
    // Time Complexity : O(N)
    // SPace Complexity : O(1)

    int opti(int n,vector<int> &heights)
    {
        int prev2 = 0;
        int prev = 0;
        for(int i = 1;i<n;i++)
        {
            int fs = prev+abs(heights[i-1]-heights[i]);
            int ss = INT_MAX;
            if(i>1) ss = prev2+abs(heights[i-2] - heights[i]);
            int curr = min(fs,ss);
            prev2 = prev;
            prev = curr;
        }
        return prev;
    }
public:
    int minimumEnergy(int n,vector<int> &heights)
    {
        /*
        // Recursion
        int ans1 = recc(n-1,heights);
        return ans1;
        */
       /*
       // Memoization
       vector<int> dp(n+1,-1);
       int ans = memo(n-1,heights,dp);
       return ans;
       */
      /*
      // Tabulation
      int ans = tab(n,heights);
      return ans;
      */
     
     // Optimization
     int ans = opti(n,heights);
     return ans;
    }
};
int main()
{
    int n;
    cin>>n;
    vector<int> heights(n);
    for(int i = 0;i<n;i++)
    {
        cin>>heights[i];
    }
    Solution obj;
    int ans = obj.minimumEnergy(n,heights);
    cout<<ans<<endl;   
    return 0;

}