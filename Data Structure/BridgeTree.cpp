#include <bits/stdc++.h>
#define  ll   long long
#define  pii pair<ll ,ll>
#define  pll pair<ll,ll>
#define  For(i, n) for(ll i = 0; i < (n); ++i)
#define  lsb(x) ((x) & (-x))
#define  PI acos(-1)
#define  getbit(n, i) (((n) & (1LL << (i))) != 0)
#define  resetbit(n, i) ((n) & (~(1LL << (i))))
#define  setbit(n, i) ((n) | (1LL << (i)))
#define  togglebit(n, i) ((n) ^ (1LL << (i)))
#define  gap " " 
using namespace std;
const int N = 3e5 + 10;
vector  < int > g[N], newG[N]; ;
int visited[N], tin[N], low[N];
map  < pii, bool > isBriedge;
int timer = 0;
void dfs(int v, int p = -1) {  // Maeking All bridges  
    visited[v]++;
    tin[v] = low[v] = timer++;
    for (int to : g[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        }
        else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
                isBriedge.insert(make_pair(make_pair(v, to), true));
                isBriedge.insert(make_pair(make_pair(to, v), true));
            }
        }
    }
}
int  ComponetNumber = 1;
queue  < int > q[N];
void dfsbfs(int u) {
    int CurrentComp = ComponetNumber;
    q[CurrentComp].push(u);
    ++visited[u];
    while (!q[CurrentComp].empty()) {
        int v = q[CurrentComp].front();
        ++visited[v];
        q[CurrentComp].pop();
        for (auto i : g[v]) {
            if (visited[i]) continue;
            if (isBriedge.count(make_pair(v, i))) {
                ++ComponetNumber;
                newG[CurrentComp].push_back(ComponetNumber);
                newG[ComponetNumber].push_back(CurrentComp);
                dfsbfs(i);
            }
            else {
                q[CurrentComp].push(i);
            }
        }
    }
}
int Best = 0, BestNode = 0; ;
void diameter(int u, int d, int p) {
    //cout << u << gap << d << endl;
    if (d > Best) {
        Best = d;
        BestNode = u;
    }
    for (auto i : newG[u]) {
        if (i == p) continue;
        diameter(i, d + 1, u);
    }

}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1) ;
    for (int i = 1;i <= n; ++i) visited[i] = 0;
    dfsbfs(1);
    diameter(1, 0, -1);
    Best = 0;
    diameter(BestNode, 0, -1);
    cout << Best << endl;




}

