// Problem
/*
We are given an “N*M” Maze. The maze contains some obstacles. A cell is ‘blockage’ in the maze if its value is -1. 0 represents non-blockage. There is no path possible through a blocked cell.

We need to count the total number of unique paths from the top-left corner of the maze to the bottom-right corner. At every cell, we can move either down or towards the right.
*/

#include<bits/stdc++.h>
using namespace std;
int mod = (int)(1e9+7);
class Solution{
private:
/*
    //Recursion
    // Time Complexity : O(N*M)
    // Space Complexity : O(N-1 * M-1)+O(N*M)
    int recc(int i,int j,vector<vector<int>> &mat)
    {
        if(i == 0 && j == 0) return 1;
        if(i<0 || j<0) return 0;
        if(i>=0 && j>=0 && mat[i][j] == -1) return 0;
        int up = recc(i-1,j,mat);
        int left = recc(i,j-1,mat);
        return up+left % mod;
    }
*/
/*
    // memoization
    // Time Complexity : O(N*M)
    // Space Complexity : O(N-1 * M-1)+O(N*M)
    int memo(int i,int j,vector<vector<int>> &mat,vector<vector<int>> &dp)
    {
        if(i == 0 && j == 0) return 1;
        if(i<0 || j<0) return 0;
        if(i>=0 && j>=0 && mat[i][j] == -1) return 0;
        if(dp[i][j] !=-1) return dp[i][j];
        int up = memo(i-1,j,mat,dp);
        int left = memo(i,j-1,mat,dp);
        return dp[i][j] = up+left&mod;
    }
*/

    //tabulation
    // Time Complexity : O(N*M)
    // Space Complexity : O(N*M)
    int tab(int n,int m,vector<vector<int>> &mat)
    {
        vector<vector<int>> dp(n,vector<int>(m,0));
        for(int i = 0;i<n;i++)
        {
            for(int j = 0;j<m;j++)
            {
                if(i == 0 && j == 0)
                {
                    dp[i][j] = 1;
                    continue;
                }
                if(i>0 && j>0 && mat[i][j] == -1)
                {
                    dp[i][j] = -1;
                    continue;
                }
                int up = 0;
                int left = 0;
                if(i>0) up = dp[i-1][j];
                if(j>0) left = dp[i][j-1];
                dp[i][j] = up+left&mod;
            }
        }
        return dp[n-1][m-1];
    }
public:
    int mazeObstacles(int n,int m,vector<vector<int>> &mat)
    {
        /*
        //recursion
        int ans = recc(n-1,m-1,mat);
        return ans;
        */
       /*
       // memoization
       vector<vector<int>> dp(n,vector<int>(m,-1));
       int ans = memo(n-1,m-1,mat,dp);
       return ans;
       */
      //Tabulation
      int ans = tab(n,m,mat);
      return ans;
    }
};
int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>> mat(n,vector<int>(m,0));
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            cin>>mat[i][j];
        }
    }
    Solution obj;
    int ans = obj.mazeObstacles(n,m,mat);
    cout<<ans<<endl;
    return 0;
}