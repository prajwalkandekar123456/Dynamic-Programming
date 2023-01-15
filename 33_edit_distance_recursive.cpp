// Problem
/*
We are given two strings ‘S1’ and ‘S2’. We need to convert S1 to S2. The following three operations are allowed:

Deletion of a character.
Replacement of a character with another one.
Insertion of a character.
We have to return the minimum number of operations required to convert S1 to S2 as our answer.


*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
// Recursion
// Time COmplexity : Recursive
// Space COmplexity : O(N)
int recc(int index1,int index2,string &str1,string &str2)
{
    if(index1<0) return index2+1;
    if(index2 < 0) return index1+1;
    if(str1[index1] == str2[index2]) return 0+recc(index1-1,index2-1,str1,str2);
    int insert = recc(index1,index2-1,str1,str2);
    int delete1 = recc(index1-1,index2,str1,str2);
    int replace = recc(index1-1,index2-1,str1,str2);
    int ans = 1+min(insert,min(replace,delete1));
    return ans;
}
// Memoization
// Time Complexity : O(N*M)
// Space COmplexity : O(N*M)+O(N+M)
int memo(int index1,int index2,string &str1,string &str2,vector<vector<int>> &dp)
{
    if(index1<0) return index2+1;
    if(index2<0) return index1+1;
    if(dp[index1][index2]!=-1) return dp[index1][index2];
    if(str1[index1] == str2[index2]) return dp[index1][index2] = 0+memo(index1-1,index2-1,str1,str2,dp);
    int insert = memo(index1,index2-1,str1,str2,dp);
    int delete1 = memo(index1-1,index2,str1,str2,dp);
    int replace = memo(index1-1,index2-1,str1,str2,dp);
    return dp[index1][index2] = 1+min(insert,min(delete1,replace));
}

// Tabulation
// Time Complexity : O(N*M)
// Space Complexity : O(N*M)
int tab(string &str1,string &str2)
{
    int n = str1.size();
    int m = str2.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    for(int j = 0;j<=m;j++) dp[0][j] = j;
    for(int i = 0;i<=n;i++) dp[i][0] = i;
    for(int i = 1;i<=n;i++)
    {
        for(int j = 1;j<=m;j++)
        {
            if(str1[i-1] == str2[j-1])
            {
                dp[i][j] = dp[i-1][j-1];
            }
            else{
                dp[i][j] = 1+min(dp[i-1][j],min(dp[i][j-1],dp[i-1][j-1]));
            }
        }
    }
    return dp[n][m];
}

// Optimization
// Time COmplexity : O(N*M)
// SPace Complexity : O(N)
int opti(string &str1,string &str2)
{
    int n = str1.size();
    int m = str2.size();
    vector<int> prev(m+1,0),curr(m+1,0);
    for(int j = 0;j<=m;j++) prev[j] = j;
    for(int i = 1;i<=n;i++)
    {
        curr[0] = i;
        for(int j = 1;j<=m;j++)
        {
            if(str1[i-1] == str2[j-1])
            {
                curr[j] = prev[j-1];
            }
            else{
                curr[j] = 1+ min(prev[j],min(curr[j-1],prev[j-1]));
            }
        }
        prev = curr;
    }
    return prev[m];
}
public:
int editDistance(string str1, string str2)
{
    int n = str1.size();
    int m = str2.size();
//     return recc(n-1,m-1,str1,str2);
    vector<vector<int>> dp(n,vector<int>(m,-1));
//     return memo(n-1,m-1,str1,str2,dp);
//     return tab(str1,str2);
    return opti(str1,str2);
}
};
int main()
{
    string s1,s2;
    cin>>s1>>s2;
    Solution obj;
    int ans = obj.editDistance(s1,s2);
    cout<<ans<<endl;
    return 0;
}