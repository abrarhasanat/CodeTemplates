#include <bits/stdc++.h>
#define  mx 100010
#define  ll long long
#define  pii pair<int,int>
#define  debug printf("%d\n", bug++);
#define  For(i,n) for(int i = 0; i < (n); ++i)
#define  INF 1 << 30
#define pb(x) push_back(x)
#define  mod  1000000007
#define PI acos(-1)
#define line printf("\n");
using  namespace std;
int bug  = 1;
vector<ll>prime;
void simpleseive(ll lim){
    prime.clear();
    bool mark[lim + 1];
    memset(mark , false, sizeof(mark));
    for(ll i = 2; i <= lim ; ++i){
        if(!mark[i]){
            prime.push_back(i);
            for(ll j = 2*i ; j <= lim; j += i)
                mark[j] = true;
        }
    }
}
ll segment_seive(ll left , ll right){
    ll lim = floor(sqrt(right));
    simpleseive(lim);
    ll n = right - left + 1;
    bool mark[n + 1];
    memset(mark, false, sizeof(mark));
    for(ll i = 0 ; i < prime.size() ; ++i){
      // prllf("%d\n" ,prime[i]);
        ll lolim = floor(left / prime[i]) * prime[i];
        if(lolim < left)
            lolim += prime[i];
        if(lolim == prime[i])
            lolim += prime[i];
        for(ll j = lolim ; j <= right ; j += prime[i]){
            //prllf("%d ", j);
            mark[j - left] = true;
        }
    }
    ll cnt = 0;
    for(ll i = left ; i <= right; ++i){
        if(!mark[i-left]) {
            cnt++;
           // prllf("%d ", i);
        }
    }

    return  cnt;
}
int main(){
    int t;
    scanf("%d", &t);
    For(tc,t){
        ll l ,r;
        scanf("%lld %lld", &l,&r);
        l = max(l,2LL);
        printf("Case %d: %d\n", tc + 1 , segment_seive(l,r));
    }
    return 0;

}

