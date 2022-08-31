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
#define printall(container) for(auto val  : container) cout << val << gap ; line ; 
using namespace std;
const int N = 1e5 + 10;

int n , a[N] ;

vector < int > cal_lis() {
    int   b[N], f[N], answer = 0;
    for (int i = 1; i <= n; ++i) {
        f[i] = upper_bound(b + 1, b + answer + 1, a[i]) - b;
        answer = max(answer, f[i]);
        b[f[i]] = a[i];
    }
    vector < int > ans;
    int req = answer;
    for (int i = n; i >= 1;--i) {
        if (f[i] == req) {
            ans.push_back(a[i]);
            req--;
        }
    }
    cout << answer << endl ; 
    reverse(ans.begin(), ans.end());
    for (auto i : ans) cout << i << gap;
    line 

    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;cin >> t;
    while (t--) {
    
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        cal_lis() ; 
       
    }
}