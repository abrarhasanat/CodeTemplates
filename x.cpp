#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
#define getbit(n, i) (((n) & (1LL << (i))) != 0) 
#define setbit0(n, i) ((n) & (~(1LL << (i)))) 
#define setbit1(n, i) ((n) | (1LL << (i))) 
#define togglebit(n, i) ((n) ^ (1LL << (i))) 
#define lastone(n) ((n) & (-(n))) 
char gap = 32;
#define int long long
#define ll long long 
#define lll __int128_t
#define pb push_back
typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll hashPrime = 1610612741;
#define d 51
int basis[d]; // basis[i] keeps the mask of the vector whose f value is i

int sz; // Current size of the basis

void insertVector(int mask) {
	for (int i = 0; i < d; i++) {
		if ((mask & 1 << i) == 0) continue; // continue if i != f(mask)

		if (!basis[i]) { // If there is no basis vector with the i'th bit set, then insert this vector into the basis
			basis[i] = mask;
			++sz;
			
			return;
		}

		mask ^= basis[i]; // Otherwise subtract the basis vector from this vector
	}
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc = 1;
    //cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        int a[n + 1];
        int xorsum = 0;
        for(int i = 1; i <= n; i++) cin >> a[i], insertVector(a[i]), xorsum ^= a[i];
        int maxans = 0;
        int cnt1 = 0;
        int flag = 0;
        for(int i = 50; i >= 0; i--) {
            if(getbit(cnt1, i) == 1) continue;
            cnt1 ^= basis[i];
            if(cnt1 == 0) continue;
            maxans = max(maxans, cnt1 + (xorsum ^ cnt1));
        }
        int cnt = 0;
        for(int i = 0; i < d; i++) {
            cnt ^= basis[i];
        }
        maxans = max(maxans, cnt + (xorsum ^ cnt));
        for(int i = 0; i < d; i++) {
            if(basis[i] == 0) continue;
            maxans = max(maxans, (basis[i]) + (xorsum ^ basis[i]));
        }
        for(int i = 0; i < d; i++) {
            for(int j = i + 1; j < d; j++) {
                if((basis[i] ^ basis[j]) == 0) continue;
                maxans = max(maxans, (basis[i] ^ basis[j]) + (xorsum ^ basis[i] ^ basis[j]));
            }
        }
        for(int i = 0; i < d; i++) {
            for(int j = i + 1; j < d; j++) {
                for(int k = j + 1; k < d; k++) {
                    if((basis[i] ^ basis[j] ^ basis[k]) == 0) continue;
                    maxans = max(maxans, (basis[i] ^ basis[j] ^ basis[k]) + (xorsum ^ basis[i] ^ basis[j] ^ basis[k]));
                }
            }
        }
        cout << maxans << "\n";
    }
}