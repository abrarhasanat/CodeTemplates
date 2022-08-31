#include<bits/stdc++.h>
#include<iostream>
#include <iomanip>
#include<math.h>
#include<fstream>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pb push_back
#define fi first
#define se second
#define gap ' '
#define abs(x) ((x)>0?(x):-(x))
#define INF 1e18
#define mod 1000000007
#define inf 1e9
#define pi 3.14159265358979
#include<time.h>
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int my_rand(int l, int r)
{
    return uniform_int_distribution<int>(l, r) (rng);
}
vector<int> v[10005];
int buyer[10005];
vector<int> own[10005];
int occ[10005];
int32_t main()
{

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int  tc = 1;
    //cin>>tc;

    for (int tt = 1; tt <= tc; tt++) {
        int n, m;
        cin >> n >> m;
        for (int i = 0;i < n;i++) {
            int k;
            cin >> k;
            for (int j = 0;j < k;j++) {
                int com;
                cin >> com;
                v[i + 1].pb(com);
                buyer[com]++;
                own[com].pb(i + 1);
            }
        }
        
         multiset<pii> ms;

        for (int i = 1;i <= m;i++) ms.insert({ buyer[i],i });
        int cnt = 0;
        while (!ms.empty()) {
            //cout<<ms.size()<<endl;
            auto it = ms.begin();
            pii p = *it;
            ms.erase(ms.begin());

            if (p.fi == 0) {
                continue;
            }
            else {
                for (auto x : own[p.se]) {
                    if (!occ[x]) {
                        occ[x] = 1;
                        //cout<<x<<endl;
                        for (auto z : v[x]) {
                            //if(z==p.se) continue;
                            auto it2 = ms.lower_bound({ buyer[z],z });
                            if (it2 == ms.end()) {
                                cout << buyer[z] << " fa " << x << " " << z << endl;
                                continue;
                            }
                            pii pp = *it2;
                            if (pp.se == z) {
                                ms.erase(it2);
                                buyer[z]--;
                                if (buyer[z] > 0) ms.insert({ buyer[z],z });
                            }

                            //cout<<x<<gap<<z<<endl;
                        }
                        cnt++;
                        break;
                    }
                }
                //if(ms.size())ms.erase(ms.begin());
            }
        }
        cout << m - cnt << "\n";

    }

}


