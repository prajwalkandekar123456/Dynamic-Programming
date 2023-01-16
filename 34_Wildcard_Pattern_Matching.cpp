// Problem
/*
We are given two strings ‘S1’ and ‘S2’. String S1 can have the following two special characters:

‘?’ can be matched to a single character of S2.
‘*’ can be matched to any sequence of characters of S2. (sequence can be of length zero or more).
We need to check whether strings S1 and S2 match or not.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
// Recursion
// Time Complexity L exponential
// Space Complexity : O(N+M)
bool recc(int index1,int index2,string &s1,string &s2)
{
    if(index1<0 && index2<0) return true;
    if(index1<0 && index2>=0) return false;
    if(index2<0 && index1>=0){
        for(int j = 0;j<=index1;j++){
            if(s1[j]!='*')
            {
                return false;
            }
        }
        return true;
    }
    if(s1[index1] == s2[index2] || s1[index1] == '?'){
        return recc(index1-1,index2-1,s1,s2);
    }
    if(s1[index1] == '*'){
        return recc(index1-1,index2,s1,s2)||recc(index1,index2-1,s1,s2);
    }
    return false;
}
// Memoization
// Time Complexity : O(N*M)
// Space COmplexity : O(N*M)+O(N+M)
bool memo(int index1,int index2,string &s1,string &s2,vector<vector<bool>> &dp)
{
    if(index1<0 && index2<0) return true;
    if(index1<0 && index2>=0) return false;
    if(index2<0 && index1>=0){
        for(int j = 0;j<=index1;j++)
        {
            if(s1[j]!='*'){
                return false;
            }
        }
        return true;
    }
    if(dp[index1][index2]!=false) return dp[index1][index2];
    if(s1[index1] == s2[index2] || s1[index1] == '?')
    {
        return dp[index1][index2] = memo(index1-1,index2-1,s1,s2,dp);
    }
    if(s1[index1] == '*'){
        return dp[index1][index2] = memo(index1-1,index2,s1,s2,dp)|| memo(index1,index2-1,s1,s2,dp);
    }
    return false;
}

// Tabulation
// time Complexity : O(N*M)
// SPace COmplexity : O(N*M)
bool tab(string &s1,string &s2)
{
    int n = s1.size();
    int m = s2.size();
    vector<vector<bool>> dp(n+1,vector<bool>(m,false));
    dp[0][0] = true;
    for(int j = 1;j<=m;j++){
        dp[0][j] = false;
    }
    for(int i = 1;i<=n;i++)
    {
        int flag = true;
        for(int j = 1;j<=i;j++){
        if(s1[j-1]!='*')
        {
            flag = false;
            break;
        }
       }
        dp[i][0] = flag;
    }
    for(int i = 1;i<=n;i++)
    {
        for(int j = 1;j<=m;j++)
        {
            if(s1[i-1] == s2[j-1] || s1[i-1] == '?')
            {
                dp[i][j] = dp[i-1][j-1];
            }
            else{
            if(s1[i-1] == '*'){
                dp[i][j] = dp[i-1][j] || dp[i][j-1];
            }
             else dp[i][j] = false;
            }
        }
    }
    return dp[n][m];
}
bool isAllStars(string & S1, int i) {

  // S1 is taken in 1-based indexing
  for (int j = 1; j <= i; j++) {
    if (S1[j - 1] != '*')
      return false;
  }
  return true;
}
// Optimization
// Time Complexity : O(N*M)
// SPace Complexity : O(M)
bool opti(string & S1, string & S2) {

  int n = S1.size();
  int m = S2.size();

  vector < bool > prev(m + 1, false);
  vector < bool > cur(m + 1, false);

  prev[0] = true;

  for (int i = 1; i <= n; i++) {
    cur[0] = isAllStars(S1, i);
    for (int j = 1; j <= m; j++) {

      if (S1[i - 1] == S2[j - 1] || S1[i - 1] == '?')
        cur[j] = prev[j - 1];

      else {
        if (S1[i - 1] == '*')
          cur[j] = prev[j] || cur[j - 1];

        else cur[j] = false;
      }
    }
    prev = cur;
  }

  return prev[m];

}
public:
bool wildcardMatching(string pattern, string text)
{
   int n = pattern.size();
    int m = text.size();
//     return recc(n-1,m-1,pattern,text);
    vector<vector<bool>> dp(n,vector<bool>(m,false));
//     return memo(n-1,m-1,pattern,text,dp);
//     return tab(pattern,text);
    return opti(pattern,text);
}

};
int main()
{
    string s1,s2;
    cin>>s1>>s2;
    Solution obj;
    bool ans = obj.wildcardMatching(s1,s2);
    if(ans) cout<<"True"<<endl;
    else cout<<"False"<<endl;
    return 0;
}