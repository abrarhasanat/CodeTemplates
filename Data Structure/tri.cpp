#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
int trie[N][60];
int idx;
int val(char ch) {
    if (isupper(ch)) return ch - 'A';
    return ch - 'a' + 26;
}
void insert(string s) {
    int cur = 0;
    for (int i = 0; i < s.length(); ++i) {
        int j = val(s[i]);
        ++trie[cur][52];
        if (trie[cur][j] == -1) {
            trie[cur][j] = ++idx;
            memset(trie[idx], -1, sizeof(trie[idx]));
            trie[idx][52] = 0;
        }
        cur = trie[cur][j];
    }
    trie[cur][52] += 1;
}
int  traverse(string s) {
    int cur = 0;
    for (int i = 0; i < s.length(); ++i) {
        int j = val(s[i]);
        if (trie[cur][j] == -1)  return 0;
        cur = trie[cur][j];
    }
    return trie[cur][52];

}
void deleteA(string  s, int  pos, int curr) {
    if (pos < 0)
        return;
    else {
        deleteA(s, pos - 1, Node[curr][val(s[pos])]);
        Node[Node[curr][val(s[pos])]][52]--;
        if (Node[Node[curr][val(s[pos])]][52] == 0)
            Node[curr][val(s[pos])] = -1;
    }
}
int main() {


}