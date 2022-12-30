//Problem
/*
We are given an “N*M” matrix of integers. We need to find a path from the top-left corner to the bottom-right corner of the matrix, such that there is a minimum cost past that we select.

At every cell, we can move in only two directions: right and bottom. The cost of a path is given as the sum of values of cells of the given matrix.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
/*
    //Recursion
    // Time Complexity : O(2^N*M)
    // Space Complexity : O(N-1 + M-1) + O(N*M)
    int recc(int i,int j,vector<vector<int>>&grid)
    {
        if(i == 0 && j == 0) return grid[0][j];
        if(i<0 || j<0) return 1e9;
        int up = grid[i][j] + recc(i-1,j,grid);
        int left = grid[i][j] + recc(i,j-1,grid);
        return min(up,left);
    }
*/
/*
    // Memoization
    //Time Complexity : O(N*M)
    // Space Complexity : O(N-1 + M-1) + O(N*M)

    int memo(int i,int j,vector<vector<int>> &grid,vector<vector<int>> &dp)
    {
        if(i == 0 && j == 0) return grid[i][j];
        if(i<0 || j<0) return 1e9;
        if(dp[i][j]!=-1) return dp[i][j];
        int up = grid[i][j]+memo(i-1,j,grid,dp);
        int left = grid[i][j]+memo(i,j-1,grid,dp);
        return dp[i][j] = min(up,left);
    }
/*
    //Tabulation
    // Time Complexity : O(N*M)
    // Space Complexity : O(N*M)

    int tab(int n,int m,vector<vector<int>> &grid)
    {
        vector<vector<int>> dp(n,vector<int>(m,0));
        for(int i = 0;i<n;i++)
        {
            for(int j = 0;j<m;j++)
            {
                if(i ==0 && j == 0)
                {
                    dp[i][j] = grid[i][j];
                    continue;
                }
                int up = grid[i][j];
                int left = grid[i][j];
                if(i>0) up+=dp[i-1][j];
                else up+=1e9;
                if(j>0) left+=dp[i][j-1];
                else left+=1e9;
                dp[i][j] = min(up,left);
            }
        }
        return dp[n-1][m-1];
    }
*/
    // Optimization
    // Time COmplexity : O(N*M)
    // Space Complexity : O(N)
    int opti(int n,int m,vector<vector<int>> &grid)
    {
        vector<int> prev(m,0);
        for(int i = 0;i<n;i++)
        {
            vector<int> temp(m,0);
            for(int j = 0;j<m;j++)
            {
                if(i == 0 && j == 0)
                {
                    temp[j] = grid[i][j];
                    continue;
                }
                int up = grid[i][j];
                int left = grid[i][j];
                if(i>0) up+=prev[j];
                else up+=1e9;
                if(j>0) left+=temp[j-1];
                else left+=1e9;
                temp[j] = min(up,left);
            }
            prev = temp;
        }
        return prev[m-1];
    }
public:
    int minimumPathSum(int n,int m,vector<vector<int>> &grid)
    {
        /*
        // Recursion
        int ans = recc(n-1,m-1,grid);
        return ans;
        */
       /*
       //Memoization
       vector<vector<int>> dp(n,vector<int>(m,-1));
       int ans = memo(n-1,m-1,grid,dp);
       return ans;
       */
      /*
      // Tabulation
      int ans = tab(n,m,grid);
      return ans;
      */

     // Optimization
     int ans = opti(n,m,grid);
     return ans;
    }
};
int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>> grid(n,vector<int>(m,0));
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            cin>>grid[i][j];
        }
    }
    Solution obj;
    int ans = obj.minimumPathSum(n,m,grid);
    cout<<ans<<endl;
    return 0;
}