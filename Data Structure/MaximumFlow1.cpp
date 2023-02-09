int capacity[N][N];
vector<int>g[N];
vector<int>parent(N);
int bfs(int s, int t) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({ s, INF });

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : g[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({ next, new_flow });
            }
        }
    }
    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    int new_flow;
    while (new_flow = bfs(s, t)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}
void addEdge(int u, int v, int cap) {
    g[u].push_back(v);
    g[v].push_back(u);
    capacity[u][v] = cap;
    capacity[v][u] = 0;
}
void clear() {
    for (int i = 0; i < N; ++i) {
        g[i].clear();
        for (int j = 0; j < N; ++j) capacity[i][j] = 0;
    }
}