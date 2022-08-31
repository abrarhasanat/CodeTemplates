ll get2root(ll x) {
    ll root = (long double)(sqrt((long double)x + 0.5) + 0.5);
    while (root * root < x)  root++;
    while (root * root > x) root--;
    if (root * root == x) return root;
    return -1;
}
ll get3root(ll x) {
    ll root = (long double)(pow((long double)x + 0.5, 1.00 / 3.00) + 0.5);
    while (root * root * root < x) ++root;
    while (root * root * root > x) --root;
    if (root * root * root == x) return root;
    return -1;
}