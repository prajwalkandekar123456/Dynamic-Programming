// Problem
/*
Given an expression, A, with operands and operators (OR , AND , XOR), in how many ways can you evaluate the expression to true, by grouping in different ways?

Operands are only true and false.

Return the number of ways to evaluate the expression modulo 103 + 3.



Input Format:

The first and the only argument of input will contain a string, A.

The string A, may contain these characters:
    '|' will represent or operator 
    '&' will represent and operator
    '^' will represent xor operator
    'T' will represent true operand
    'F' will false
Output:

Return an integer, representing the number of ways to evaluate the string.
Constraints:

1 <= length(A) <= 150
Example:

Input 1:
    A = "T|F"

Output 1:
    1

Explanation 1:
    The only way to evaluate the expression is:
        => (T|F) = T 

Input 2:
    A = "T^T^F"
    
Output 2:
    0
    
Explanation 2:
    There is no way to evaluate A to a true statement.
*/

#include<bits/stdc++.h>
using namespace std;
// Time Complexity : O(N*N*2)
// Space Complexity : O(N*N*2)+O(N)
int mod=1000000007;

long long fun(int i,int j,int t,string &exp,vector<vector<vector<int >>> &dp) {
    if(i>j) return 0;
    if(i==j){
        if(t) return exp[i]=='T';
        else return exp[i]=='F';
    }
    long long res=0;
    if(dp[i][j][t]!=-1) return dp[i][j][t];
    for(int k=i+1;k<=j-1;k+=2){
       long long lt=fun(i,k-1,1,exp,dp);
       long long lf=fun(i,k-1,0,exp,dp);
       long long rt=fun(k+1,j,1,exp,dp);
       long long rf=fun(k+1,j,0,exp,dp);
       if(exp[k]=='&'){
           if(t) res+=(lt*rt)%mod;
           else res+=((lf*rt)%mod+(lf*rf)%mod+(lt*rf)%mod)%mod;
        }
       else if(exp[k]=='|'){
           if(t) res+=((lt*rt)%mod+(lt*rf)%mod+(lf*rt)%mod)%mod;
           else res+=(lf*rf)%mod;
       }
    else{
        if(t) res+=((lt*rf)%mod+(lf*rt)%mod)%mod;
           else res+=((lf*rf)%mod+(lt*rt)%mod)%mod;
    }
    }
    return dp[i][j][t]=res%mod;
} 
int evaluateExp(string &exp) {
    int n = exp.size();
    vector<vector<vector<int>>>dp(n,vector<vector<int>>(n,vector<int>(2,-1)));
    return fun(0,n-1,1,exp,dp)%mod;
}
int main()
{
    string s;
    cin>>s;
    int ans = evaluateExp(s);
    cout<<ans<<endl;
    return 0;
}