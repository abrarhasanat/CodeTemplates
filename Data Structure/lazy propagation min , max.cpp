#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <chrono>
 
#define  ll  long long
#define  pii pair<int,int>
#define  pll pair<ll , ll>
#define  debug cout << "this far" << endl;
#define  For(i, n) for(int i = 0; i < (n); ++i)
#define  mod 1000000007LL
#define  lsb(x) ((x) & (-x))
#define  PI acos(-1)
#define  line cout << endl;
#define  getbit(n, i) (((n) & (1LL << (i))) != 0)
#define  resetbit(n, i) ((n) & (~(1LL << (i))))
#define  setbit(n, i) ((n) | (1LL << (i)))
#define  togglebit(n, i) ((n) ^ (1LL << (i)))
//#define  ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
//using namespace __gnu_pbds;
//using namespace std::chrono;
using namespace std;
const int N = 1e6 + 10;
vector<pii > weapon, defense;
int mincost[N];
vector<tuple<int, int, int>> monsters;
int tree[N * 4], lazy[N * 4];
 
void prop(int at, int left, int right) {
    if (!lazy[at]) return;
    tree[at] += lazy[at];
    if (left != right) {
        lazy[at * 2] += lazy[at];
        lazy[at * 2 + 1] += lazy[at];
    }
    lazy[at] = 0;
}
 
void build(int at, int left, int right) {
    if (left == right) {
        tree[at] = -mincost[left];
        lazy[at] = 0;
        return;
    }
    build(at * 2, left, (left + right) / 2);
    build(at * 2 + 1, (left + right) / 2 + 1, right);
    tree[at] = max(tree[at * 2], tree[at * 2 + 1]);
    lazy[at] = 0;
}
 
void update(int at, int left, int right, int start, int end, int x) {
    prop(at, left, right);
    if (right < start || left > end) return;
    if (left >= start && right <= end) {
        lazy[at] += x;
        prop(at, left, right);
        return;
    }
    update(at * 2, left, (left + right) / 2, start, end, x);
    update(at * 2 + 1, (left + right) / 2 + 1, right, start, end, x);
    tree[at] = max(tree[at * 2], tree[at * 2 + 1]);
}
 
int query(int at, int left, int right, int start, int end) {
    prop(at, left, right);
    if (right < start || left > end) return -1e9;
    if (left >= start && right <= end) return tree[at];
    return max(query(at * 2, left, (left + right) / 2, start, end),
               query(at * 2 + 1, (left + right) / 2 + 1, right, start, end));
}
 
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, p;
    cin >> n >> m >> p;
    weapon.resize(n), defense.resize(m);
    for (int i = 0; i < n; ++i) cin >> weapon[i].first >> weapon[i].second;
    for (int i = 0; i < m; ++i) cin >> defense[i].first >> defense[i].second;
    for (int i = 0; i < p; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        monsters.emplace_back(x, y, z);
    }
    sort(weapon.begin(), weapon.end());
    sort(monsters.begin(), monsters.end());
    for (int i = 1; i < N; ++i) mincost[i] = 2e9 + 7;
    for (int i = 0; i < m; ++i) mincost[defense[i].first] = min(mincost[defense[i].first], defense[i].second);
    int mx = 1e6 + 1;
    build(1, 1, mx);
    int end = -1;
    int begin = 0;
    int ans = -1e9;
    while (begin < n) {
        while (end + 1 < p && get<0>( monsters[end + 1])< weapon[begin].first) {
            ++end;
            int x = get<2>(monsters[end]) ; 
            int y  = get<1>(monsters[end] )  ;
            update(1, 1, mx, y + 1 , mx, x) ;
        }
        ans = max(ans, -weapon[begin].second + query(1, 1, mx, 1, mx));
        ++begin;
    }
    cout << ans << endl;
}