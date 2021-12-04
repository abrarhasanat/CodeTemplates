ll D[N];
void CalculateDerangment() {
    D[0] = 1;
    ll ss = -1;
    for (int i = 1; i < N; ++i) {
        D[i] = (i * D[i - 1]) % mod;
        D[i] = (D[i] + ss + mod) % mod;
        ss *= -1;
    }

}