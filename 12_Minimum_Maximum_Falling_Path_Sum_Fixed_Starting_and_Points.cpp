//Problem
/*
We are given an ‘N*M’ matrix. We need to find the maximum path sum from any cell of the first row to any cell of the last row.

At every cell we can move in three directions: to the bottom cell (↓), to the bottom-right cell(↘), or to the bottom-left cell(↙).
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Recursion
    // Time Complexity : O(3^N)
    // Space Complexity : O(N)
    int recc(int i,int j,vector<vector<int>> &matrix)
    {
        int m = matrix[0].size();
        if(j<0 || j>=m) return -1e9;
        if(i == 0) return matrix[i][j];
        int up = matrix[i][j] + recc(i-1,j,matrix);
        int diagonalLeft = matrix[i][j]+recc(i-1,j-1,matrix);
        int diagonalRight = matrix[i][j] + recc(i-1,j+1,matrix);
        return max(up,max(diagonalLeft,diagonalRight));
    }
    // Memoization
    // Time Complexity : O(N*M)
    // Space Complexity : O(N*M)+O(M)
    int memo(int i,int j,vector<vector<int>> &matrix,vector<vector<int>> &dp,int m)
    {
        // int m = matrix[0].size();
        if(j<0 || j>=m) return -1e9;
        if(i == 0) return matrix[0][j];
        
        if(dp[i][j] != -1) return dp[i][j];
        int up = matrix[i][j]+memo(i-1,j,matrix,dp,m);
        int diagonalLeft = matrix[i][j] + memo(i-1,j-1,matrix,dp,m);
        int diagonalRight = matrix[i][j] + memo(i-1,j+1,matrix,dp,m);
        return dp[i][j] = max(up,max(diagonalLeft,diagonalRight));
    }
    // Tabulation
    // Time Complexity : O(N*M)
    // Space Complexity : O(N*M)
    int tab(int n,int m,vector<vector<int>> &matrix)
    {
        vector<vector<int>> dp(n,vector<int>(m,0));
        for(int j = 0;j<m;j++)
        {
            dp[0][j] = matrix[0][j];
        }
        for(int i = 1;i<n;i++)
        {
            for(int j = 0;j<m;j++)
            {
                int up = matrix[i][j]+dp[i-1][j];
                int diagonalLeft = matrix[i][j];
                int diagonalRight = matrix[i][j];
                if(j-1>=0) diagonalLeft+=dp[i-1][j-1];
                else diagonalLeft+=-1e9;
                if(j+1<m) diagonalRight+=dp[i-1][j+1];
                else diagonalRight+=-1e9;
                dp[i][j] = max(up,max(diagonalLeft,diagonalRight));
            }
        }
        int maxi = INT_MIN;
        for(int j = 0;j<m;j++)
        {
            maxi = max(maxi,dp[n-1][j]);
        }
        return maxi;
    }

    // Optimization
    // Time Complexity : O(N*M)
    // Space Complexity :O(N) + O(N);
    int opti(int n,int m,vector<vector<int>> &matrix)
    {
        vector<int> prev(m,0),curr(m,0);
        for(int j = 0;j<m;j++)
        {
            prev[j] = matrix[0][j];
        }
        for(int i = 1;i<n;i++)
        {
            for(int j = 0;j<m;j++)
            {
                int up = matrix[i][j]+prev[j];
                int diagonalLeft = matrix[i][j];
                int diagonalRight = matrix[i][j];
                if(j-1>=0) diagonalLeft+= prev[j-1];
                else diagonalLeft+=-1e9;
                if(j+1<m) diagonalRight+= prev[j+1];
                curr[j] = max(up,max(diagonalLeft,diagonalRight));
            }
            prev = curr;
        }
        int maxi = INT_MIN;
        for(int i = 0;i<m;i++)
        {
            maxi = max(maxi,prev[i]);
        }
        return maxi;
    }
public:
    int getMaxPathSum(int n,int m,vector<vector<int>> &matrix)
    {
       /* 
        // Recursion
        int maxi = -1e9;
        for(int j = 0;j<m;j++)
        {
            int ans = recc(n-1,j,matrix);
            if(ans>maxi) maxi = ans;
        }
        return maxi;
        */
       /*
       // Memoization
       int maxi = INT_MIN;
       vector<vector<int>> dp(n,vector<int>(m,-1));
       for(int j = 0;j<m;j++)
       {
          int ans = memo(n-1,j,matrix,dp,m);
          maxi = max(maxi,ans);
       }
       return maxi;
      */
     /*
     // Tabulation
     return tab(n,m,matrix);
     */
    // Optimization
    return opti(n,m,matrix);
    }
};
int main()
{
    int n, m;
    cin>>n>>m;
    vector<vector<int>> matrix(n,vector<int>(m,0));
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            cin>>matrix[i][j];
        }
    }

    Solution obj;
    int ans = obj.getMaxPathSum(n,m,matrix);
    cout<<ans<<endl;
    return 0;
}