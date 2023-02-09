#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 9;

struct HopcroftKarp {
    static const int inf = 1e9;
    int n;
    vector<int> l, r, d;
    vector<vector<int>> g;
    HopcroftKarp(int _n, int _m) {
        n = _n;
        int p = _n + _m + 1;
        g.resize(p);
        l.resize(p, 0);
        r.resize(p, 0);
        d.resize(p, 0);
    }
    void add_edge(int u, int v) {
        g[u].push_back(v + n); //right id is increased by n, so is l[u]
    }
    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= n; u++) {
            if (!l[u]) d[u] = 0, q.push(u);
            else d[u] = inf;
        }
        d[0] = inf;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v : g[u]) {
                if (d[r[v]] == inf) {
                    d[r[v]] = d[u] + 1;
                    q.push(r[v]);
                }
            }
        }
        return d[0] != inf;
    }
    bool dfs(int u) {
        if (!u) return true;
        for (auto v : g[u]) {
            if (d[r[v]] == d[u] + 1 && dfs(r[v])) {
                l[u] = v;
                r[v] = u;
                return true;
            }
        }
        d[u] = inf;
        return false;
    }
    int maximum_matching() {
        int ans = 0;
        while (bfs()) {
            for (int u = 1; u <= n; u++) if (!l[u] && dfs(u)) ans++;
        }
        return ans;
    }
};
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    HopcroftKarp M(n, m);
    for (int i = 1;i <= n; ++i) {
        int  k; cin >> k;
        for (int j = 0; j < k; ++j) {
            int x; cin >> x;
            M.add_edge(i, x);
        }
    }
    cout << m - M.maximum_matching() << "\n";

    // while (q--) {
    //     int u, v;
    //     cin >> u >> v;
    //     M.add_edge(u, v);
    // }
    // cout << M.maximum_matching() << '\n';
    // return 0;
}