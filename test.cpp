#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
#define int long long
const int N = 1e5 + 10;
const int mod = 1e9 + 7;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<int>g[N];
int vis[N];
void dfs(int u) {
    ++vis[u];
    for (auto i : g[u]) {
        if (!vis[i]) dfs(i);
    }
}
signed main() {

    // freopen("input.txt", "r", stdin);
    freopen("input.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1000;
    cout << t << endl;
    while (t--) {
        int n = uniform_int_distribution<int>(1, 10)(rng);
        cout << n << endl;
        int s = uniform_int_distribution<int>(1, 10) (rng);
        for (int i = 0; i < n; ++i) {
            int x = uniform_int_distribution<int>(0, 10)(rng);
            cout << x << " ";
            // if (x == 3) cout << "S ";
            // else cout << char('A' + x) << " ";
            // int l = uniform_int_distribution<int>(1, 10)(rng);
            // int r = uniform_int_distribution<int>(1, 10)(rng);
            // cout << min(l, r) << " " << max(l, r) << " ";
            // if (x == 2) {
            //     int temp = uniform_int_distribution<int>(1, 4000)(rng);
            //     cout << temp - 2000;
            // }
            // cout << endl;
        }
        cout << endl;
        // int n = 1000;
        // cout << n << endl;
        // vector<int>arr(n + 1);
        // for (int i = 1;i <= n; ++i) arr[i] = i;
        // for (int i = 1; i <= 7 * n + 1; ++i) {
        //     int ix, jx;
        //     ix = uniform_int_distribution<int>(1, n)(rng);
        //     jx = uniform_int_distribution<int>(1, n) (rng);
        //     swap(arr[ix], arr[jx]);
        // }
        // for (int i = 1; i <= n; ++i) cout << arr[i] << " ";
        // cout << endl;
        // int n = 7;
        // int k = uniform_int_distribution<int>(1, n - 1)(rng);
        // cout << n << " " << k << endl;
        // bool isTree = false;
        // while (isTree == false) {
        //     for (int i = 1; i <= n; ++i) {
        //         g[i].clear();
        //         vis[i] = 0;
        //     }
        //     vector<int>arr;
        //     for (int i = 2; i <= n; ++i) {
        //         int x = uniform_int_distribution<int>(1, 10)(rng);
        //         arr.push_back(x);
        //         g[i].push_back(x);
        //         g[x].push_back(i);
        //     }
        //     dfs(1);
        //     int cnt = 0;
        //      for (int i = 1; i <= n; ++i) {
        //          if (vis[i]) ++cnt;
        //      }
        //      if (cnt == n) {
        //          for (int i : arr) cout << i << " ";
        //          // for (int i = 2;i <= n; ++i) cout << i << " " << arr[i - 2] << endl;

        //         cout << endl;
        //         break;
        //     }
        // }
        // // for (int i = 1;i <= n; ++i) cout << (uniform_int_distribution<int>(1, 10)(rng)) << " ";
        //  //cout << endl; 

        // int n = uniform_int_distribution <int>(1, 5)(rng);
        // int m = n * n;
        // set<int>st;
        // for (int i = 0; i < m; ++i) st.insert(i);
        // int val = -1;
        // cout << n << endl;
        // int pos = 0;
        // while (!st.empty()) {
        //     while (!st.count(val)) {
        //         val = uniform_int_distribution<int>(0, m + 1)(rng);
        //     }
        //     cout << val << " ";
        //     st.erase(val);
        //     val = -1;
        //     ++pos;

        //     if (pos == n) {
        //         cout << endl;
        //         pos = 0;
        //     }
        // }
        //int  x = n + 1;
        //while (n % x) {
          //  x = uniform_int_distribution<int>(2, n / 2) (rng);
       // }cout << n << " " << x << endl;


        // int lim = 5;
        // int n = uniform_int_distribution<int>(1, lim)(rng);
        // cout << n << endl;
        // for (int i = 1; i <= n; ++i) {
        //     int  x = uniform_int_distribution<int>(1, lim)(rng);

        //      int  y = uniform_int_distribution<int>(1, lim)(rng);
        //      cout << x << " " << y << endl;
        //  }
    }
}