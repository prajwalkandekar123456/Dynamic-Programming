// Problem
/*
Given an array, ‘Arr’ of length ‘n’, count the number of longest increasing subsequences (LIS).
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
    // Time Complexity : O(N*N)
    // Space COmplexity : O(N)
public:
    int NumberOfLIS(int n,vector<int> &arr)
    {
        vector<int> dp(n,1);
        vector<int> cnt(n,1);
        int maxLen = 1;
        for(int i = 1;i<n;i++)
        {
            for(int j = 0;j<i;j++)
            {
                if(arr[i]>arr[j] && dp[i] == dp[j]+1)
                {
                    cnt[i]+=cnt[j];
                }
                if(arr[i]>arr[j] && dp[i]<dp[j]+1)
                {
                    dp[i] = dp[j]+1;
                    cnt[i] = cnt[j];
                }
            }
            maxLen = max(maxLen,dp[i]);
        }
        int ans = 0;
        for(int i = 0;i<n;i++)
        {
            if(dp[i] == maxLen)
            {
                ans+=cnt[i];
            }
        }
        return ans;
    }
};
int main()
{
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i = 0;i<n;i++)
    {
        cin>>arr[i];
    }
    Solution obj;
    int ans = obj.NumberOfLIS(n,arr);
    cout<<ans<<endl;
    return 0;
}