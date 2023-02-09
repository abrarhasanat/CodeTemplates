#include<bits/stdc++.h>
#define pii pair<int,int>
#define int long long
#define ll long long 
#define ld long double 
using namespace std;
const int N = 5e5 + 10;
const int mod = 998244353;
const long double EPS = 1e-9;
const long double eps = 1e-9;
inline bool gt(const long double x, const long double y) {
    return x > y + eps;
}
inline bool lt(const long double x, const long double y) {
    return y > x + eps;
}
struct pt {
    long long x, y;
    pt() {}
    pt(long long _x, long long _y) : x(_x), y(_y) {}
    pt operator-(const pt& p) const { return pt(x - p.x, y - p.y); }
    long long cross(const pt& p) const { return x * p.y - y * p.x; }
    long long cross(const pt& a, const pt& b) const { return (a - *this).cross(b - *this); }
};

int sgn(const long long& x) { return x >= 0 ? x ? 1 : 0 : -1; }

bool inter1(long long a, long long b, long long c, long long d) {
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);
    return max(a, c) <= min(b, d);
}
// checks if two lines intersect or not
bool check_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
    if (c.cross(a, d) == 0 && c.cross(b, d) == 0)
        return inter1(a.x, b.x, c.x, d.x) && inter1(a.y, b.y, c.y, d.y);
    return sgn(a.cross(b, c)) != sgn(a.cross(b, d)) &&
        sgn(c.cross(d, a)) != sgn(c.cross(d, b));
}
int L, W;

// returns the intersection point of two lines ax + by +c = 0 
pair<pii, pii> getInterSectingPoint(int a1, int b1, int c1, int a2, int b2, int c2) {
    pii x, y;
    // intersecting point ;
    // x = p / q ; y = p / q stored as (p , q);
    x.first = -(c1 * b2 - c2 * b1);
    x.second = a1 * b2 - a2 * b1;
    int g = __gcd(x.first, x.second);
    x.first /= g;
    x.second /= g;

    y.first = -(a1 * c2 - a2 * c1);
    y.second = a1 * b2 - a2 * b1;
    g = __gcd(y.first, y.second);
    y.first /= g;
    y.second /= g;

    // y == 0 kina check
    if (y.first == 0) y.first = -1;
    // y == W kina check { 
    if (y.first % y.second == 0 and (y.first / y.second) == W) y.first = -1;
    // x == 0 kine check 
    if (x.first == 0) x.first = -1;
    if (x.first % x.second == 0 and (x.first / x.second) == L) x.first = -1;

    // cout << (double)(x.first) / (double)(x.second) << " " << (double)(y.first) / (double)(y.second) << endl;
    return { x,y };
}
// gives the eqn of a line connecting two point p , q 
pair<pii, int > getEqnFromPoint(pt p, pt  q) {
    int a = p.y - q.y;
    int b = q.x - p.x;
    int c = -a * p.x - b * p.y;
    return { {a,b}, c };
}

ld res_x1, res_y1, res_x2, res_y2;
int circleLineIntersect(ld r, ld a, ld b, ld c) {
    // set the result to global variable res_x1 ,res_x2 .... 
    // returns number of intersecting point
    // the equation is x2 + y2 = r2 and ax + by + c = 0 ;
    double x0 = -a * c / (a * a + b * b), y0 = -b * c / (a * a + b * b);
    if (c * c > r * r * (a * a + b * b) + EPS)
        return  0;
    else if (abs(c * c - r * r * (a * a + b * b)) < EPS) {
        // puts("1 point");
        res_x1 = x0;
        res_y1 = y0;
        return 1;
    }
    else {
        double d = r * r - c * c / (a * a + b * b);
        double mult = sqrt(d / (a * a + b * b));
        double ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;
        res_x1 = ax;
        res_y1 = ay;
        res_x2 = bx;
        res_y2 = by;
        return 2;
    }

}
int circleCircleIntersect(ld x1, ld y1, ld r1, ld x2, ld y2, ld r2) {
    // results is set int res_x1 , res_x2 
    // x1 , y1 is acting as origin... remember this 
    x2 -= x1;
    y2 -= y1;
    ld A = -2 * x2;
    ld B = -2 * y2;
    ld C = x2 * x2 + y2 * y2 + r1 * r1 - r2 * r2;
    int res = circleLineIntersect(r1, A, B, C);
    res_x1 += x1;
    res_y1 += y1;
    res_x2 += x1;
    res_y2 += y1;
    return res;
}
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc = 1;
    cin >> tc;
    for (int tcase = 1; tcase <= tc; ++tcase) {
        vector<pair<pt, pt>>pts;
        int n; cin >> n >> L >> W;
        pts.resize(n + 5);
        for (int i = 1; i <= n; ++i) {
            cin >> pts[i].first.x >> pts[i].first.y >> pts[i].second.x >> pts[i].second.y;
        }
        int res = 1;
        for (int i = 1; i <= n; ++i) {
            int cnt = 0;
            set<pair<pii, pii>>st;
            for (int j = 1; j < i; ++j) {
                if (check_inter(pts[i].first, pts[i].second, pts[j].first, pts[j].second)) {
                    pair<pii, int> x = getEqnFromPoint(pts[i].first, pts[i].second);
                    pair<pii, int >y = getEqnFromPoint(pts[j].first, pts[j].second);
                    pair<pii, pii> res = getInterSectingPoint(x.first.first, x.first.second, x.second, y.first.first, y.first.second, y.second);
                    if (res.first.first != -1 and res.second.first != -1) st.insert(res);
                }
            }
            //cout << i << "  " << cnt << "  " << res + cnt + 1 << endl;
           // cout << st.size() << endl;
            res = res + (int)st.size() + 1;
        }
        cout << "Case " << tcase << ": ";
        cout << res << "\n";
    }

}

