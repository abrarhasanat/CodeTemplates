vector<int> side(n, -1);
bool is_bipartite = true;
queue<int> q;
for (int node =  1 ; node <= n ; ++node ) {
    if (side[node] == -1) {
        q.push(node);
        side[node] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : g[v]) {
                if (side[u] == -1) {
                    side[u] = side[v] ^ 1;
                    q.push(u);
                } else {
                    is_bipartite &= side[u] != side[v];
                }
            }
        }
    }
}