ll  ncr(ll   n, ll  r) {
    ll  nom = 1;
    ll  denom = 1;
    for (ll i = 1; i <= r; ++i) {
        nom *= (n - i + 1);
        denom *= i;
        ll  gcd = __gcd(nom, denom);
        nom /= gcd;
        denom /= gcd;
    }
    return nom / denom;
}