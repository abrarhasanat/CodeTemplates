#include <bits/stdc++.h>
#define  pii pair<int,int>
#define mx 10010

using namespace std;
vector<pii>edge[N];
int L[N], P[N][30], T[N];
int vis[N];
long dist[N];
void dfs(int from, int u, int dep) {
    L[u] = dep;
    T[u] = from;
    vis[u] = 1;
    for (auto i : edge[u]) {
        int a = i.first;
        int dis = i.second;
        if (vis[a]) continue;
        P[a][0] = u;
        dist[a] = dist[u] + dis;
        dfs(u, a, dep + 1);
    }

}
void preprocess(int N) {
    for (int i = 1; i <= N;++i) {
        for (int j = 0; (1 << j) < N;++j)
            P[i][j] = -1;
    }
    dfs(-1, 1, 0);
    for (int j = 1; (1 << j) < N; ++j) {
        for (int i = 1;i <= N; ++i) {
            if (P[i][j - 1] == -1) continue;
            P[i][j] = P[P[i][j - 1]][j - 1];
        }
    }
}
void Reset(int N) {
    for (int i = 0; i <= N; i++) {
        edge[i].clear();
        vis[i] = 0;
        dist[i] = -1;
    }
    dist[0] = 0;
}
int lca(int p, int q) {
    if (L[p] < L[q])  swap(p, q);
    int log = 1;
    for (log = 1; (1 << log) <= L[p]; log++); log--;
    for (int i = log; i >= 0; --i) {
        if (L[p] - (1 << i) >= L[q])
            p = P[p][i];
    }
    if (p == q) return  p;
    for (int i = log; i >= 0; --i) {
        if (P[p][i] != -1 && P[p][i] != P[q][i]) {
            p = P[p][i];
            q = P[q][i];
        }
    }
    return  P[p][0];


}
int distance(int p, int q) {
    int c = lca(p, q);
    return dist[p] + dist[q] - 2 * dist[c];

}
int Findkth(int p, int q, int k) {
    int c = lca(p, q);
    int z;
    if (c == p) {
        swap(p, q);
        z = L[p] - L[q] + 1;
        k = z - k + 1;
    }
    else if (k > L[p] - L[c] + 1) {
        swap(p, q);
        z = L[q] + L[p] - 2 * L[c] + 1;
        k = z - k + 1;
    }
    int lg;
    for (lg = 1; (1 << lg) <= L[p];lg++);
    lg--;
    k--;
    for (int i = lg; i >= 0; --i) {
        if ((1 << i) <= k) {
            p = P[p][i];
            k -= (1 << i);
        }

    }
    return  p;
}
int main()
{
    int t;
    char str[100];
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("\n%d", &n);
        Reset(n);

        for (int i = 0; i < n;++i) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            edge[x].push_back({ y,z });
            edge[y].push_back({ x,z });
        }
        preprocess(n);
        while (scanf("%s", &str)) {
            if (str[1] == 'O')
                break;
            if (str[0] == 'D') {
                int a, b;
                cin >> a >> b;
                printf("%d\n", distance(a, b));

            }
            else {
                int a, b, c;
                cin >> a >> b >> c;
                printf("%d\n", Findkth(a, b, c));
            }
        }
    }



}
