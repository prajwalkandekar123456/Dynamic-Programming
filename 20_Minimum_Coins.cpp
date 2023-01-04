// Problem
/*
We are given a target sum of ‘X’ and ‘N’ distinct numbers denoting the coin denominations. We need to tell the minimum number of coins required to reach the target sum. We can pick a coin denomination for any number of times we want.
*/
#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    // Recursion
    // Time Complexity : O(2^N)
    // Space Complexity : O(N)
    int recc(int index,int target,vector<int> &arr)
    {
        if(index == 0)
        {
            if(target % arr[0] == 0){
                return target/ arr[0];
            }
            else return 1e9;
        }
        int notTake = 0+recc(index-1,target,arr);
        int take = 1e9;
        if(target>=arr[index]) take = 1+recc(index,target-arr[index],arr);
        return min(take,notTake);
    }

    // Memoization
    // Time Complexity : O(N*K)
    // Space Complexity : O(N*K)+O(N)
    int memo(int index,int target,vector<int> &arr,vector<vector<int>> &dp)
    {
        if(index == 0)
        {
            if(target%arr[0] == 0){
                return target/arr[0];
            }
            else return 1e9;
        }
        int notTake = 0+ memo(index-1,target,arr,dp);
        int take = 1e9;
        if(target>=arr[index]) take = 1+memo(index,target-arr[index],arr,dp);
        return dp[index][target] = min(take,notTake);
    }

    // Tabulation
    // Time Complexity : O(N*K)
    // Space Complexity : O(N*K)
    int tab(int n,int target,vector<int> &arr)
    {
        vector<vector<int>> dp(n,vector<int> (target+1,0));
    for(int i = 0;i<=target;i++)
    {
        if(i%arr[0] == 0) dp[0][i] = i/arr[0];
        else dp[0][i] = 1e9;
    }
    for(int i = 1;i<n;i++){
        for(int j = 0;j<=target;j++)
        {
            int notTake = 0 + dp[i-1][j];
            int take = 1e9;
            if(j>=arr[i]) take = 1+dp[i][j-arr[i]];
            dp[i][j] = min(take,notTake);
        }
    }
    return dp[n-1][target];

    }

    // Optimization
    // Time Complexity : O(N*M)
    // Space Complexity : O(N)
int opti(int n,int target,vector<int> &arr)
{
    vector<int> prev(target+1,0),curr(target+1,0);
    for(int i = 0;i<=target;i++)
    {
        if(i%arr[0] == 0) prev[i] = i/arr[0];
        else prev[i] = 1e9;
    }
    for(int i = 1;i<n;i++)
    {
        for(int j = 0;j<=target;j++){
            int notTake = prev[j];
            int take = 1e9;
            if(j>=arr[i]) take = 1+curr[j-arr[i]];
            curr[j] = min(take,notTake);
        }
        prev = curr;
    }
    return prev[target];
}
public:
    int minimumCoins(int n,int x,vector<int> &arr)
    {
        // Recursion
        // int ans = recc(n-1,x,arr);
        vector<vector<int>> dp(n,vector<int>(x+1,-1));
        // int ans = memo(n-1,x,arr,dp);
        int ans = tab(n,x,arr);
        // int ans = opti(n,x,arr);
        if(ans>=1e9) return -1;
        return ans;
    }
};
int main()
{
    int n,x;
    cin>>n>>x;
    vector<int> arr(n);
    for(int i = 0;i<n;i++)
    {
        cin>>arr[i];
    }
    Solution obj;
    int ans = obj.minimumCoins(n,x,arr);
    cout<<ans<<endl;
    return 0;
}