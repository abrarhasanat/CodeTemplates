#include<bits/stdc++.h>
using namespace std;
class disjointSet {
private:
    int v;
    int* par;
    int* sz;
public:
    disjointSet(int _v) {
        v = _v;
        par = new int[v + 1];
        sz = new int[v + 1];
        for (int i = 0; i < v; ++i) {
            par[i] = i;
            sz[i] = 1;
        }
    }
    int find(int  u) {
        if (u == par[u]) return u;
        return par[u] = find(par[u]);
    }

    bool Union(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)  return false;
        if (sz[x] < sz[y]) swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
        return true;
    }

};