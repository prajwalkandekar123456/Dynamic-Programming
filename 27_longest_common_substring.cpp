// Problem
/*
Given two strings. The task is to find the length of the longest common substring.


Example 1:

Input: S1 = "ABCDGH", S2 = "ACDGHR", n = 6, m = 6
Output: 4
Explanation: The longest common substring
is "CDGH" which has length 4.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
    private:
    // Tabulation
    // Time Complexity : O(N*M)
    // Space Complexity : O(N*M)
    int tab(string &s1,string &s2)
    {
        int n = s1.size();
        int m = s2.size();
        vector<vector<int>> dp(n+1,vector<int>(m+1,0));
        for(int i = 0;i<=n;i++) dp[i][0] = 0;
        for(int j = 0;j<=m;j++) dp[0][j] = 0;
        int ans = 0;
        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=m;j++)
            {
                if(s1[i-1] == s2[j-1])
                {
                    dp[i][j] = 1+dp[i-1][j-1];
                    ans = max(ans,dp[i][j]);
                }
                else dp[i][j] = 0;
            }
        }
        return ans;
    }

    // Space Optimization
    // Time Complexity : O(N*M)
    // Space COmplexity : O(M)
    int opti(string &s1,string &s2)
    {
        int n = s1.size();
        int m = s2.size();
        vector<int> prev(m+1,0),curr(m+1,0);
        int ans = 0;
        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=m;j++)
            {
                if(s1[i-1] == s2[j-1])
                {
                    curr[j] = 1+prev[j-1];
                    ans = max(ans,curr[j]);
                }
                else curr[j] = 0;
            }
            prev = curr;
        }
        return ans;
    }
    public:
    int LCS(string &s1,string &s2)
    {
        // Tabulation
        return tab(s1,s2);
        // Optimization
        return opti(s1,s2);
    }
};
int main()
{
    string s1,s2;
    cin>>s1>>s2;
    Solution obj;
    int ans = obj.LCS(s1,s2);
    cout<<ans<<endl;
    return 0;
}