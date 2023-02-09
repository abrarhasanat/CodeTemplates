mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//f you want 64-bit random numbers, just use mt19937_64 instead
uniform_int_distribution<int>(l, r)(rng);