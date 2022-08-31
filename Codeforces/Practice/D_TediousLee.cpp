#include <bits/stdc++.h>
#define  ll  long long
#define  pii pair<int,int>
#define  pll pair<ll , ll>
#define  debug cout << "this far" << endl;
#define  For(i, n) for(int i = 0; i < (n); ++i)
#define  lsb(x) ((x) & (-x))
#define  PI acos(-1)
#define  line cout << endl;
#define  getbit(n, i) (((n) & (1LL << (i))) != 0)
#define  resetbit(n, i) ((n) & (~(1LL << (i))))
#define  setbit(n, i) ((n) | (1LL << (i)))
#define  togglebit(n, i) ((n) ^ (1LL << (i)))
#define  gap " "
using namespace std;
const int N = 2e6 + 10;
const int mod = 1e9 + 7;
ll dp[N][2];
ll cal(ll  n, ll  prevtaken) {

    if (n < 3) return 0;
    if (dp[n][prevtaken] != -1) return dp[n][prevtaken];
    if (prevtaken)
        return dp[n][prevtaken] = ((ll)(cal(n - 1, 0) + (ll)cal(n - 2, 0) + (ll)cal(n - 2, 0))) % mod;
    else {
        ll x = ((ll)cal(n - 1, 0) + (ll)cal(n - 2, 0) + (ll)cal(n - 2, 0));
        x = max(x, 4LL + (ll)cal(n - 1, 1) + (ll)cal(n - 2, 1) + (ll)cal(n - 2, 1));
        return dp[n][prevtaken] = x % mod ;
    }

}
int  main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll  t; cin >> t;
    for (ll i = 0; i < N; ++i) dp[i][0] = dp[i][1] = -1;
    while (t--) {
        ll  n; cin >> n;
        cout << cal(n, 0) << endl;
    }

}

