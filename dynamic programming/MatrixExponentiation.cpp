#include <bits/stdc++.h>
#define  ll  long long
#define  pii pair<ll  ,ll >
#define  pll pair<ll,ll>
#define  For(i, n) for(ll  i = 0; i < (n); ++i)
#define  lsb(x) ((x) & (-x))
#define  PI acos(-1)
#define  getbit(n, i) (((n) & (1LL << (i))) != 0)
#define  resetbit(n, i) ((n) & (~(1LL << (i))))
#define  setbit(n, i) ((n) | (1LL << (i)))
#define  togglebit(n, i) ((n) ^ (1LL << (i)))
#define  gap  " "
using namespace std;
const ll  N = 101;
const ll mod = 1e9 + 7;
ll mp[N];
vector<vector<ll >> multiply(vector<vector<ll>>a, vector  < vector<ll>>b) {
    vector < vector <ll >> mul(N);
    for (ll i = 0; i < N; i++) {
        mul[i].assign(N, 0);
        for (ll j = 0; j < N; j++) {
            mul[i][j] = 0;
            for (ll k = 0; k < N; k++)
                mul[i][j] += (a[i][k] * b[k][j]) % mod ; 
                mul[i][j] %= mod ;
        }
    }
    return mul;
}
vector<vector<ll >> MatrixPow(vector<vector<ll >> F, ll p) {
    if (p == 1) return F;
    vector<vector<ll>> res = MatrixPow(F, p / 2);
    res = multiply(res, res);
    if (p % 2) {
        res = multiply(res, F);
    }
    return res;
}