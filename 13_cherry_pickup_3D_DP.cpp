// Problem
/*
We are given an ‘N*M’ matrix. Every cell of the matrix has some chocolates on it, mat[i][j] gives us the number of chocolates. We have two friends ‘Alice’ and ‘Bob’. initially, Alice is standing on the cell(0,0) and Bob is standing on the cell(0, M-1). Both of them can move only to the cells below them in these three directions: to the bottom cell (↓), to the bottom-right cell(↘), or to the bottom-left cell(↙).

When Alica and Bob visit a cell, they take all the chocolates from that cell with them. It can happen that they visit the same cell, in that case, the chocolates need to be considered only once.

They cannot go out of the boundary of the given matrix, we need to return the maximum number of chocolates that Bob and Alice can together collect.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Recursion
    // Time Complexity : O(3^N * 3^N)
    // Space Complexity : O(N*M)+O(3^N 8 3^N)
int recc(int i,int j1,int j2,vector<vector<int>> &grid)
{
    int m = grid[0].size();
    int n = grid.size();
    if(j1<0 || j1>=m || j2<0 || j2>=m) return -1e9;
    if(i == n-1)
    {
        if(j1 == j2) return grid[j1][j2];
        else return grid[i][j1]+grid[i][j2];
    }
    int maxi = INT_MIN;
    for(int di = -1;di<=1;di++)
    {
        for(int dj = -1;dj<=1;dj++)
        { 
            int ans = 0;
            if(j1 == j2)  ans = grid[i][j1];
            else ans = grid[i][j1]+grid[i][j2];
            ans+=recc(i+1,j1+di,j2+dj,grid);
            maxi = max(maxi,ans);
        }
    }
    return maxi;
}

// Memoization
// Time Complexity :  O(N*M*M) * 9
// Space Complexity : O(N) + O(N*M*M)
    int memo(int i,int j1,int j2,vector<vector<int>> &grid,vector<vector<vector<int>>> &dp)
    {
        int n = grid.size();
    int m = grid[0].size();
    if(j1<0 || j2<0 || j1>=m || j2>=m) return -1e9;
    if(i == n-1)
    {
        if(j1 == j2) return grid[i][j1];
        else return grid[i][j1]+grid[i][j2];
    }
    if(dp[i][j1][j2] != -1) return dp[i][j1][j2];
    int maxi = INT_MIN;
    for(int di = -1;di<=1;di++)
    {
        for(int dj = -1;dj<=1;dj++)
        {
            int ans;
            if(j1 == j2) ans = grid[i][j1]+memo(i+1,di+j1,dj+j2,grid,dp);
            else ans = grid[i][j1]+grid[i][j2]+memo(i+1,di+j1,dj+j2,grid,dp);
            maxi = max(maxi,ans);
        }
    }
    return dp[i][j1][j2] = maxi;
    }

    // Tabulation
    // Time Complexity : O(N*M*M)*9
    // Space Complexity : O(N*M*M)
int tab(int n,int m,vector<vector<int>> &grid)
{
    vector < vector < vector < int >>> dp(n, vector < vector < int >> (m, vector < int > (m, 0)));

  for (int j1 = 0; j1 < m; j1++) {
    for (int j2 = 0; j2 < m; j2++) {
      if (j1 == j2)
        dp[n - 1][j1][j2] = grid[n - 1][j1];
      else
        dp[n - 1][j1][j2] = grid[n - 1][j1] + grid[n - 1][j2];
    }
  }

  //Outer Nested Loops for travering DP Array
  for (int i = n - 2; i >= 0; i--) {
    for (int j1 = 0; j1 < m; j1++) {
      for (int j2 = 0; j2 < m; j2++) {

        int maxi = INT_MIN;

        //Inner nested loops to try out 9 options
        for (int di = -1; di <= 1; di++) {
          for (int dj = -1; dj <= 1; dj++) {

            int ans;

            if (j1 == j2)
              ans = grid[i][j1];
            else
              ans = grid[i][j1] + grid[i][j2];

            if ((j1 + di < 0 || j1 + di >= m) ||
              (j2 + dj < 0 || j2 + dj >= m))

              ans += -1e9;
            else
              ans += dp[i + 1][j1 + di][j2 + dj];

            maxi = max(ans, maxi);
          }
        }
        dp[i][j1][j2] = maxi;
      }
    }
  }

  return dp[0][0][m - 1];
}

// Optimization
// Time Complexity :  O(N*M*M)*9
// Space Complexity : O(M*M)
int opti(int n, int m, vector < vector < int >> & grid) {
  // Write your code here.
  vector < vector < int >> front(m, vector < int > (m, 0)), cur(m, vector < int > 
  (m, 0));

  for (int j1 = 0; j1 < m; j1++) {
    for (int j2 = 0; j2 < m; j2++) {
      if (j1 == j2)
        front[j1][j2] = grid[n - 1][j1];
      else
        front[j1][j2] = grid[n - 1][j1] + grid[n - 1][j2];
    }
  }

  //Outer Nested Loops for travering DP Array
  for (int i = n - 2; i >= 0; i--) {
    for (int j1 = 0; j1 < m; j1++) {
      for (int j2 = 0; j2 < m; j2++) {

        int maxi = INT_MIN;

        //Inner nested loops to try out 9 options
        for (int di = -1; di <= 1; di++) {
          for (int dj = -1; dj <= 1; dj++) {

            int ans;

            if (j1 == j2)
              ans = grid[i][j1];
            else
              ans = grid[i][j1] + grid[i][j2];

            if ((j1 + di < 0 || j1 + di >= m) ||
              (j2 + dj < 0 || j2 + dj >= m))

              ans += -1e9;
            else
              ans += front[j1 + di][j2 + dj];

            maxi = max(ans, maxi);

          }
        }
        cur[j1][j2] = maxi;
      }
    }
    front = cur;
  }

  return front[0][m - 1];

}

public:
    int maximumChocolates(int n,int m,vector<vector<int>> &grid)
    {
        
        // Recursion
        int ans = recc(0,0,m-1,grid);
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
    int ans = obj.maximumChocolates(n,m,grid);
    cout<<ans<<endl;   
    return 0;
}