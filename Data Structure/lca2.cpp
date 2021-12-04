#include <bits/stdc++.h>
#define  mx 100005
#define  ll long long
#define  pii pair<int,int>
#define  debug printf("%d\n", bug++);
#define  For(i,n) for(int i = 0; i < n; ++i)
#define  INF 1 << 29
using namespace std;
struct  edge{
    int u , v, c;
    bool operator < (const edge &o ) const {
        return  c < o.c;
    }
};
vector<edge>g(mx);
int bug = 1;
int parent[mx],size[mx];
vector<pii>adj[mx];
int find(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find(parent[v]);
}
void Union(int a,int b) {
    if (size[a] < size[b])
        swap(a, b);
    parent[b] = a;
    size[a] += size[b];
}
void MST(int  n , int m){
    for(int i = 0;i <= m; ++i)
        parent[i] = i, size[i] = 1;
    sort(g.begin(), g.end());
    For(i,n){
        int a ,b, c;
        a = find(g[i].u);
        b  = find(g[i].v);
        if(a != b)
        {
            Union(a,b);
            adj[g[i].u].push_back({g[i].v, g[i].c});
            adj[g[i].v].push_back({g[i].u, g[i]. c});
        }
    }
}
int P[mx][30], L[mx], E[mx][30],vis[mx];
void dfs(int from , int u ,int cst,int lvl)
{
    E[u][0] = cst;
    P[u][0] = from;
    L[u] = lvl;
    vis[u] = 1;
    for(auto i : adj[u]){
        int a = i.first;
        int b = i.second;

        if(vis[a]) continue;
        dfs(u,a,b,lvl + 1);

    }
}
void preprocess(int n){
    for(int i = 0 ; i < n; ++i) {
        for(int j = 0; (1 << j) < n ;++j){
            P[i][j] = -1;
            E[i][j] = -1;
        }
    }

    dfs(-1,0,0,0);
    for(int j = 1 ; (1 << j) < n; ++j){
            For(i,n){
                if(P[i][j-1] != -1){
                P[i][j] = P[P[i][j-1]][j-1];
                E[i][j] = max(E[i][j-1] ,  E[P[i][j-1]][j-1]);
            }
        }
    }
}
int lca(int a, int b){
    if(L[a] < L[b]){
        swap (a,b);
    }
    int ans = 0;
    int lg,i;
    for(lg =1;(1 << lg) <= L[a]; ++lg);
    --lg;
    for(i = lg ; i >= 0; --i) {
        if (L[a] - (1 << i) >= L[b]) {
            ans = max(ans, E[a][i]);
            a = P[a][i];
        }
    }

    if(a == b)
        return ans;
    for(i = lg; i >= 0; --i) {
        if (P[a][i] != -1 && P[a][i] != P[b][i]) {
            ans = max(ans, E[a][i]);
            ans = max(ans, E[b][i]);
            a = P[a][i];
            b = P[b][i];
        }
    }
    ans = max(ans , E[a][0]);
    ans = max(ans, E[b][0]);
    return  ans;
}
void Reset(int n){

    g.clear();
    For(i ,n+1){
        adj[i].clear();
        parent[i] = -1;
        size[i]  = -1;
        L[i]  = -1;
        vis[i] = 0;
    }
}
int main(){
    int t;
    scanf("%d", &t);
    For(tc,t){
        int n,m;
        scanf("%d %d", &n, &m);
        Reset(n + 1);
        For(i ,m){
            int a, b,c;
            scanf("%d %d %d", &a, &b, &c);
            --a;
            --b;
            g.push_back({a,b,c});
        }
        MST(m , n);
        preprocess(n);
        int q;
        scanf("%d", &q);
        printf("Case %d:\n", tc + 1);
        while (q--){
            int a, b;
            scanf("%d %d", &a, &b);
            --a;
            --b;
            printf("%d\n", lca(a,b));
        }

    }
}


