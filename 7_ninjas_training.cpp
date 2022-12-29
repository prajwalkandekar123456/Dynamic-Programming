// Problem
/*
A Ninja has an ‘N’ Day training schedule. He has to perform one of these three activities (Running, Fighting Practice, or Learning New Moves) each day. There are merit points associated with performing an activity each day. The same activity can’t be performed on two consecutive days. We need to find the maximum merit points the ninja can attain in N Days.

We are given a 2D Array POINTS of size ‘N*3’ which tells us the merit point of specific activity on that particular day. Our task is to calculate the maximum number of merit points that the ninja can earn.

Example:

*/

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    //Recursion
    //Time Complexity : O(N*4*3) + O(N)
    // Space Complexity : O(N) + O(N*4)
    int recc(int day,int last,vector<vector<int>> &points)
    {
        if(day == 0)
        {
            int maxi = 0;
            for(int task = 0;task<3;task++)
            {
                if(task!=last){
                maxi = max(maxi,points[0][task]);
                }
            }
            return maxi;
        }
        int maxi = 0;
        for(int task = 0;task<3;task++)
        {
            if(task!=last)
            {
                int point = points[day][task]+recc(day-1,task,points);
                maxi = max(maxi,point);
            }
        }
        return maxi;
    }

    // Memoization
    //Time Complexity : O(N*4*3)
    // Space Complexity : O(N) + O(N*4)
int memo(int day, int last, vector<vector<int>> &points,vector<vector<int>> &dp) {

  if (dp[day][last] != -1) return dp[day][last];

  if (day == 0) {
    int maxi = 0;
    for (int i = 0; i <= 2; i++) {
      if (i != last)
        maxi = max(maxi, points[0][i]);
    }
    return dp[day][last] = maxi;
  }

  int maxi = 0;
  for (int i = 0; i <= 2; i++) {
    if (i != last) {
      int activity = points[day][i] + memo(day - 1, i, points, dp);
      maxi = max(maxi, activity);
    }

  }

  return dp[day][last] = maxi;
}

// Tabulation
// Time Complexity : O(N*4*3)
// Space Complexity : O(N*4)
int tab(int n,vector<vector<int>> &points)
{
    vector < vector < int > > dp(n, vector < int > (4, 0));

  dp[0][0] = max(points[0][1], points[0][2]);
  dp[0][1] = max(points[0][0], points[0][2]);
  dp[0][2] = max(points[0][0], points[0][1]);
  dp[0][3] = max(points[0][0], max(points[0][1], points[0][2]));

  for (int day = 1; day < n; day++) {
    for (int last = 0; last < 4; last++) {
      dp[day][last] = 0;
      for (int task = 0; task <= 2; task++) {
        if (task != last) {
          int activity = points[day][task] + dp[day - 1][task];
          dp[day][last] = max(dp[day][last], activity);
        }
      }
    }

  }

  return dp[n - 1][3];
}

// Optimization
// Time Complexity : O(N*4*3)
// Space Complexity : O(4)
int opti(int n,vector<vector<int>> &points)
{
    vector < int > prev(4, 0);

  prev[0] = max(points[0][1], points[0][2]);
  prev[1] = max(points[0][0], points[0][2]);
  prev[2] = max(points[0][0], points[0][1]);
  prev[3] = max(points[0][0], max(points[0][1], points[0][2]));

  for (int day = 1; day < n; day++) {

    vector < int > temp(4, 0);
    for (int last = 0; last < 4; last++) {
      temp[last] = 0;
      for (int task = 0; task <= 2; task++) {
        if (task != last) {
          temp[last] = max(temp[last], points[day][task] + prev[task]);
        }
      }
    }

    prev = temp;

  }

  return prev[3];
}
public:
    int ninjaTraining(int n,vector<vector<int>> &points)
    {
        //Recursion
        int ans = recc(n-1,3,points);
        return ans;

        // Memoization
        vector<vector<int>> dp(n,vector<int>(3,0));
        int ans = memo(n-1,3,points,dp);
        return ans;

        //Tabulation
        int ans = tab(n-1,points);
        return ans;

        //Optimization
        int ans = opti(n-1,points);
        return ans;
    }
};

int main()
{
    // int n;
    // cin>>n;
    vector < vector < int > > points = {{10,40,70},
                                      {20,50,80},
                                      {30,60,90}};
    // for(int i = 0;i<n;i++)
    // {
    //     vector<int> temp;
    //     for(int j = 0;j<3;j++)
    //     {
    //         int x;
    //         cin>>x;
    //         temp.push_back(x);
    //     }
    //     points.push_back(temp);
    // }
    Solution obj;
    int ans = obj.ninjaTraining(3,points);
    cout<<ans<<endl;
    return 0;
}