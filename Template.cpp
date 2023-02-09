#include <bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
using namespace std;
const int MAX = 2e6 + 10;
const int N = 2e6 + 10;
vector<string>arr;
ll mods[2] = { 1072857881,  1066517951 };
//Some back-up primes: 1072857881, 1066517951, 1040160883
ll bases[2] = { 31, 37 };
ll pwbase[3][MAX];

void Preprocess() {
    pwbase[0][0] = pwbase[1][0] = 1;
    for (ll i = 0; i < 2; i++) {
        for (ll j = 1; j < MAX; j++) {
            pwbase[i][j] = (pwbase[i][j - 1] * bases[i]) % mods[i];
        }
    }
}

ll fmod(ll a, ll b, int md = mods[0]) {
    unsigned long long x = (long long)a * b;
    unsigned xh = (unsigned)(x >> 32), xl = (unsigned)x, d, m;
    asm(
        "divl %4; \n\t"
        : "=a" (d), "=d" (m)
        : "d" (xh), "a" (xl), "r" (md)
    );
    return m;
}


struct Hashing {
    vector<vector<ll>> hsh;
    Hashing() {}
    Hashing(string& _str) {
        hsh.push_back(vector<ll>(_str.size() + 5, 0));
        hsh.push_back(vector<ll>(_str.size() + 5, 0));
        Build(_str);
    }

    void Build(const string& str) { Build1(str);Build2(str); }
    void Build1(const string& str) {
        int j = 0;
        for (ll i = str.size() - 1; i >= 0; i--) {
            hsh[j][i] = fmod(hsh[j][i + 1], bases[j], mods[j]) + str[i];
            if (hsh[j][i] > mods[j])
                hsh[j][i] -= mods[j];
        }
    }
    void Build2(const string& str) {
        int j = 1;
        for (ll i = str.size() - 1; i >= 0; i--) {
            hsh[j][i] = fmod(hsh[j][i + 1], bases[j], mods[j]) + str[i];
            if (hsh[j][i] > mods[j])
                hsh[j][i] -= mods[j];
        }
    }

    pair<ll, ll> GetHash(ll i, ll j) {
        assert(i <= j);
        ll tmp1 = (hsh[0][i] - fmod(hsh[0][j + 1], pwbase[0][j - i + 1]));
        ll tmp2 = (hsh[1][i] - fmod(hsh[1][j + 1], pwbase[1][j - i + 1], mods[1]));
        if (tmp1 < 0) tmp1 += mods[0];
        if (tmp2 < 0) tmp2 += mods[1];
        return make_pair(tmp1, tmp2);
    }

    ll getSingleHash(ll i, ll j) {
        assert(i <= j);
        ll tmp1 = (hsh[0][i] - fmod(hsh[0][j + 1], pwbase[0][j - i + 1]));
        if (tmp1 < 0) tmp1 += mods[0];
        return tmp1;
    }

    int  GetReverseHash(ll i, ll j, ll len) {
        //  assert(i <= j);
        int ii = len - j - 1;
        int jj = len - i - 1;
        return getSingleHash(ii, jj);
    }
};
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, int> mp[N], rev[N];

// map<int, int > mp[N];
// map<int, int > rev[N];
vector<Hashing>g, gr;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Preprocess();
    int n; cin >> n;
    for (int i = 0;i < n; ++i) {
        int x;  cin >> x;
        string s;  cin >> s;
        arr.push_back(s);
        Hashing h1(s);
        mp[x][h1.getSingleHash(0, x - 1)]++;
        Hashing h2(s);
        // rev[x][h2.GetHash(0, x - 1)]++;
        g.push_back(h1);
        gr.push_back(h2);
        // cout << x << " " << h1.GetHash(0, x - 1).first << endl;
    }
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        int len = arr[i].size();
        int hval = g[i].getSingleHash(0, len - 1);
        ans += mp[len][hval];
        // cout << ans << endl;
        for (int j = 0; j < arr[i].size(); ++j) {
            int crLen = j + 1;
            int crHash = gr[i].GetReverseHash(0, j, len);
            if (j + 1 <= len - 1) {
                if (g[i].getSingleHash(j + 1, len - 1) == gr[i].GetReverseHash(j + 1, len - 1, len)) {
                    ans += mp[crLen][crHash];
                }
            }
        }
        // cout << ans << endl;
        for (int j = arr[i].size() - 1; j >= 0; --j) {
            int crLen = arr[i].size() - j;
            int crHash = gr[i].GetReverseHash(j, arr[i].size() - 1, arr[i].size());
            if (0 <= j - 1) {
                if (g[i].getSingleHash(0, j - 1) == gr[i].GetReverseHash(0, j - 1, arr[i].size())) {
                    ans += mp[crLen][crHash];
                }
            }
        }
        // cout << ans << endl;
    }
    cout << ans << "\n";
}






10110110






