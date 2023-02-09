#include <bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
using namespace std;
const int N = 5e5 + 10;
const int M = 5e5 + 10;
const int MAX = 200005;
ll mods[2] = { 1072857881, 1066517951 };
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
};






map <pair<pii, pii>, int > hashes[M];
map <pii, int > mp;
int32_t main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int x1 = uniform_int_distribution<int>(0, 30)(rng);
    int x2 = uniform_int_distribution<int>(0, 30) (rng);
    bases[0] = 31 + x1;
    bases[1] = 31 + x2;
    int n, m;
    cin >> n >> m;
    ll ans = 0;
    Preprocess();
    for (int ii = 0; ii < n; ++ii) {
        vector<int> pref(m + 1, 0), pref1(m + 1, 0), pref2(m + 1, 0);
        vector<int> suff(m + 2, 0), suff1(m + 2, 0), suff2(m + 2, 0);
        string s;
        cin >> s;
        Hashing h1(s);
        reverse(s.begin(), s.end());
        Hashing h2(s);

        int idx = 0;
        for (int j = 0; j + 2 < m; ++j) {
            ans += hashes[idx][{h1.GetHash(0, j), h2.GetHash(0, m - 3 - j)}];
            ans -= mp[h1.GetHash(0, m - 1)];
            ++idx;
        }

        // cout << h2.GetHash(0, 0).first << " rrr " << h2.GetHash(0, 0).second << endl;
       // cout << h1.GetHash(0, 0).first << " rrr " << h1.GetHash(0, 0).second << endl;

        ans += hashes[idx][{ {-1, -1}, h2.GetHash(0, m - 2) }];
        ans -= mp[h1.GetHash(0, m - 1)];
        if (m > 1) {
            ans += hashes[idx + 1][{ {-1, -1}, h1.GetHash(0, m - 2)}];
            ans -= mp[h1.GetHash(0, m - 1)];
        }
        idx = 0;
        for (int i = 0; i + 2 < m; ++i) {
            hashes[idx][{h1.GetHash(0, i), h2.GetHash(0, m - 3 - i)}]++;
            ++idx;
        }
        //  cout << pref[m] <<  endl;
        // cout << suff[1] <<  " " << pref[m - 1] << " " << idx << " "<< hashes[idx + 1][{-1, pref[m - 1]}] << endl;
        hashes[idx][{ {-1, -1}, h2.GetHash(0, m - 2)}]++;
        hashes[idx + 1][{ {-1, -1}, h1.GetHash(0, m - 2)}]++;
        mp[h1.GetHash(0, m - 1)]++;
        // cout << ans << endl;
    }
    cout << ans << "\n";
}
