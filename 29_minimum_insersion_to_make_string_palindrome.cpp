// Problem
/*
Problem Statement: Minimum insertions required to make a string palindrome

A palindromic string is a string that is the same as its reverse. For example: “nitin” is a palindromic string. Now the question states that we are given a string, we need to find the minimum insertions that we can make in that string to make it a palindrome.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // tabulation
    // Time Complexity : O(N*M)
    // Space COmplexity : O(N*M)
    int tab(string &s1,string &s2)
    {
        int n = s1.size();
        int m = s2.size();
        vector<vector<int>> dp(n+1,vector<int>(m+1,0));
        for(int i = 0;i<=n;i++) dp[i][0] = 0;
        for(int j = 0;j<=m;j++) dp[0][j] = 0;
        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=m;j++)
            {
                if(s1[i-1] == s2[j-1]) dp[i][j] = 1+dp[i-1][j-1];
                else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
        }
        return dp[n][m];
    }
    // Space Optimization
    // Time COmplexity : O(N*M)
    // SPace COmplexity : O(M)
    int opti(string &s1,string &s2)
    {
        int n = s1.size();
        int m = s2.size();
        vector<int> prev(m+1,0),curr(m+1,0);
        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=m;j++)
            {
                if(s1[i-1] == s2[j-1]) curr[j] = 1+prev[j-1];
                else curr[j] = max(prev[j],curr[j-1]);
            }
            prev = curr;
        }
        return prev[m];
    }
public:
    int lcs(string &s1)
    {
        string s2 = s1;
        reverse(s2.begin(),s2.end());
        // return tab(s1,s2);
        return opti(s1,s2);
    }
    int minimumInsertion(string &s)
    {
        int n = s.size();
        return n-lcs(s);
    }
};
int main()
{
    string s1;
    cin>>s1;
    Solution obj;
    int ans = obj.minimumInsertion(s1);
    cout<<ans<<endl;
    return 0;
}