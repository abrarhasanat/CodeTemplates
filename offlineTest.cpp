#include<bits/stdc++.h>
#define pii pair<int,int>
#define VAH1 1
#define VAH2 2
#define VAH3 3
#define VAH4 4
#define VAH5 5
using namespace std;


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//VAH1 
inline bool cmp1(const pair< pii, pii >& a, const pair < pii, pii >& b) {
    return a.first.first < b.first.first;
}


//VAH2
inline bool cmp2(const pair <pii, pii>& a, const pair<pii, pii>& b) {
    return  a.first.second > b.first.second;
}

//VAH3
inline bool cmp3(const pair<pii, pii>& a, const pair<pii, pii>& b) {
    if (a.first.first == b.first.first)
        return a.first.second > b.first.second;
    return a.first.first < b.first.first;
}

//VAH4

inline bool cmp4(const pair<pii, pii>& a, const pair<pii, pii>& b) {
    return (a.first.first * b.first.second) < (b.first.first * a.first.second);
}




class Solver {
public:
    int n;
    vector<vector<int>>mat, originalMat;
    vector < vector<int>> row;
    vector < vector<int>>col;
    int vah;
    int nodeCount;
    int btCount;
    int loadN() {
        int n; cin >> n;
        return n;
    }
    vector< vector<int >> loadSquare(int n) {
        vector<vector<int>>mat(n);
        for (int i = 0;i < n; ++i) {
            mat[i].resize(n);
            for (int j = 0;j < n; ++j) cin >> mat[i][j];
        }
        return mat;
    }

