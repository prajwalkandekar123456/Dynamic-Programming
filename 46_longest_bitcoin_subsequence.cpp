// problem
/*
Given an array of positive integers. Find the maximum length of Bitonic subsequence. 
A subsequence of array is called Bitonic if it is first strictly increasing, then strictly decreasing.
 

Example 1:

Input: nums = [1, 2, 5, 3, 2]
Output: 5
Explanation: The sequence {1, 2, 5} is
increasing and the sequence {3, 2} is 
decreasing so merging both we will get 
length 5.
Example 2:

Input: nums = [1, 11, 2, 10, 4, 5, 2, 1]
Output: 6
Explanation: The bitonic sequence 
{1, 2, 10, 4, 2, 1} has length 6.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
    int longestBitonic(int n,vector<int> &arr)
    {
        vector<int> dp1(n,1);
        for(int i = 0;i<n;i++)
        {
            for(int j = 0;j<i;j++)
            {
                if(arr[i]>arr[j] && dp1[i]<dp1[j]+1)
                {
                    dp1[i] = dp1[j]+1;
                }
            }
        }
        vector<int> dp2(n,1);
        for(int i = n-1;i>=0;i--)
        {
            for(int j = n-1;j>i;j--)
            {
                if(arr[i]>arr[j] && dp2[i]<dp2[j]+1)
                {
                    dp2[i] = dp2[j]+1;
                }
            }
        }
        int maxi= 0;
        for(int i = 0;i<n;i++)
        {
            maxi = max(maxi,dp1[i]+dp2[i]-1);
        }
        return maxi;
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
    int ans = obj.longestBitonic(n,arr);
    cout<<ans<<endl;
    return 0;
}