// Problem
/*
Given a binary matrix M of size n X m. Find the maximum area of a rectangle formed only of 1s in the given matrix.

Example 1:

Input:
n = 4, m = 4
M[][] = {{0 1 1 0},
         {1 1 1 1},
         {1 1 1 1},
         {1 1 0 0}}
Output: 8
Explanation: For the above test case the
matrix will look like
0 1 1 0
1 1 1 1
1 1 1 1
1 1 0 0
the max size rectangle is 
1 1 1 1
1 1 1 1
and area is 4 *2 = 8.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Time Complexity :(O(N*M))
    // Space Complexity : O(N*M)
    int largestArea(vector<int> &heights)
    {
        int n = heights.size();
        stack<int> st;
        vector<int> leftSmall(n),rightSmall(n);
        for(int i = 0;i<n;i++)
        {
            while(!st.empty()&& heights[st.top()]>=heights[i])
            {
                st.pop();
            }
            if(st.empty()) leftSmall[i] = 0;
            else leftSmall[i] = st.top()+1;
            st.push(i);
        }
        while(!st.empty()) st.pop();
        for(int i = n-1;i>=0;i--)
        {
            while(!st.empty() && heights[st.top()]>=heights[i])
            {
                st.pop();
            }
            if(st.empty()) rightSmall[i] = n-1;
            else rightSmall[i] = st.top()-1;
            st.push(i);
        }
        int maxi = 0;
        for(int i = 0;i<n;i++)
        {
            maxi = max(maxi,(rightSmall[i]-leftSmall[i]+1)*heights[i]);
        }
        return maxi;
    }
public:
    int maximalAreaOfSubMatrixOfAll1(vector<vector<int>> &mat,int n,int m)
    {
        vector<int> heights(m,0);
        int maxArea = 0;
        for(int i = 0;i<n;i++)
        {
            for(int j =0;j<m;j++)
            {
                if(mat[i][j] == 1) heights[j]++;
                else heights[j] = 0;
            }
            int ans = largestArea(heights);
            maxArea = max(maxArea,ans);
        }
        return maxArea;
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
    int ans = obj.maximalAreaOfSubMatrixOfAll1(mat,n,m);
    cout<<ans<<endl;
    return 0;
}