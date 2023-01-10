// Problem
/*
A palindromic string is a string that is equal to its reverse. For example: “nitin” is a palindromic string. Now the question states to find the length of the longest palindromic subsequence of a string. It is that palindromic subsequence of the given string with the greatest length.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Tabulation
    // Time Complexity : O(N*M)
    // Space COmplexity : O(N*M)
    int tab(string &s1,string &s2)
    {
        int n = s1.size();
        int m = s2.size();
        vector<vector<int>> dp(n+1,vector<int>(m+1,0));
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
    // Optimization
    // Time COmplexity : O(N*M)
    // SPace Complexity : O(M)
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
                else prev[j] = max(curr[j-1],prev[j]);
            }
            prev = curr;
        }
        return prev[m];
    }
public:
    int longestCommonPalindrome(string &s1)
    {
        string s2 = s1;
        reverse(s2.begin(),s2.end());
        // Tabulation
        // return tab(s1,s2);
        //Optimization
         return opti(s1,s2);
    }
};

int main()
{
    string s1;
    cin>>s1;
    Solution obj;
    int ans = obj.longestCommonPalindrome(s1);
    cout<<ans<<endl;
    return 0;
}