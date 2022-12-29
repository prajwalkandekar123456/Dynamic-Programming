// Problem
/*
In this article, we will solve the most asked coding interview problem: Grid Unique Paths

Given two values M and N, which represent a matrix[M][N]. We need to find the total unique paths from the top-left cell (matrix[0][0]) to the rightmost cell (matrix[M-1][N-1]).

At any cell we are allowed to move in only two directions:- bottom and right.


*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
/*
    //Recursion
    // Time Complexity : O(2^N*M)
    // Space Complexity : O(m-1 * n-1)

    int recc(int i,int j)
    {
        if(i == 0 && j == 0) return 1;
        if(i<0 || j<0) return 0;
        int up = recc(i-1,j);
        int left = recc(i,j-1);
        return up+left;
    }
*/

/*
// Memoization
// Time Complexity : O(N*M)
// Space Complexity : O(n-1 * m-1) + O(N*M)
int memo(int i,int j,vector<vector<int>> &dp)
{
    if(i == 0 && j==0) return 1;
    if(i < 0 || j < 0) return 0;
    if(dp[i][j]!=-1) return dp[i][j];
    int up = memo(i-1,j,dp);
    int left = memo(i,j-1,dp);
    return dp[i][j] = up+left;

}
*/
/*
// Tabulation
// Time Complexity :O(N*M)
// Space Complexity : O(N*M)
int tab(int m,int n)
{
    vector<vector<int>> dp(m,vector<int>(n,0));
    dp[0][0] = 1;
    for(int i = 0;i<m;i++)
    {
        for(int j = 0;j<n;j++)
        {
            if(i == 0 && j == 0){
                dp[0][0] = 1;
                continue;
            }
            int up = 0;
            int left = 0;
            if(i>0) up = dp[i-1][j];
            if(j>0) left = dp[i][j-1];
            dp[i][j] = up+left;
        }
    }
    return dp[m-1][n-1];
}
*/

// Optimization
// Time Complexity : O(N*M)
// Space Complexity : O(M)
int opti(int m,int n)
{
    vector<int> prev(n,0);
    for(int i=0; i<m; i++){
        vector<int> temp(n,0);
        for(int j=0; j<n; j++){
            if(i==0 && j==0){
                temp[j]=1;
                continue;
            }
            
            int up=0;
            int left =0;
            
            if(i>0)
                up = prev[j];
            if(j>0)
                left = temp[j-1];
                
            temp[j] = up + left;
        }
        prev = temp;
    }
    
    return prev[n-1];
}
public:
    int countWays(int m,int n)
    {
        /*
        // Recursion
        int ans = recc(m-1,n-1);
        return ans;
        */
       /*
       //memoization
       vector<vector<int>> dp(m,vector<int> (n,-1));
       int ans = memo(m-1,n-1,dp);
       return ans;
       */
      /*
      //tabulation
      int ans = tab(m,n);
      return ans;
      */
     //optimization
     int ans = opti(m,n);
     return ans;
    }
};

int main()
{
    int m,n;
    cin>>m>>n;
    Solution obj;
    int ans = obj.countWays(m,n);
    cout<<ans<<endl;
    return 0;
}