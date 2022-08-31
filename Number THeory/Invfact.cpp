ll fact[N], invfact[N];
ll bigmod(ll a, ll p) {
    if (p == 0) return 1;
    ll x = bigmod(a, p / 2);
    x = (x * x) % mod;
    if (p % 2) x = (x * a) % mod;
    return  x;
}
void PrecalculatingInverseFactorial() {
    fact[0] = 1;
    for (ll i = 1; i < N; ++i) fact[i] = (i * fact[i - 1]) % mod;
    invfact[N - 1] = bigmod(fact[N - 1], mod - 2);
    for (ll i = N - 2; i >= 0; --i) {
        invfact[i] = (invfact[i + 1] * (i + 1)) % mod;
    }
}