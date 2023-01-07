// Problem
/*
Given two sequences, find the length of longest subsequence present in both of them. Both the strings are of uppercase.

Example 1:

Input:
A = 6, B = 6
str1 = ABCDGH
str2 = AEDFHR
Output: 3
Explanation: LCS for input Sequences
“ABCDGH” and “AEDFHR” is “ADH” of
length 3.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Recursion
    // Time Complexity : O(2^N + 2^M)
    // Space Complexity : O(N+M)
    int recc(int index1,int index2,string s1,string s2)
    {
        if(index1<0 || index2<0)
        {
            return 0;
        }
        if(s1[index1] == s2[index2]) return 1+recc(index1-1,index2-1,s1,s2);
        return max(recc(index1-1,index2,s1,s2),recc(index1,index2-1,s1,s2));
    }
    // Memoization
    // Time Complexity : O(N*M)
    // Space COmplexity : O(N*M)+O(N+M)
    int memo(int index1,int index2,string &s1,string &s2,vector<vector<int>> &dp)
    {
        if(index1<0 || index2<0) return 0;
        if(dp[index1][index2]!=-1) return dp[index1][index2];
        if(s1[index1] == s2[index2]) return 1+memo(index1-1,index2-1,s1,s2,dp);
        else return max(memo(index1-1,index2,s1,s2,dp),memo(index1,index2-1,s1,s2,dp));
    }
    // Tabulation
    // Time Complexity : O(N*M)
    // Space Complexity : O(N*M)
    int tab(int n,int m,string s1,string s2)
    {
        vector<vector<int>> dp(n+1,vector<int>(m+1,-1));
        for(int i = 0;i<=n;i++) dp[i][0] = 0;
        for(int j = 0;j<=m;j++) dp[0][j] = 0;
        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=m;j++)
            {
                if(s1[i] == s2[j]) dp[i][j] = 1+dp[i-1][j-1];
                else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
        }
        return dp[n][m];
    }
    // Optimozation
    // Time Complexity : O(N*M)
    // Space Complexity : O(N+M)
    int opti(int n,int m,string s1,string s2)
    {
        vector<int> prev(m+1,0),curr(m+1,0);
        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=m;j++)
            {
                if(s1[i] == s2[j]) curr[j] = 1+prev[j-1];
                else curr[j] = max(prev[j],curr[j-1]);
            }
            prev = curr;
        }
        return prev[m];
    }
public:
    int lcs(string s1,string s2)
    {
        int n = s1.size();
        int m = s2.size();
        // Recursion
        // return recc(n-1,m-1,s1,s2);
        // Memoization
        vector<vector<int>> dp(n,vector<int>(m,-1));
        // return memo(n-1,m-1,s1,s2,dp);
        // Tabulation
        // return tab(n,m,s1,s2);
        // Optimization
        return opti(n,m,s1,s2);
    }
};
int main()
{
    string s1,s2;
    cin>>s1>>s2;
    Solution obj;
    int ans = obj.lcs(s1,s2);
    cout<<ans<<endl;

    return 0;
}