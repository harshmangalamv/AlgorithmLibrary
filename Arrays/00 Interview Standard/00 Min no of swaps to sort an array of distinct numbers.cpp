/*
Que = Find min no of swaps required to sort an array consisting of distinct numbers
*/

class Solution {
    public: int minSwaps(vector < int > & a) {
        int n = a.size();
        vector < pair < int, int >> v;
        for (int i = 0; i < n; i++) {
            v.push_back({a[i], i});
        }
        sort(v.begin(), v.end());

        int swaps = 0;
        for (int i = 0; i < n; i++) {
            while (v[i].second != i) {
                swaps++;
                swap(v[i], v[v[i].second]);
            }
        }
        return swaps;
    }
};
