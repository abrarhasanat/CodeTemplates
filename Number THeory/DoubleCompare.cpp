const long double eps = 1e-9;
inline bool gt(const long double x, const long double y) {
    return x > y + eps;
}
inline bool lt(const long double x, const long double y) {
    return y > x + eps;
}
cout.precision(24); 
    cout << fixed << r << endl;