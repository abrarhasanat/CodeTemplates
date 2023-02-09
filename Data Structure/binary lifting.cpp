
///CF 739 B binary lifting // 

#include <bits/stdc++.h>
#define  ll  long long
#define  pii pair<int,int>
#define  pll pair<ll,ll>
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
#define  printall(container) for(auto val  : container) cout << val << gap ; line ; 
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
using namespace std;
const ll  N = 2e5 + 10  ; 
vector <pii> g[N] ; 
ll par[N][23] ,  sum[N]  , dep[N] , arr[N] ; 
void dfs(ll  u  , ll  p , ll d) { 
    par[u][0]  = p ;
    dep[u] = d ; 
    for(auto i : g[u]) { 
        if(i.first != p )   dfs(i.first , u , d + i.second ) ; 
    }
}
void preprocess(ll  n )   {
    for(ll  j = 1 ;j <= 20; ++j ) { 
        for(ll  i = 1 ; i  <= n ; ++i) { 
            par[i][j] = par[par[i][j - 1]][j - 1] ; 
        }
    }

}
void update(ll  u ,  ll val ) { 
    for(ll  i  = 20 ; i >= 0 ;  --i) { 
        if(dep[par[u][i]] >= val) u = par[u][i] ; 
    }
    if(u == 1) return   ; 
    sum[par[u][0]] -- ;  
}
void dfs2(ll  u ) { 
    if(u != 1) { 
        update(u , dep[u] - arr[u])    ; 
    }
    for(auto i  : g[u]) { 
        dfs2(i.first) ; 
        sum[u] += sum[i.first]; 
    }
}

int main () { 
    ios_base :: sync_with_stdio(false) ; cin.tie(nullptr)  ;
    ll  n  ;  cin >>  n ; 
    for(ll  i =  1  ;i  <= n ; ++i ) cin >> arr[i] ,  sum[i]   = 1 ; 
    for(ll  i = 2 ; i <=  n ; ++i) { 
        ll  x  , w ; cin >> x >> w ; 
        g[x].emplace_back(i , w)  ; 
    }
    dfs(1 , 1 , 0) ; 
    preprocess(n) ; 
    dfs2(1) ;
    for(ll  i = 1 ; i  <= n ; ++i) cout << sum[i] - 1 << " " ; 
}