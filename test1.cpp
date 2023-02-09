#include <bits/stdc++.h>
#define int long long 
#define pii pair<int,int>
#define ll long long
using namespace std;
const int MAX = 1e6 + 10;
const int N = 1e5 + 10;
const int mod = 1e18;
vector<int>g[N];
int visited[N];
vector<int>nodes;
void dfs(int u, int n) {
    if (u < 1 or u > n)  return;
    visited[u]++;
    for (auto i : g[u]) {
        if (i < 1 or i > n) continue;
        if (!visited[i]) dfs(i, n);
    }
    nodes.push_back(u);

}
signed main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<int>to(n + 1), vis(n + 1, 0), bef(n + 1, 0), isRec(n + 1, 0), isFirst(n + 1, 0);
        for (int i = 1; i <= n; ++i) cin >> to[i];
        for (int i = 1; i <= n; ++i) g[i].clear();
        for (int i = 1;i <= n; ++i) {
            g[i].push_back(i + to[i]);
            visited[i] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            if (!visited[i]) dfs(i, n);
        }
        reverse(nodes.begin(), nodes.end());

        int recSizes = 0;
        bool isOneOut = true;
        vector<int>seqFirst;
        for (int i = 1; i <= n; ++i) {
            if (vis[i]) continue;
            int curr = i;
            int sz = 0;
            bool found = false;
            vector<int>tmp;
            set < int > nvis;
            while (curr >= 1 and curr <= n) {
                if (nvis.count(curr)) {
                    found = true;
                    break;
                }
                if (vis[curr]) {
                    if (isRec[curr])
                        found = true;
                    // bef[curr] += sz;
                    break;
                }

                nvis.insert(curr);
                tmp.push_back(curr);
                bef[curr] = (sz > 0);
                sz++;
                ++vis[curr];
                curr += to[curr];

            }
            if (found) {
                if (i == 1) isOneOut = false;
                recSizes += tmp.size();
                for (auto i : tmp) isRec[i] ++;
            }

            if (i == 1) {
                seqFirst = tmp;
                for (auto i : tmp) isFirst[i]++;
            }

        }

        int ans = 0;

        if (isOneOut) {
            for (int i = 1; i <= n; ++i) {
                if (!isFirst[i])
                    ans += 2 * n + 1;
            }




        }

        else {
            for (int i = 1; i <= n; ++i) {
                if (!isFirst[i]) continue;
                ans += 2 * n + 1 - recSizes;
            }
        }
        cout << ans << "\n";

    }

}