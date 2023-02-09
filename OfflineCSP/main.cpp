#include<bits/stdc++.h>
#define int long long 
#define pii pair<int,int>
using namespace std;
const int  N = 1e5 + 10;
vector<pair<int, int>>courses;
vector<vector<int>>courseInfo;
vector<int>g[N]; //adj list  

int parseInteger(string s) {
    //from geeksforgeeks
    stringstream geek(s);
    int x = 0;
    geek >> x;
    return x;
}
vector<int> getListOfCourse(string s) {
    istringstream ss(s);
    string word;
    vector<int>res;
    while (ss >> word) {
        res.push_back(parseInteger(word));
    }
    return res;
}
void loadInfo(string courseFileName, string studentFileName) {
    ifstream courseFile(courseFileName);
    ifstream studentFile(studentFileName);
    string info;
    if (courseFile.is_open()) {
        while (!courseFile.eof()) {
            getline(courseFile, info);
            if (info.empty()) break;
            vector<int>res = getListOfCourse(info);
            if (res.size() < 2) break;
            courses.emplace_back(res[0], res[1]);
            info.clear();
        }
    }


    if (studentFile.is_open()) {
        while (!studentFile.eof()) {
            getline(studentFile, info);
            if (info.empty()) break;
            vector<int>res = getListOfCourse(info);
            if (res.empty()) break;
            courseInfo.push_back(res);
        }
    }
}

void buildGraph() {
    for (auto i : courseInfo) {
        for (int j = 0; j < i.size(); ++j) {
            for (int k = j + 1; k < i.size(); ++k) {
                g[i[j]].push_back(i[k]);
                g[i[k]].push_back(i[j]);
            }
        }
    }

}



void clear(int n) {
    for (int i = 0; i <= n; ++i) {
        g[i].clear();
    }
    courseInfo.clear();
    courses.clear();
}



inline bool cmp(const int& a, const int& b) {
    return g[a].size() > g[b].size();
}




vector<int> solveWithLargestDegree() {
    vector<int>crs;
    for (auto i : courses) crs.push_back(i.first);
    sort(crs.begin(), crs.end(), cmp);
    int n = courses.size();
    vector<int>color(n + 1, -1);
    int cnt = 0;
    for (auto u : crs) {
        if (color[u] != -1) continue;
        set<int>adjColors;
        for (auto v : g[u]) {
            if (color[v] == -1) continue;
            adjColors.insert(color[v]);
        }
        int mex = 0;
        for (auto i : adjColors) {
            if (i == mex) ++mex;
            else break;
        }
        color[u] = mex;
        // if (cnt < 400) {
        //     for (auto x : adjColors) cout << x << " ";
        //     cout << endl;
        //     cout << g[u].size() << endl;
        //     cout << "mex : " << mex << endl;
        //     //++cnt;
        // }
    }
    return color;

}


struct node {
    int v, sat, deg;
    node(int _v, int _sat, int _deg) : v(_v), sat(_sat), deg(_deg) {}
    bool operator < (const node& o) const {
        if (sat == o.sat) return deg < o.deg;
        return sat < o.sat;
    }
};


vector<int> solveWithSaturationDegree() {
    int n = courses.size();
    vector<set<int>> adjcols(n + 1);
    priority_queue<node>mst;
    vector<node>src;
    int deg[n + 1];  // to break the tie using maximum degree to uncolored vertex ;
    vector<int>col(n + 1, -1);
    for (int i = 1; i <= n; ++i) {
        deg[i] = g[i].size();
        col[i] = -1;
        src.push_back({ i, 0 , deg[i] });
        //mst.insert({ i, 0, deg[i] });
    }
    sort(src.begin(), src.end());
    vector<int>vis(n + 1, 0);
    for (int i = 1;i <= n; ++i) {
        if (vis[i]) continue;
        mst.push(node(i, adjcols[i].size(), deg[i]));
        while (!mst.empty()) {
            node v = mst.top();
            mst.pop();
            if (col[v.v] != -1) continue;
            int mex = 0;
            set<int>cols;
            for (auto i : g[v.v]) {
                if (col[i] == -1) continue;
                cols.insert(col[i]);
            }
            for (auto i : cols) {
                if (i == mex) ++mex;
                else break;
            }
            col[v.v] = mex;
            ++vis[v.v];
            for (auto j : g[v.v]) {
                if (col[j] != -1) continue;
                adjcols[j].insert(mex);
                --deg[j];
                mst.push(node(j, adjcols[j].size(), deg[j]));
            }
        }
    }

    return col;
}



inline bool cmpx(const pii& x, const pii& y) {
    return x.first > y.first;
}
vector<int> solveWithLargestEnrolment() {
    vector<pair<int, int>>crs;
    for (auto i : courses) crs.emplace_back(i.second, i.first);
    sort(crs.begin(), crs.end(), cmpx);
    int n = courses.size();
    vector<int>color(n + 1, -1);
    for (auto uu : crs) {
        int u = uu.second;
        set<int>adjColors;
        for (auto v : g[u]) {
            if (color[v] == -1) continue;
            adjColors.insert(color[v]);
        }
        int mex = 0;
        for (auto i : adjColors) {
            if (i == mex) ++mex;
            else break;
        }
        color[u] = mex;
    }
    return color;
}




