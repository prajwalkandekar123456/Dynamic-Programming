// Problem
/*
Minimum Insertions/Deletions to Convert String A to String B

We are given two strings, str1 and str2. We are allowed the following operations:

Delete any number of characters from string str1.
Insert any number of characters in string str1.
We need to tell the minimum operations required to convert str1 to str2.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
// Memoization
// Time Complexity : O(N*M)
// Space Complexity : O(N*M)+O(M)
int memo(int index1,int index2,string &s1,string &s2,vector<vector<int>> &dp)
{
    if(index1<0 || index2<0) return 0;
    if(dp[index1][index2]!=-1) return dp[index1][index2];
    if(s1[index1]==s2[index2]) return 1+memo(index1-1,index2-1,s1,s2,dp);
    else return dp[index1][index2] = max(memo(index1-1,index2,s1,s2,dp),memo(index1,index2-1,s1,s2,dp));
}
// Tabulation
// Time Complexity : O(N*M)
// Space COmplexity : O(N*M)
int tab(string &s1,string &s2){
    int n = s1.size();
    int m = s2.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1,-1));
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
// Optimization
// Time Complexity : O(N*M)
// Space Complexity : O(M)
int opti(string &s1,string &s2)
{
    int n = s1.size();
    int m = s2.size();
    vector<int> prev(m+1,0),curr(m+1,0);
    for(int i = 1;i<=n;i++)
    {
        for(int j = 1;j<=m;j++)
        {
            if(s1[i-1] == s2[j-1]) curr[j] = prev[j-1]+1;
            else curr[j] = max(curr[j-1],prev[j]);
        }
        prev = curr;
    }
    return prev[m];
}
public:
int canYouMake(string &str, string &ptr)
{
    int n = str.size();
    int m = ptr.size();
    vector<vector<int>> dp(n,vector<int>(m,-1));
//     int com = memo(n-1,m-1,str,ptr,dp);
//     int com = tab(str,ptr);
    int com = opti(str,ptr);
    int t1 = m-com;
    int t2 = n-com;
    return t1+t2;
}
};
int main()
{
    string s1,s2;
    cin>>s1>>s2;
    Solution obj;
    int ans = obj.canYouMake(s1,s2);
    cout<<ans<<endl;
    return 0;
}