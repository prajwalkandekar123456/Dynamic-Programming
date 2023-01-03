// Problem
/*
A thief wants to rob a store. He is carrying a bag of capacity W. The store has ‘n’ items. Its weight is given by the ‘wt’ array and its value by the ‘val’ array. He can either include an item in its knapsack or exclude it but can’t partially have it as a fraction. We need to find the maximum value of items that the thief can steal.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
// Recursion
// Time Complexity : O(2^N)
// Space Complexity : O(N)
int recc(int index,vector<int> &weight,vector<int> &value, int maxWeight)
{
    if(index == 0)
    {
        if(maxWeight>=weight[0]) return value[0];
        else return 0;
    }
    int notTake = 0+recc(index-1,weight,value,maxWeight);
    int take = INT_MIN;
    if(maxWeight>=weight[index]) take = value[index]+recc(index-1,weight,value,maxWeight-weight[index]);
    return max(take,notTake);
}

// Memoization
// Time Complexity : O(N*K)
// Space Complexity : O(N*K) + O(N)
int memo(int index,vector<int> &weight,vector<int> &value, int maxWeight,vector<vector<int>> &dp)
{
    if(index == 0)
    {
        if(maxWeight>=weight[0]) return value[0];
        else return 0;
    }
    if(dp[index][maxWeight]!=-1) return dp[index][maxWeight];
    int notTake = 0+memo(index-1,weight,value,maxWeight,dp);
    int take = INT_MIN;
    if(maxWeight>=weight[index]) take = value[index]+memo(index-1,weight,value,maxWeight-weight[index],dp);
    return dp[index][maxWeight] = max(take,notTake);
}

// Tabulation
// Time Complexity : O(N*K)
// Space Complexity : O(N*K)
int tab(int n,vector<int> &weight,vector<int> &value,int maxWeight)
{
    vector<vector<int>> dp(n,vector<int> (maxWeight+1,0));
    for(int i= weight[0];i<=maxWeight;i++)
    {
        dp[0][i] = value[0];
    }
    for(int i = 1;i<n;i++)
    {
        for(int j = 0;j<=maxWeight;j++)
        {
            int notPick = 0+dp[i-1][j];
            int pick = INT_MIN;
            if(j>=weight[i]) pick = value[i]+dp[i-1][j-weight[i]];
            dp[i][j] = max(pick,notPick);
        }
    }
    return dp[n-1][maxWeight];
}

// Optimization
// Time Complexity : O(N*K)
// Space COmplexity : O(N)
int opti(vector<int>& wt, vector<int>& val, int n, int W){
    
    vector<int> prev(W+1,0);
    
    //Base Condition
    
    for(int i=wt[0]; i<=W; i++){
        prev[i] = val[0];
    }
    
    for(int ind =1; ind<n; ind++){
        for(int cap=W; cap>=0; cap--){
            
            int notTaken = 0 + prev[cap];
            
            int taken = INT_MIN;
            if(wt[ind] <= cap)
                taken = val[ind] + prev[cap - wt[ind]];
                
            prev[cap] = max(notTaken, taken);
        }
    }
    
    return prev[W];
}
public:
    int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
// return recc(n-1,weight,value,maxWeight);
    vector<vector<int>> dp(n,vector<int> (maxWeight+1,-1));
//     return memo(n-1,weight,value,maxWeight,dp);
    return tab(n,weight,value,maxWeight);
    // return opti(weight,value,n,maxWeight);
}
};
int main()
{
    int n;
    cin>>n;
    vector<int> weight(n),value(n);
    for(int i = 0;i<n;i++)
    {
        cin>>weight[i];
    }
      for(int i = 0;i<n;i++)
    {
        cin>>value[i];
    }
    int maxWeight;
    cin>> maxWeight;
    Solution obj;
    int ans = obj.knapsack(weight,value,n,maxWeight);
    cout<<ans<<endl;
    return 0;
}