vector<int> solveWithRandomOrdering() {
    vector<int>crs;
    for (auto i : courses) crs.push_back(i.first);
    int n = crs.size();
    srand(1033756);
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(crs[i], crs[j]);
    }
    vector<int>color(n + 1, -1);
    for (auto u : crs) {
        set<int>adjColors;
        for (auto v : g[u]) {
            if (color[v] == -1) continue;
            adjColors.insert(color[v]);
        }
        int mex = 0;
        for (auto i : adjColors) {
            if (i == mex) ++mex;
            else break;
        }
        color[u] = mex;
    }
    return color;
}




double  calculatePenalty(vector<int>color, int isLinear) {
    int n = courseInfo.size();
    int totSum = 0;
    for (int i = 0;i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < courseInfo[i].size(); ++j) {
            for (int k = j + 1; k < courseInfo[i].size(); ++k) {
                int n = llabs(color[courseInfo[i][j]] - color[courseInfo[i][k]]);
                if (n <= 5) {
                    if (isLinear)
                        sum += ((5 - n) << 1);
                    else
                        sum += (1LL << (5 - n));
                }
            }
        }
        totSum += sum;
    }
    int m = courseInfo.size();

    double  res = (double)(totSum) / (double)(n);
    return res;
}







vector<int>v1, v2, vis, ncolor;
void dfs(int u, int from, int c1, int c2, int cs) {
    // cout << u << " " << ncolor[u] << " " << c1 << " " << c2 << " " << cs << endl;
    if (cs == 0) v1.push_back(u);
    else v2.push_back(u);
    ++vis[u];
    for (auto j : g[u]) {
        if (vis[j]) continue;
        if (cs == 0) {
            if (ncolor[j] == c2) dfs(j, u, c1, c2, 1);
        }
        else {
            if (ncolor[j] == c1) dfs(j, u, c1, c2, 0);
        }
    }
}




void applyKempeChain(vector<int>& color, int isLinear) {
    int  n = courses.size();
    int  root = rand() % (n + 1);
    int  sz = g[root].size();
    if (sz == 0) return;
    int  child = rand() % sz;
    child = g[root][child];
    assert(root <= courses.size());
    assert(child <= courses.size());
    v1.clear();
    v2.clear();
    vis.assign(n + 1, 0);
    ncolor = color;

    assert(color[root] <= courses.size());
    assert(color[child] <= courses.size());
    dfs(root, -1, color[root], color[child], 0);


    double currentPenalty = calculatePenalty(color, isLinear);
    for (auto i : v1) ncolor[i] = color[child];
    for (auto i : v2) ncolor[i] = color[root];

    bool pass = true;
    for (int i = 1;i <= courses.size(); ++i) {
        for (auto j : g[i]) if (color[i] == color[j]) pass = false;
    }
    if (!pass) return;

    double  newPenalty = calculatePenalty(ncolor, isLinear);
    if (newPenalty < currentPenalty)
        color = ncolor;
    //cout << newPenalty << " " << currentPenalty << endl;
}

void kempeChainUtill(vector<int>& color, int isLinear) {
    int maxIter = 100;
    srand(1023);
    for (int i = 0; i < maxIter; ++i) {
        applyKempeChain(color, isLinear);
        // cout << i << endl;
    }
}






void applyRandomPairSwap(vector<int>& color, int isLinear) {
    int maxIter = 1000;
    srand(541114);
    int maxCnt = 0;
    int n = courses.size();
    for (int i = 0; i < maxIter && maxCnt < 1000; ++i) {
        int u = rand() % (n + 1);
        int v = rand() % (n + 1);
        bool pass = true;
        for (auto i : g[u]) {
            if (color[i] == color[v]) pass = false;
        }
        for (auto i : g[v]) {
            if (color[i] == color[u]) pass = false;
        }
        if (pass) {
            int currentPenalty = calculatePenalty(color, isLinear);
            vector<int>ncolor = color;
            swap(ncolor[u], ncolor[v]);
            int newPenalty = calculatePenalty(ncolor, isLinear);
            if (newPenalty < currentPenalty) {
                ++maxCnt;
                swap(color[u], color[v]);
            }
        }
    }
}



int32_t main() {
    int isLinear = 1;
    string crs_name, stu_name;
    cin >> crs_name >> stu_name;
    loadInfo(crs_name, stu_name);
    buildGraph();
    vector<int>color1 = solveWithRandomOrdering();
    cout << calculatePenalty(color1, isLinear) << endl;
    set<int>uniqueCols;
    for (int i = 1; i <= courses.size(); ++i) uniqueCols.insert(color1[i]);
    cout << "uniqueColors " << uniqueCols.size() << endl;
    kempeChainUtill(color1, isLinear);
    cout << calculatePenalty(color1, isLinear) << endl;
    applyRandomPairSwap(color1, isLinear);
    cout << calculatePenalty(color1, isLinear) << endl;
    clear(courses.size());


}


//  car-f-92.crs car-f-92.stu
//  car-s-91.crs car-s-91.stu
//  kfu-s-93.crs kfu-s-93.stu
//  tre-s-92.crs tre-s-92.stu
//  yor-f-83.crs yor-f-83.stu


// kfu-s-93.crs kfu-s-93.stu