// Problem
/*
We are given an array of strings (sat words[ ]), and we need to return the longest string chain. This longest string chain is defined as:

A subsequence of words[ ] of the string.
Every element of this subsequence ( a string) except the first one can be formed by inserting a single character into the previous element.
The first element of this subsequence can be any string from the words[ ] array.
*/

#include<bits/stdc++.h>
using namespace std;

// Time Complexity : O(N*N*L)
// Space Complexity : O(N)
class Solution{
private:
    // bool comp(string &s1,string &s2)
    // {
    //     return s1.size()<s2.size();
    // }
    bool checkPossible(string &s1,string &s2)
    {
        if(s1.size()!=s2.size()+1) return false;
        int first = 0;
        int second = 0;
        while(first<s1.size())
        {
            if(s1[first] == s2[second])
            {
                first++;
                second++;
            }
            else{
                first++;
            }
        }
        if(s1.size() == first && second == s2.size()) return true;
        return false;
    }
public:
    int longestChain(int n,vector<string> &arr)
    {
        vector<int> dp(n,1);
        sort(arr.begin(),arr.end());
        int maxi = 1;
        for(int i = 0;i<n;i++)
        {
            for(int j = 0;j<n;j++)
            {
                if(dp[i]<dp[j]+1 && checkPossible(arr[i],arr[j]))
                {
                    dp[i] = dp[j]+1;
                }
                if(maxi<dp[i])
                {
                    maxi = dp[i];
                }
            }
        }
        return maxi;
    }
};
int main()
{
    int n;
    cin>>n;
    vector<string> arr(n);
    for(int i = 0;i<n;i++)
    {
        cin>>arr[i];
    }
    Solution obj;
    int ans = obj.longestChain(n,arr);
    cout<<ans<<endl;
    return 0;
}