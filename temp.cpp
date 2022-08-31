#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <cfloat>
#include <map>
#include <utility>
#include <set>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>
#include <complex>
#include <stack>
#include <queue>
#include <memory.h>
#include <ctime>
#include <bits/stdc++.h>

using namespace std;
vector<pair<pair<int , int> , int>>points;
double findDis(pair<int , int >&a , pair<int , int>&b) {
    return (double) ((a.first - b.first) * (a.first - b.first) * 1.000000 +
                     (a.second - b.second) * (a.second - b.second) * 1.000000);
}
pair<pair<double , double> , pair<pair<int , int> , pair<int , int>>> bruteForce(vector<pair<pair<int , int> , int>> &a , vector<pair<pair<int , int> , int>> &b) {
    double minDis = LONG_LONG_MAX;
    double secondMinDis = LONG_LONG_MAX;
    pair<int, int> disPair, secondDisPair;
    disPair = secondDisPair = {-1, -1};
    for (auto &x : a) {
        for (auto &y : b) {
            double temp = findDis(x.first, y.first);
            if (minDis > temp) {
                secondMinDis = minDis;
                secondDisPair.first = disPair.first;
                secondDisPair.second = disPair.second;
                minDis = temp;
                disPair.first = x.second;
                disPair.second = y.second;
            } else if (secondMinDis > temp) {
                secondMinDis = temp;
                secondDisPair.first = x.second;
                secondDisPair.second = y.second;
            }
        }
    }
    return make_pair(make_pair(minDis, secondMinDis), make_pair(disPair, secondDisPair));
}
pair<pair<double , double> , pair<pair<int , int> , pair<int , int>>> findSecondMin(int i , int j) {
    if (i == j) {
        return make_pair(make_pair((double) LONG_LONG_MAX, (double) LONG_LONG_MAX),
                         make_pair(make_pair(i, j), make_pair(i, j)));
    }
    int mid = (i + j) / 2;
    auto pr1 = findSecondMin(i, mid);
    auto pr2 = findSecondMin(mid + 1, j);
    double minDis = LONG_LONG_MAX;
    double secondMinDis = LONG_LONG_MAX;
    pair<int, int> disPair, secondDisPair;
    disPair = {-1, -1};
    secondDisPair = {-1, -1};
    if (pr1.first.first <= pr2.first.first) {
        minDis = pr1.first.first;
        disPair = pr1.second.first;
        if (pr1.first.second <= pr2.first.first) {
            secondMinDis = pr1.first.second;
            secondDisPair = pr1.second.second;
        } else {
            secondMinDis = pr2.first.first;
            secondDisPair = pr2.second.first;
        }
    } else {
        minDis = pr2.first.first;
        disPair = pr2.second.first;
        if (pr2.first.second <= pr1.first.first) {
            secondMinDis = pr2.first.second;
            secondDisPair = pr2.second.second;
        } else {
            secondMinDis = pr1.first.first;
            secondDisPair = pr1.second.first;
        }
    }

    vector<pair<pair<int, int>, int>> a, b;
    for (int iter = i; iter <= j; iter++) {
        if (points[iter].first.first <= points[mid].first.first and
            (double) (points[mid].first.first - secondMinDis) <= (double) points[iter].first.first) {
            a.push_back({{points[iter].first.first, points[iter].first.second}, points[iter].second});
        }
        if (points[iter].first.first > points[mid].first.first and
            (double) (points[mid].first.first + secondMinDis) >= (double) points[iter].first.first) {
            b.push_back({{points[iter].first.first, points[iter].first.second}, points[iter].second});
        }
    }
    auto pr3 = bruteForce(a, b);
    if (pr3.first.first <= minDis) {
        if (minDis <= pr3.first.second) {
            secondMinDis = minDis;
            secondDisPair = disPair;
        } else {
            secondMinDis = pr3.first.second;
            secondDisPair = pr3.second.second;
        }
        minDis = pr3.first.first;
        disPair = pr3.second.first;
    } else if (pr3.first.first <= secondMinDis) {
        secondMinDis = pr3.first.first;
        secondDisPair = pr3.second.first;
    }
    return make_pair(make_pair(minDis, secondMinDis), make_pair(disPair, secondDisPair));
}

int main() { 
    freopen("input.txt" , "r" , stdin) ;
    freopen("output.txt" , "w" , stdout) ;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        points.push_back({{x, y}, i - 1});
    }
    sort(points.begin(), points.end());
    auto res = findSecondMin(0, n - 1);
    cout << res.second.second.first << " " << res.second.second.second << "\n";
    cout << fixed << setprecision(4);
    res.first.second = sqrt(res.first.second);
    cout << res.first.second << "\n";
}
/*
3
0 0
1 0
3 0
*/
/*
10
-2289 9295
3137 3748
-5033 5679
7729 -432
9262 16
8341 -5462
-4163 3577
1710 -3328
-8676 -3161
5106 3295
*/
/*
5
-9765 2172
-4808 7289
955 -2187
9279 -9856
6332 -2249


10
5 2
5 4
5 11
5 20
11 2
11 9
11 33
11 90
6 2
6 123
*/