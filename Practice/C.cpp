#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
char gap = 32;
#define int long long
#define ll long long
#define lll __int128_t
#define pb push_back
typedef tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update>
    ordered_set;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define mod 1000000007
int a[200005];
vector<int>adj[200005];
int subTreeSum[200005];
vector<int>dfsArray;
int pos[200005];
int subTreeSize[200005];
int T = 0;

void dfs(int root, int par) {
    subTreeSize[root] = 1;
    subTreeSum[root] = a[root];
    pos[root] = T;
    dfsArray.push_back(root);
    T++;
    for (auto x : adj[root]) {
        if (x == par) continue;
        dfs(x, root);
        subTreeSize[root] += subTreeSize[x];
        subTreeSum[root] += subTreeSum[x];
    }
}

bool checkAncestor(int u, int v) {
    //cout << pos[u] << " " << subTreeSize[u] << "\n";
    if (pos[u] > pos[v]) return false;
    else if (pos[u] + subTreeSize[u] - 1 >= pos[v]) return true;
    else return false;
}

void solve() {
    T = 0;
    dfsArray.clear();
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) adj[i].clear();
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    int q;
    cin >> q;

    while (q--) {
        int u, v, x;
        cin >> u >> v >> x;
        if (!(checkAncestor(u, v) or checkAncestor(v, u))) {
            if (checkAncestor(x, u) and checkAncestor(x, v)) {
                cout << subTreeSum[x] << " ";
            }
            else if (checkAncestor(x, u)) {
                cout << subTreeSum[x] - subTreeSum[u] + subTreeSum[v] << " ";
            }
            else if (checkAncestor(x, v)) {
                cout << subTreeSum[x] - subTreeSum[v] + subTreeSum[u] << " ";
            }
            else {
                cout << subTreeSum[x] << " ";
            }
        }
        else {
            cout << subTreeSum[x] << " ";
        }
    }
    cout << endl;;
}


signed main() {
    freopen("input.txt", "r", stdin);

    // Printing the Output to output.txt file
    freopen("output2.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
