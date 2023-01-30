// Problem
/*
Given a string s, partition s such that every 
substring
 of the partition is a 
palindrome
.

Return the minimum cuts needed for a palindrome partitioning of s.

 

Example 1:

Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
Example 2:

Input: s = "a"
Output: 0
Example 3:

Input: s = "ab"
Output: 1
*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    bool isPalindrome(string &s)
    {
        string s1 = s;
        reverse(s1.begin(),s1.end());
        return s1==s;
    }
    // Recursion
    // Time Complexity : Exponential
    // SPace Complexity : O(N)
    int recc(int i,int n,string &s)
    {
        if(i == n) return 0;
        string temp="";
        int mini = INT_MAX;
        for(int j = i;j<n;j++)
        {
            temp+=s[j];
            if(isPalindrome(temp))
            {
                int cost = 1+recc(j+1,n,s);
                mini = min(mini,cost);
            }
        }
        return mini;
    }
    // Memoization
    // Time Complexity : O(N)+O(N)
    // Space Complexity:O(N)+O(N)+O(N)
    int memo(int i,int n,string &s,vector<int> &dp)
    {
        if(i == n) return 0;
        if(dp[i]!=-1) return dp[i];
        string temp = "";
        int mini = INT_MAX;
        for(int j = i;j<n;j++)
        {
            temp+=s[j];
            if(isPalindrome(temp))
            {
                int cost = 1+memo(j+1,n,s,dp);
                mini = min(mini,cost);
            }
        }
        return dp[i] = mini;
    }
public:
    int palindromePartitioning(string &s)
    {
        int n = s.size();
        // Recursion
        // int ans = recc(0,n,s);
        // Memoization
        vector<int>dp(n,-1);
        int ans = memo(0,n,s,dp);
        return ans-1;
    }
};
int main()
{
    string s;
    cin>> s;
    Solution obj;
    int ans = obj.palindromePartitioning(s);
    cout<<ans<<endl;
    return 0;
}