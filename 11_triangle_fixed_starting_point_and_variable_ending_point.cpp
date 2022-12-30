// Problem
/*
We are given a Triangular matrix. We need to find the minimum path sum from the first row to the last row.

At every cell we can move in only two directions: either to the bottom cell (↓) or to the bottom-right cell(↘)
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Recursion
    // Time Complexity : O(N*N)
    // Space Complexity : O(N*N)+ O(N*N)
    int recc(int i,int j,vector<vector<int>> &triangle,int n)
    {
        if(i == n-1) return triangle[i][j];
        int down = triangle[i][j]+recc(i+1,j,triangle,n);
        int diagonal = triangle[i][j]+recc(i+1,j+1,triangle,n);
        return min(down,diagonal);
    }

    // Memoization
    // Time Complexity : O(N*N)
    // Space Complexity : O(N*N)+ O(N)
    int memo(int i,int j,vector<vector<int>> &triangle,vector<vector<int>> &dp,int n)
    {
        if(i == n-1) return triangle[i][j];
        if(dp[i][j]!=-1) return dp[i][j];
        int down = triangle[i][j]+memo(i+1,j,triangle,dp,n);
        int diagonal = triangle[i][j]+memo(i+1,j+1,triangle,dp,n);
        return dp[i][j] = min(down,diagonal);
    }

    //Tabulation
    // Time Complexity : O(N*N)
    // Space Complexity : O(N*N)
    int tab(int n,vector<vector<int>> &triangle)
    {
        vector<vector<int>> dp(n,vector<int>(n,0));
        for(int j = 0;j<n;j++){
            dp[n-1][j] = triangle[n-1][j];
        }
        for(int i = n-2;i>=0;i--)
        {
            for(int j = i;j>=0;j--)
            {
                int down = triangle[i][j]+dp[i+1][j];
                int diagonal = triangle[i][j]+dp[i+1][j+1];
                dp[i][j] = min(down,diagonal);
            }
        }
        return dp[0][0];
    }

    // Optimization
    // Time Complexity : O(N*N)
    // Space Complexity :O(n)
    int opti(int n,vector<vector<int>> &triangle)
    {
        vector<int> front(n,0),curr(n,0);
        for(int j = 0;j<n;j++)
        {
            front[j] = triangle[n-1][j];
        }
        for(int i = n-2;i>=0;i--)
        {
            for(int j = i;j>=0;j--)
            {
                int down = triangle[i][j]+front[j];
                int diagonal = triangle[i][j]+front[j+1];
                curr[j] = min(down,diagonal);
            }
            front = curr;
        }
        return front[0];
    }
public:
    int minimumPathSum(int n,vector<vector<int>> &triangle)
    {
        /*
        // Recursion
        return recc(0,0,triangle,n);
        */
       /*
       // Memoization
       vector<vector<int>> dp(n,vector<int>(n,-1));
       return memo(0,0,triangle,dp,n);
       */
      /*
      // Tabulation
      return tab(n,triangle);
      */
     // Optimization
     return opti(n,triangle);
    }
};

int main()
{
    int n;
    cin>>n;
    vector<vector<int>> triangle(n,vector<int>(n,0));
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<=i;j++)
        {
            cin>>triangle[i][j];
        }
    }
    Solution obj;
    int ans = obj.minimumPathSum(n,triangle);
    cout<<ans<<endl;
    return 0;
}