/*
Que = Find min no of swaps required to sort an array consisting of distinct numbers
*/

// NOTE: Array must have distinct elements for the below solutions.

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




class Solution {
    public: int minSwaps(vector < int > & a) {
        int n = a.size();
        vector < int > aSorted = a;
        sort(aSorted.begin(), aSorted.end());

        unordered_map < int, int > idxMap;
        for (int i = 0; i < n; i++) {
            idxMap[a[i]] = i;
        }

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == aSorted[i]) continue;
            
            cnt++;
            int idx = idxMap[aSorted[i]];
            swap(a[i], a[idx]);

            idxMap[a[idx]] = idx;
        }

        return cnt;
    }
};
