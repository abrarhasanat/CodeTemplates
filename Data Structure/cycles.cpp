int n;
int cycle_start, cycle_end;
vector < int  >g[N];
int col[N], par[N], vis[N];
bool dfs(int u) { //  directed graph 
    col[u] = 1;
    for (int i : g[u]) {
        if (color[i] == 0) {
            parent[i] = u;
            if (dfs(i))
                return true;
        }
        else if (color[i] == 1) {
            cycle_end = u;
            cycle_start = i;
            return true;
        }
    }
    col[u] = 2;
    return false;
}

bool dfs(int u, int p) {
    ++vis[u];
    for (int i : g[u]) {
        if (i == p) continue;
        if (vis[i]) {
            cycle_end = u;
            cycle_start = i;
            return true;
        }
        parent[i] = u;
        if (dfs(i, parent[i]))
            return true;
    }
    return false;
}
void find_cycle() {
    memset(col, 0, sizeof(col));
    memset(par, -1, sizeof(par));
    cycle_start = -1;

    for (int v = 0; v < n; v++) {
        if (col[v] == 0 && dfs(v))
            break;
    }

    if (cycle_start == -1) {
        cout << "Acyclic" << endl;
    }
    else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v])
            cycle.push_back(v);
        cycle.push_back(cycle_start);
        reverse(cycle.begin(), cycle.end());

        cout << "Cycle found: ";
        for (int v : cycle)
            cout << v << " ";
        cout << endl;
    }
}