#include  <bits/stdc++.h>
using namespace std;
const int N = 1e3;
int  n, k;
void multiply(int a[n][n], int b[n][n], int res[][n]) {
    int mul[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mul[i][j]  = 0 ;
            for (int k = 0; k < n; ++k) {
                mul[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            res[i][j] = mul[i][j];
    }
}
void pow(int G[n][n], int res[n][n], int p) {
    if (p == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                res[i][j] = G[i][j];
            }
        }
        return;
    }
    pow(G, res, n / 2);
    multiply(G, G, res);
    if (n % 2) multiply(res, G, res);
}
int main() {
    cin >> n >> k ;
    int G[n][n] ; 
    for(int i = 0 ; i < n ; ++i) { 
        for(int j =  0 ; j <  n ; ++j) cin >> G[i][j] ; 
    }
    int res[n][n] ; 
    power(G , res , k ) ; 


}