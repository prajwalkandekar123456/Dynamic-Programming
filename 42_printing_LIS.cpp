// Problem
/*
Given an integer n and array of integers, returns the Longest Increasing subsequence which is lexicographically smallest.
LIS  of a given sequence such that all elements of the subsequence are sorted in increasing order. For example, the length of LIS for {10, 22, 9, 33, 21, 50, 41, 60, 80} is 6 and LIS is {10, 22, 33, 50, 60, 80}. 
 

Example 1:

Input:
n = 16
arr = [0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15]
Output:
0 4 6 9 13 15 
Explanation:
longest Increasing subsequence is 0 4 6 9 13 15  and the length of the longest increasing subsequence is 6.
Example 2:

Input:
n = 1
arr = [1]
Output:
1
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> longestIncreasingSubsequence(int n, vector<int>& arr) {
        vector<int> dp(n,1),hash(n);
        int lastIndex = 0;
        int maxi = 1;
        for(int i = 0;i<n;i++)
        {
            hash[i] = i;
            for(int j = 0;j<i;j++)
            {
                if(arr[i]>arr[j] && 1+dp[j]>dp[i]){
                    dp[i] = 1+dp[j];
                    hash[i] = j;
                }
            }
            if(dp[i]>maxi)
            {
                maxi = dp[i];
                lastIndex = i;
            }
        }
        vector<int> ans;
        ans.push_back(arr[lastIndex]);
        while(hash[lastIndex]!=lastIndex)
        {
            lastIndex = hash[lastIndex];
            ans.push_back(arr[lastIndex]);
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};


int main() {
        int N;
        cin >> N;
        vector<int> arr(N);
        for (int i = 0; i < N; i++) {
            cin >> arr[i];
        }
        Solution obj;
        vector<int> res = obj.longestIncreasingSubsequence(N, arr);
        for (auto x : res) cout << x << " ";
        cout << "\n";
    return 0;
}
