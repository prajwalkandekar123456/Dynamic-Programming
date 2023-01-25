// Problem
/*
Given an array of integers, find the length of the longest (strictly) increasing subsequence from the given array.

Example 1:

Input:
N = 16
A[]={0,8,4,12,2,10,6,14,1,9,5
     13,3,11,7,15}
Output: 6
Explanation:Longest increasing subsequence
0 2 6 9 13 15, which has length 6
Example 2:

Input:
N = 6
A[] = {5,8,3,7,9,1}
Output: 3
Explanation:Longest increasing subsequence
5 7 9, with length 3
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
    // Time Complexity : O(N*logn)
    // Space Complexity : O(N)
    int LIS(int n,vector<int> &arr)
    {
        vector<int> temp;
        temp.push_back(arr[0]);
        for(int i = 1;i<n;i++)
        {
            if(arr[i]>temp.back())
            {
                temp.push_back(arr[i]);
            }
            else{
                int ind = lower_bound(temp.begin(),temp.end(),arr[i])-temp.begin();
                temp[ind] = arr[i];
            }
        }
        return temp.size();
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
    int ans = obj.LIS(n,arr);
    cout<<ans<<endl;
    return 0;
}