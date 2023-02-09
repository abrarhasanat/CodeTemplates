#include <bits/stdc++.h>
#define  mx 5005
#define  pii pair<int,int>
#define  inf 1 << 30
using namespace std;
struct edge
{
    int to , weight;
    edge(int t ,int w) : to(t), weight(w) {}

};
struct  node
{
    int state, v,cost;
    node(int x, int y, int z) : state(x) ,  v(y) , cost(z) {}
    bool operator < (const node &o) const
    {
        if(state == o.state)
            if(cost == o.cost)
                return v > o.v;
        return  cost > o.cost;
        return state > o.state;
    }
};
vector<edge>g[mx];
int d[2][mx];
int djks(int n)
{
    for(int i = 1 ;i <= n; ++i)
    {
        d[0][i] = d[1][i] = INT_MAX;
    }
    priority_queue<node>q;
    d[0][1] = 0;
    q.push(node(0,1,0));
    while (!q.empty())
    {
        int st = q.top().state;
        int vr  = q.top().v;
        int cst = q.top().cost;
        q.pop();
        if(vr == n && st == 1)
            return  d[1][n];
        if(cst > d[st][vr]) continue;
        for(int i = 0; i < int(g[vr].size()) ;++i)
        {
            int v1 = g[vr][i].to;
            int w1 = g[vr][i].weight;
            if(cst + w1 < d[0][v1])
            {
                d[1][v1] = d[0][v1];
                d[0][v1] = cst + w1;
                q.push(node(0 ,v1, d[0][v1]));
                q.push(node(1,v1, d[1][v1]));
            }
            else if(w1 + cst > d[0][v1]   && w1 + cst < d[1][v1])
            {
                d[1][v1] = w1 + cst;
                q.push(node(1, v1,d[1][v1]));
            }
        }
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    for(int tc = 1; tc <= t ;++tc)
    {
        int n,r;
        scanf("%d %d", &n, &r);
        for(int i = 1;i <= r ;++i)
        {
            int a,b,c;
            scanf("%d %d %d",&a, &b, &c );
            g[a].push_back(edge(b,c));
            g[b].push_back(edge(a,c));
        }
        printf("Case %d: %d\n", tc, djks(n));
        for(int i = 0 ; i <=n ;++i)
            g[i].clear();

    }
}