    void init() {
        row.resize(n + 1);
        col.resize(n + 1);
        for (int i = 0; i <= n; ++i) {
            row[i].clear();
            col[i].clear();
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                row[i].push_back(mat[i][j]);
                col[j].push_back(mat[i][j]);
            }
        }
    }
    Solver() {
        n = loadN();
        mat = loadSquare(n);
        originalMat = mat;
        init();

    }
    pii getVar(int choice, int n) {
        vector < pair<pii, pii >> arr;
        for (int i = 0; i < n; ++i) {
            for (int j = 0;j < n; ++j) {
                if (mat[i][j] != 0) continue;
                int degreeCnt = 0;
                for (int k = 0; k < n; ++k) {
                    if (k != j and mat[i][k] == 0) ++degreeCnt;
                    if (k != i and mat[k][j] == 0) ++degreeCnt;
                }
                int domSize = getDomain(i, j).size();
                arr.push_back({ { domSize , degreeCnt }, { i, j } });
            }
        }
        if (arr.empty()) return { -1,-1 };

        if (choice == VAH1) {
            sort(arr.begin(), arr.end(), cmp1);
            return arr.front().second;
        }

        else if (choice == VAH2) {
            sort(arr.begin(), arr.end(), cmp2);
            return arr.back().second;
            //return arr.front().first;
        }

        else if (choice == VAH3) {
            sort(arr.begin(), arr.end(), cmp3);
            return arr.front().second;
        }

        else if (choice == VAH4) {
            sort(arr.begin(), arr.end(), cmp4);
            return arr.front().second;
        }

        else {
            int n = arr.size();
            int idx = uniform_int_distribution<int>(0, n - 1) (rng);
            return arr[idx].second;
        }
        return { -2,-2 };
    }



    void shuffleArray(vector<int>& arr) {
        int n = arr.size();
        for (int i = n - 1; i >= 0; --i) {
            int j = uniform_int_distribution<int>(0, i)(rng);
            swap(arr[i], arr[j]);
        }
    }



    vector<int>getDomain(int x, int y) {
        vector<int>cnt(n + 1, 0);
        for (int i : row[x]) ++cnt[i];
        for (int i : col[y]) ++cnt[i];
        vector<int>arr;
        for (int i = 1;i <= n; ++i) {
            if (!cnt[i]) arr.push_back(i);
        }
        return arr;
    }


    bool forwardCheck(int r, int c, int val) {
        //checing for all the cells on the r-th row
        for (int j = 0; j < n; ++j) {
            if (j == c) continue;
            if (mat[r][j] != 0) continue;
            vector<int>domain = getDomain(r, j);
            if (domain.size() == 1 and domain.back() == val) return false;
        }
        for (int i = 0; i < n; ++i) {
            if (i == r) continue;
            if (mat[i][c] != 0) continue;
            vector<int>domain = getDomain(i, c);
            if (domain.size() == 1 and domain.back() == val) return false;
        }
        return true;
    }



    bool simpleBackTrack(int choice) {
        ++nodeCount;
        pii idx = getVar(choice, n);
        if (idx.first == -2) return false;
        // there is something wrong in our assignment 


        if (idx.first == -1) return true;
        // there is no empty squares. which means we are done

        vector<int>domain = getDomain(idx.first, idx.second);
        if (domain.empty()) return false;
        shuffleArray(domain);
        for (auto i : domain) {
            mat[idx.first][idx.second] = i;
            row[idx.first].push_back(i);
            col[idx.second].push_back(i);

            if (simpleBackTrack(choice)) return true;

            ++btCount;

            mat[idx.first][idx.second] = 0;
            row[idx.first].pop_back();
            col[idx.second].pop_back();
        }
        mat[idx.first][idx.second] = 0;
        return false;
    }

    bool backTrackWithFc(int choice) {
        ++nodeCount;
        pii idx = getVar(choice, n);


        if (idx.first == -2) return false;
        // there is something wrong in our assignment 


        if (idx.second == -1) return true;
        // there is no empty squares. which means we are done
       /// idx = { 11, 11 };
        // returns the domain of (idx.first, idx.second) cell
        vector<int>domain = getDomain(idx.first, idx.second);
        // shuffles the domain. i.e random value order heuristics
        if (domain.empty()) return false;
        shuffleArray(domain);




        for (auto i : domain) {
            if (forwardCheck(idx.first, idx.second, i)) {
                mat[idx.first][idx.second] = i;
                row[idx.first].push_back(i);
                col[idx.second].push_back(i);
                if (backTrackWithFc(choice)) return true;
                ++btCount;
                row[idx.first].pop_back();
                col[idx.second].pop_back();
                mat[idx.first][idx.second] = 0;
            }
        }
        mat[idx.first][idx.second] = 0;
        return false;
    }


    void print() {

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
    }
    void restorMat() {
        mat = originalMat;
    }

    void FcSolve(int choice) {
        btCount = 0;
        cout << "\n\nForward Check\n\n";
        if (choice == 1) {
            cout << "VAH1\n\n";
            restorMat();
            //init();
            nodeCount = 0;
            auto start = chrono::high_resolution_clock::now();
            backTrackWithFc(1);
            auto end = chrono::high_resolution_clock::now();
            print();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << duration.count() << " ms " << "\n";
            cout << nodeCount << " nodes" << endl;
            cout << btCount << " backtracks" << endl;
            cout << "\n\n";

        }

        if (choice == 2) {

            cout << "VAH2\n\n";
            restorMat();
            init();
            auto start = chrono::high_resolution_clock::now();
            backTrackWithFc(2);
            auto end = chrono::high_resolution_clock::now();
            print();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << duration.count() << " ms " << "\n";

            cout << nodeCount << " nodes" << endl;
            cout << btCount << " backtracks" << endl;            cout << "\n\n";
        }


        if (choice == 3) {

            cout << "VAH3\n\n";
            nodeCount = 0;
            restorMat();
            init();
            auto start = chrono::high_resolution_clock::now();
            backTrackWithFc(3);
            auto end = chrono::high_resolution_clock::now();
            print();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << duration.count() << " ms " << "\n";
            cout << nodeCount << " nodes" << endl;
            cout << btCount << " backtracks" << endl;
            cout << "\n\n";

        }

        if (choice == 4) {

            cout << "VAH4\n\n";
            nodeCount = 0;
            restorMat();
            init();
            auto start = chrono::high_resolution_clock::now();
            backTrackWithFc(4);
            auto end = chrono::high_resolution_clock::now();
            print();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << duration.count() << " ms " << "\n";
            cout << nodeCount << " nodes" << endl;
            cout << btCount << " backtracks" << endl;
            cout << "\n\n";
        }

        if (choice == 5) {
            cout << "VAH5\n\n";
            nodeCount = 0;
            restorMat();
            init();
            auto start = chrono::high_resolution_clock::now();
            backTrackWithFc(5);
            auto end = chrono::high_resolution_clock::now();
            print();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << duration.count() << " ms " << "\n";
            cout << nodeCount << " nodes" << endl;
            cout << btCount << " backtracks" << endl;
            cout << "\n\n";
        }
    }


    void simpleSolve(int choice) {
        cout << "\n\nSimple Backtracking\n\n";
        btCount = 0;
        if (choice == 1) {
            cout << "VAH1\n\n";
            restorMat();
            init();
            nodeCount = 0;
            auto start = chrono::high_resolution_clock::now();
            simpleBackTrack(1);
            auto end = chrono::high_resolution_clock::now();
            print();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << duration.count() << " ms " << "\n";
            cout << nodeCount << " nodes" << endl;
            cout << btCount << " backtracks" << endl;
            cout << "\n\n";

        }

        if (choice == 2) {

            cout << "VAH2\n\n";
            restorMat();
            init();
            auto start = chrono::high_resolution_clock::now();
            simpleBackTrack(2);
            auto  end = chrono::high_resolution_clock::now();
            print();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << duration.count() << " ms " << "\n";
            cout << nodeCount << " nodes" << endl;
            cout << btCount << " backtracks" << endl;
            cout << "\n\n";
        }

        if (choice == 3) {


            cout << "VAH3\n\n";
            nodeCount = 0;
            restorMat();
            init();
            auto start = chrono::high_resolution_clock::now();
            simpleBackTrack(3);
            auto end = chrono::high_resolution_clock::now();
            print();
            auto  duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << duration.count() << " ms " << "\n";
            cout << nodeCount << " nodes" << endl;
            cout << btCount << " backtracks" << endl;
            cout << "\n\n";
        }


        if (choice == 4) {


            cout << "VAH4\n\n";
            nodeCount = 0;
            restorMat();
            init();
            auto start = chrono::high_resolution_clock::now();
            simpleBackTrack(4);
            auto end = chrono::high_resolution_clock::now();
            print();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << duration.count() << " ms " << "\n";
            cout << nodeCount << " nodes" << endl;
            cout << btCount << " backtracks" << endl;
            cout << "\n\n";

        }
        if (choice == 5) {
            cout << "VAH5\n\n";
            nodeCount = 0;
            restorMat();
            init();
            auto start = chrono::high_resolution_clock::now();
            simpleBackTrack(5);
            auto end = chrono::high_resolution_clock::now();
            print();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << duration.count() << " ms " << "\n";
            cout << nodeCount << " nodes" << endl;
            cout << btCount << " backtracks" << endl;
            cout << "\n\n";
        }
    }
};
int main() {
    Solver s;
    // s.FcSolve(1);
    // s.FcSolve(2);
    // s.FcSolve(3);
    // s.FcSolve(4);
    // s.FcSolve(5);
    // s.simpleSolve(1);
    s.simpleSolve(2);
    s.simpleSolve(3);
    // s.simpleSolve(4);
    // s.simpleSolve(5);


}



// test 5 
// fc 
// 92503 ms 
// 1460525 nodes
// 1460467 backtracks

