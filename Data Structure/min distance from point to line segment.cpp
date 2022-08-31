#include <bits/stdc++.h>
#define  ll  long long
#define  pii pair<ll,ll>
#define  pll pair<ll , ll>
#define  debug cout << "this far" << endl;
#define  For(i, n) for(int i = 0; i < (n); ++i)
#define  lsb(x) ((x) & (-x))
#define  PI acos(-1)
#define  line cout << endl;
#define  getbit(n, i) (((n) & (1LL << (i))) != 0)
#define  resetbit(n, i) ((n) & (~(1LL << (i))))
#define  setbit(n, i) ((n) | (1LL << (i)))
#define  togglebit(n, i) ((n) ^ (1LL << (i)))
#define  gap " "
#define printall(container) for(auto val  : container) cout << val << gap ; line ; 
using namespace std;
const int N = 2e5 + 10;
// min distance from a point to a line segment ;
pii getvector(pii a, pii b) {
    // vector from point  a to point b 
    return make_pair(b.first - a.first, b.second - a.second);
}
long double dotproduct(pii a, pii b) {
    return a.first * b.first + a.second * b.second;
}
long double mindistance(pii  p, pii p1, pii p2) {
    // distance from p to line segment p1 -> p2 ;
    pii a = getvector(p1, p);
    pii b = getvector(p1, p2);
    double r = dotproduct(a, b) / dotproduct(b, b);
    if (r > 1)
        return dotproduct(getvector(p, p2), getvector(p, p2));
    if (r < 0) return dotproduct(getvector(p, p1), getvector(p, p1));
    else {
        double x = r;
        x *= sqrt(dotproduct(b, b));
        double y = dotproduct(a, a);
        return y - x * x;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}