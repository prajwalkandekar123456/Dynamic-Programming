// Problem
/*
Given two sequences, print the longest subsequence present in both of them.

Examples: 

LCS for input Sequences “ABCDGH” and “AEDFHR” is “ADH” of length 3. 
LCS for input Sequences “AGGTAB” and “GXTXAYB” is “GTAB” of length 4.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution
{
private:
// Tabulation
// Time COmplexity : O(N*M)
// Space COmplexity : O(N*M)
    string tab(string &s1,string &s2)
    {
        int n = s1.size();
        int m = s1.size();
        vector<vector<int>> dp(n+1,vector<int>(m+1,0));
        for(int j = 0;j<=n;j++)
        {
            dp[0][j] = 0;
        }
        for(int i = 0;i<=m;i++)
        {
            dp[i][0] = 0;
        }
        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=m;j++)
            {
                if(s1[i-1] == s2[j-1]) dp[i][j] = 1+dp[i-1][j-1];
                else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
        }
        int len = dp[n][m];
        string ans = "";
        for(int i = 1;i<=len;i++)
        {
            ans+='$';
        }
        int index = len-1;
        int i = n,j=m;
        while(i>0 && j>0)
        {
            if(s1[i-1] == s2[j-1])
            {
                ans[index] = s1[i-1];
                i--;
                j--;
                index--;
            }
            else if(s1[i-1]>s2[j-1])
            {
                i--;
            }
            else{
                j--;
            }
        }
        return ans;
    }
public:
    string printLCS(string &s1,string &s2)
    {
        // Tabulation
        return tab(s1,s2);
    }
};
int main()
{
    string s1,s2;
    cin>>s1>>s2;
    Solution obj;
    string ans = obj.printLCS(s1,s2);
    cout<<ans<<endl;
    return 0;
}