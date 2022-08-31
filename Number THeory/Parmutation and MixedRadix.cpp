#include <bits/stdc++.h>
#define  ll  long long
#define  pii pair<ll ,ll>
#define  pll pair<ll,ll>
#define  For(i, n) for(int i = 0; i < (n); ++i)
#define  lsb(x) ((x) & (-x))
#define  PI acos(-1)
#define  getbit(n, i) (((n) & (1LL << (i))) != 0)
#define  resetbit(n, i) ((n) & (~(1LL << (i))))
#define  setbit(n, i) ((n) | (1LL << (i)))
#define  togglebit(n, i) ((n) ^ (1LL << (i)))
#define  gap " " 
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
const int N = 3e6 + 10;
vector  <int > ParmutationToMixedRadix(vector < int > a) {
    ordered_set oset;
    int n = a.size();
    for (int i = 0; i < n; ++i) oset.insert(i);
    vector < int > ans(n);
    for (int i = 0; i < n; ++i) {
        ans[i] = oset.order_of_key(a[i]);
        oset.erase(a[i]);
    }
    return ans;
}
vector < int >  MixedRadixToParmutation(vector < int > a) {
    ordered_set  oset;
    int n = a.size();
    for (int i = 0; i < n; ++i) oset.insert(i);
    vector < int > ans(n);
    for (int i = 0; i < n; ++i) {
        auto it = oset.find_by_order(a[i]);
        ans[i] = *it;
        oset.erase(it);
    }
    return ans;
}
int  main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n;  cin >> n;
    vector < int > a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    vector < int > na = ParmutationToMixedRadix(a);
    vector < int > nb = ParmutationToMixedRadix(b);
    int carry = 0;
    vector < int >sum(n);
    for (int i = n - 1; i >= 0; --i) {
        int cr_sum = na[i] + nb[i] + carry;
        sum[i] = cr_sum % (n - i);
        carry = cr_sum / (n - i);
    }
    vector < int > ans = MixedRadixToParmutation(sum);
    for (int i = 0; i < n; ++i) cout << ans[i] << " ";


}
