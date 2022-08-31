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
int n, m, k, vis[N], isspecial[N], par[N], sz[N], x[N];
struct e {
    int  u, v, w;
    e(int x1, int x2, int x3) : u(x1), v(x2), w(x3) {};
    bool operator < (const e& p) const {
        return w < p.w;
    }
};
vector<e>edges;
int find(int u) {
    if (u == par[u])
        return u;
    return par[u] = find(par[u]);
}
vector< pii > g[N];
void mst() {
    for (int i = 1; i <= n; ++i) par[i] = i, sz[i] = 1;
    sort(edges.begin(), edges.end());
    for (auto i : edges) {
        int x = find(i.u);
        int y = find(i.v);
        if (x == y) continue;
        if (sz[x] < sz[y]) swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
        g[i.v].emplace_back(i.u, i.w);
        g[i.u].emplace_back(i.v, i.w);
    }
}
int max_ans = 0;
void dfs(int u, int from, int mx_sofar) {
    if (isspecial[u]) max_ans = max(mx_sofar ,  max_ans);
    for (auto i : g[u]) {
        if (i.first == from) continue;
        dfs(i.first, u, max(i.second, mx_sofar));
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 0; i < k; ++i) {
        cin >> x[i];
        isspecial[x[i]]++;
    }
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }
    mst();
    dfs(x[0] , -1 , 0) ;
    for (int i = 0; i < k; ++i) cout << max_ans << gap;
    line





}
