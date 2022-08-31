#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define gap " "
using namespace std;
const int  N = 5e5 + 10;
const int mod = 1e9 + 7;
inline bool cmp(const pii& a, const pii& b) {
    return a.first + a.second > b.first + b.second;
}
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pii>arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].first >> arr[i].second;
    }
    sort(arr.begin(), arr.end(), cmp);
    int ans = 0, x = 0, y = 0;
    for (auto i : arr) x += (i.first);
    int i = 0;
    while (i < n and x >= y) {
        ++ans ; 
        x -= arr[i].first ; 
        y += arr[i].first + arr[i].second ; 
        ++i ; 
    }
    cout << ans ;

}

//7
//1100010
