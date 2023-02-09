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
ll  tree[N * 4], lazy[N * 4];

void prop(ll  at, ll  left, ll  right) {
    if (!lazy[at]) return;
    tree[at] += ((right - left + 1 ) * lazy[at]);
    if (left != right) {
        lazy[at * 2] += lazy[at];
        lazy[at * 2 + 1] += lazy[at];
    }
    lazy[at] = 0;
}

void build(ll  at, ll  left, ll  right) {
    if (left == right) {
        tree[at] =  0 ;
        lazy[at] = 0;
        return;
    }
    build(at * 2, left, (left + right) / 2);
    build(at * 2 + 1, (left + right) / 2 + 1, right);
    tree[at] = tree[at * 2] + tree[at * 2 + 1];
    lazy[at] = 0;
}

void update(ll  at, ll  left, ll  right, ll  start, ll  end, ll  x) {
    prop(at, left, right);
    if (right < start || left > end) return;
    if (left >= start && right <= end) {
        lazy[at] += x;
        prop(at, left, right);
        return;
    }
    update(at * 2, left, (left + right) / 2, start, end, x);
    update(at * 2 + 1, (left + right) / 2 + 1, right, start, end, x);
    tree[at] = tree[at * 2] +  tree[at * 2 + 1];
}

ll  query(ll  at, ll  left, ll  right, ll  start, ll  end) {
    prop(at, left, right);
    if (right < start || left > end) return 0;
    if (left >= start && right <= end) return tree[at];
    ll p = query(at * 2, left, (left + right) / 2, start, end );
    ll q  = query(at * 2 + 1, (left + right) / 2 + 1, right, start, end) ;
    return p + q  ;
}


int main() {
    int t ;
    scanf("%d" , &t) ;
    For(tc , t) {
        int n, m;
        scanf("%d %d" , &n , &m);
        build(1 , 1 , n ) ;
        printf("Case %d:\n" , tc + 1) ;
        while (m--){
            int  cs , x ,y ;
            scanf("%d %d %d" , &cs , &x , &y) ;
            if(cs == 1)  {
                printf("%lld\n" , query(1, 1, n , x + 1 , y + 1)) ;
            }
            else {
                int z ; scanf("%d" , &z) ;
                update(1 ,1  , n ,x + 1 ,y + 1 ,z)  ;
            }
        }
    }
}