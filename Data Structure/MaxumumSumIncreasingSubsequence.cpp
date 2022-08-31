#include <bits/stdc++.h>
#define  ll  long long
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
const ll N = 5e5 + 10;
ll tree[N * 4], arr[N], idx[N];
void build(ll at, ll left, ll right) {
    if (left == right) {
        tree[at] = arr[left];
        return;
    }
    ll m = (left + right) / 2;
    build(at * 2, left, m);
    build(at * 2 + 1, m + 1, right);
    tree[at] = max(tree[at * 2], tree[at * 2 + 1]);
}
ll query(ll at, ll left, ll right, ll start, ll end) {
    if (right < start || left > end) return 0;
    if (left >= start && right <= end) return tree[at];
    return max(query(at * 2, left, (left + right) / 2, start, end),
        query(at * 2 + 1, (left + right) / 2 + 1, right, start, end));
}
void update(ll at, ll left, ll right, ll idx, ll val) {
    if (right < idx || left > idx) return;
    if (left >= idx && right <= idx) {
        tree[at] = val;
        return;
    }
    update(at * 2, left, (left + right) / 2, idx, val);
    update(at * 2 + 1, (left + right) / 2 + 1, right, idx, val);
    tree[at] = max(tree[at * 2], tree[at * 2 + 1]);
}
map < ll, vector < int > > mp;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll  n; cin >> n;
    for (ll i = 1; i <= n; ++i) {
        ll r, h; cin >> r >> h;
        arr[i] = r * r * h;
        mp[arr[i]].push_back(i);
    }
    for (auto i : mp) {
        vector < ll > tmp;
        for (auto j : i.second) {
            ll mxx = query(1, 1, n, 1, j - 1);
            //update(1 , 1 , n , j , mxx + i.first)  ; 
            tmp.push_back(mxx + i.first);
        }
        for (int j = 0; j < tmp.size(); ++j) {
            update(1, 1, n, i.second[j], tmp[j]);
        }
    }


    cout << setprecision(24) << PI * (long double)(query(1, 1, n, 1, n));
}