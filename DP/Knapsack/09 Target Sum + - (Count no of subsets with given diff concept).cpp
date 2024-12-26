// https://leetcode.com/problems/target-sum/

/*
You are given an integer array nums and an integer target.
You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.
For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
Return the number of different expressions that you can build, which evaluates to target.
*/


/*
Count no of subsets with given diff concept:

Let there be two subsets with sum s1 and s2 respectively
s1 + s2 = arrSum
s1 - s2 = diff

So solving the above equations, we get:
s1 = (arr_sum + diff) / 2
s2 = (arr_sum - diff) / 2

Therefore, question reduces to:
find number of subsets with sum as s1
OR
find number of subsets with sum as s2

Prefer using s2 since s2 has (arr_sum - diff), so s2 will be smaller than s1 which uses (arr_sum + diff)
*/



// Method 1.1
class Solution {
public:
    int n;

    int f(int i, int sum, vector<int>& a, int& target, vector<vector<int>>& dp) {
        if(i >= n) return sum == target;
        if(sum > target) return 0;

        if(dp[i][sum] != -1) return dp[i][sum];

        return dp[i][sum] = f(i + 1, sum + a[i], a, target, dp) + f(i + 1, sum, a, target, dp);
    }

    int findTargetSumWays(vector<int>& a, int target) {
        n = a.size();
        int sum = accumulate(a.begin(), a.end(), 0);

        if((sum - target) < 0) return 0;
        if((sum - target) % 2) return 0;
        int newTarget = (sum - target) / 2;

        if(newTarget > sum) return 0;

        vector<vector<int>> dp(n + 1, vector<int>(newTarget + 1, -1));

        return f(0, 0, a, newTarget, dp);
    }
};


// Method 1.2
class Solution {
public:
    int findTargetSumWays(vector<int>& a, int target) {
        int n = a.size();
        int sum = accumulate(a.begin(), a.end(), 0);

        if((sum - target) < 0 || (sum - target) % 2) return 0;
        int newTarget = (sum - target) / 2;

        if(newTarget > sum) return 0;

        vector<vector<int>> dp(n + 1, vector<int>(newTarget + 1, 0));

        // Base case: there's one way to achieve a sum of 0 (by taking no elements)
        dp[0][0] = 1;

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= newTarget; ++j) {
                if (j < a[i - 1]) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i - 1][j - a[i - 1]];
                }
            }
        }

        return dp[n][newTarget];
    }
};





// Method 2:
/*
Apart from Count no of subsets with given diff concept,
we need to check number of zeros in array.
Since -0 and +0 doesn't contribute in sum but contributes in result as (2 ^ TotalZeroCounts)
and an extra condition is also added

if(nums[i - 1] == 0) {
    dp[i][j] = dp[i-1][j];
}
*/

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int n = nums.size(), cnt0 = 0, arrSum = 0;
        for(int i = 0; i < n; i++) {
            if(nums[i] == 0) cnt0++;
            arrSum += nums[i];
        }
        
        if(S > arrSum) return 0;
        if((S + arrSum) % 2) return 0;
        
        int sum = (S + arrSum) / 2;

        int dp[n + 1][sum + 1];
        for (int i = 0; i <= n; i++) dp[i][0] = 1;
        for (int j = 1; j <= sum; j++) dp[0][j] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= sum; j++) {
                // extra condition
                if(nums[i - 1] == 0) {
                    dp[i][j] = dp[i-1][j];
                } else if (j < nums[i - 1]) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i - 1]];
                }
            }
        }

        return dp[n][sum] * pow(2, cnt0);
    }
};
