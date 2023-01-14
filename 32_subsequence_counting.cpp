// Problem
/*
We are given two strings S1 and S2, we want to know how many distinct subsequences of S2 are present in S1.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
int prime = 1e9+7;
private:
// Recursion
// Time COmplexity : exponential
// SPace Complexity : O(N+M)
int recc(int index1,int index2,string &s1,string &s2)
{
    if(index2<0) return 1;
    if(index1<0) return 0;
    if(s1[index1] == s2[index2]) return (recc(index1-1,index2-1,s1,s2)+recc(index1-1,index2,s1,s2));
    else return recc(index1-1,index2,s1,s2);
}
// Memoization
// Time Complexity : O(N*m)
// Space COmplexity : O(N*M)+O(N+M)
int memo(int index1,int index2,string &s1,string &s2,vector<vector<int>> &dp)
{
    if(index2<0) return 1;
    if(index1<0) return 0;
    if(dp[index1][index2]!=-1) return dp[index1][index2];
    if(s1[index1]==s2[index2]) return dp[index1][index2] = (memo(index1-1,index2-1,s1,s2,dp)+memo(index1-1,index2,s1,s2,dp))%prime;
    else return dp[index1][index2] = memo(index1-1,index2,s1,s2,dp);
}
// Tabulation
// Time Complexity : O(N*m)
// Space COmplexity : O(N*M)
int tab(string &s1,string &s2)
{
    int n = s1.size();
    int m = s2.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    for(int i = 0;i<=n;i++) dp[i][0] = 1;
    for(int j = 1;j<=m;j++) dp[0][j] = 0;
    for(int i = 1;i<=n;i++)
    {
        for(int j = 1;j<=m;j++)
        {
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = (dp[i-1][j-1]+dp[i-1][j]) % prime;
            }
            else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][m] % prime;
}
// Optimization
// Time Complexity : O(N*M)
// Space Complexity : O(M)
int opti(string &s1,string &s2)
{
    int n = s1.size();
    int m = s2.size();
    vector<int> prev(m+1,0),curr(m+1,0);
    prev[0] = curr[0] = 1;
    for(int i = 1;i<=n;i++)
    {
        for(int j = 1;j<=m;j++)
        {
            if(s1[i-1] == s2[j-1]){
                curr[j] = (prev[j-1]+prev[j]) % prime;
            }
            else{
                curr[j] = prev[j];
            }
        }
        prev = curr;
    }
    return prev[m];
}
public:
int subsequenceCounting(string &t, string &s, int lt, int ls) {
//     return recc(lt-1,ls-1,t,s);
    vector<vector<int>> dp(lt,vector<int>(ls,-1));
//     return memo(lt-1,ls-1,t,s,dp);
//     return tab(t,s);
    return opti(t,s);
} 
};
int main()
{
    string s1,s2;
    cin>>s1>>s2;
    Solution obj;
    int n = s1.size();
    int m  = s2.size();
    int ans = obj.subsequenceCounting(s1,s2,n,m);
    cout<<ans<<endl;
    return 0;
}