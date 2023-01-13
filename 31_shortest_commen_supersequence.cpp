// Problem
/*
Shortest Common Supersequence

We are given two strings ‘S1’ and ‘S2’. We need to return their shortest common supersequence. A supersequence is defined as the string which contains both the strings S1 and S2 as subsequences.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
// Tabulation
// Time Complexity : O(N*M)+O(N*M)
// Space Complexity : O(N*M)
    string tab(string &s1,string &s2)
    {
        int n  = s1.size();
        int m = s2.size();
        vector<vector<int>> dp(n+1,vector<int> (m+1,0));
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
        int len = dp[n][m];
        int i = n;
        int j = m;
        int index = len-1;
        string ans = "";
        while(i>0 && j>0)
        {
            if(s1[i-1] == s2[j-1])
            {
                ans+=s1[i-1];
                index--;
                i--;
                j--;
            }
            else if(dp[i-1][j]>dp[i][j-1])
            {
                ans+=s1[i-1];
                i--;
            }
            else{
                ans+=s2[j-1];
                j--;
            }
        }
        while(i>0){
            ans+=s1[i-1];
            i--;
        } 
        while(j>0){
            ans+=s2[j-1];
            j--;
        } 
        reverse(ans.begin(),ans.end());
        return ans;
    }
public:
    string scs(string &s1,string &s2){
        string ans = tab(s1,s2);
        return ans;
    }
};
int main()
{
    string s1,s2;
    cin>>s1>>s2;
    Solution obj;
    string ans = obj.scs(s1,s2);
    cout<<ans<<endl;
    return 0;
}