const long double eps = 1e-9;
inline bool gt(const long double x, const long double y) {
    return x > y + eps;
}
inline bool lt(const long double x, const long double y) {
    return y > x + eps;
}
cout.precision(24);
cout << fixed << r << endl;
double acos1(double x) {
    if (x > 1)
        x = 1;
    if (x < -1)
        x = -1;
    return acos(x);
}

long  double sqrt1(long double a) {
    if (a < 0)
        return 0;
    return sqrtl(a);
}