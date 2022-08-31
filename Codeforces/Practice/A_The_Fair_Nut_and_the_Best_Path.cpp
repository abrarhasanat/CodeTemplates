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
const int N = 1e5 + 10;
int w[N];
ll ans = 0;
vector<pii> g[N];
ll dfs(int u, int from) {
    ll max1 = 0, max2 = 0;
    for (auto i : g[u]) {
        if (i.first == from) continue;
        ll cr_val = dfs(i.first, u) - i.second;
        if (cr_val > max1) {
            max2 = max1;
            max1 = cr_val;
        }
        else max2 = max(max2, cr_val);
    }
    ans = max(ans, max1 + max2 + w[u]);
    return w[u] + max1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 0; i < n - 1; ++i) {
        int u, v, c; cin >> u >> v >> c;
        g[u].emplace_back(v, c);
        g[v].emplace_back(u, c);
    }
    dfs(1, -1);
    cout << ans << endl;



}
