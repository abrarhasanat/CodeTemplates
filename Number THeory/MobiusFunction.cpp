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
const ll N = 1e6 + 10;
int Lpf[N], mobius[N], freq[N];
void seive() {
    for (int i = 2; i < N; ++i) Lpf[i] = i;
    for (int i = 2; i * i < N; ++i) {
        if (Lpf[i] == i) {
            for (int j = i * i;j < N; j += i) {
                Lpf[j] = min(Lpf[j], i);
            }
        }
    }
}
void CalculateMobius() {
    seive();
    mobius[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (Lpf[i / Lpf[i]] == Lpf[i]) mobius[i] = 0;
        else mobius[i] = -1 * Lpf[i / Lpf[i]];
    }
}
//Funtion To get Number of Pairs in an Array that habve GCD ... 

ll gcdPairs() {  
    ll ans = 0;
    for (int i = 1; i < N; ++i) {
        if (!mobius[i]) continue;
        ll tmp = 0;
        for (int j = i; j < N; j += i) {
            tmp += freq[j];
        }
        tmp = (tmp * (tmp - 1)) / 3 * mobius[i]; 
        //cout << tmp << gap << i << endl;
        ans += tmp;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;  cin >> x;
        ++freq[x];
    }
    CalculateMobius(); 
    for(int i = 1 ; i <= 10 ; ++i) cout << mobius[i] << gap; 
    
    cout << gcdPairs() << endl; 

}
