// Problem
/*
Given a set of distinct positive integers nums, return the largest subset answer such that every pair (answer[i], answer[j]) of elements in this subset satisfies:

answer[i] % answer[j] == 0, or
answer[j] % answer[i] == 0
If there are multiple sequences with the largest size, return any of them.

Example 1:

Input:
n = 3
arr = [1,2,3]
Output:
[1,2]
Explanation:
Largest Divisble Subset is [1,2].
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
    // Time Complexity : O(N*N)
    // Space Complexity : O(N)
    vector<int> divisibleSet(int n,vector<int> &arr)
    {
        vector<int> dp(n,1);
        vector<int> hash(n,1);
        sort(arr.begin(),arr.end());
        for(int i = 0;i<n;i++)
        {
            hash[i] = i;
            for(int j = 0;j<=i-1;j++)
            {
                if(arr[i]%arr[j] == 0 && 1+dp[i]>dp[i])
                {
                    dp[i] = 1+dp[i];
                    hash[i] = j;
                }
            }
        }
        int ans = -1;
        int lastIndex = -1;
        for(int i = 0;i<n;i++)
        {
            if(ans<hash[i])
            {
                ans = hash[i];
                lastIndex = i;
            }
        }
        vector<int> temp;
        temp.push_back(arr[lastIndex]);
        while(lastIndex!=hash[lastIndex])
        {
            lastIndex = hash[lastIndex];
            temp.push_back(arr[lastIndex]);
        }
        reverse(temp.begin(),temp.end());
        return temp;
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
    vector<int> ans = obj.divisibleSet(n,arr);
    for(int i = 0;i<ans.size();i++)
    {
        cout<<ans[i]<<" ";
    }
    cout<<endl;
    return 0;
}
