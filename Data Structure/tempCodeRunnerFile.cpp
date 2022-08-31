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
int main() {
    int t;cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        int n; cin >> n;
        idx = 0;
        memset(trie[0], -1, sizeof(trie[0]));
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            if (s.length() <= 2) continue;
            sort(s.begin() + 1, s.end() - 1);
            cin.ignore(); 
            insert(s);
        }
        cout << "Case " << tc << endl; 
        int m; cin >> m;
        getchar();
        while (m--) {
            string sentence;
            getline(cin, sentence);
        
            int i = 0;
            ll ans = 1;
            //cout << sentence.size() << " anbaa " << endl;
            while (sentence[i]) {
                if (!isalpha(sentence[i])) {
                    ++i;
                    continue;
                }
                string word;
                while (sentence[i] && isalpha(sentence[i])) {
                    word.push_back(sentence[i]);
                    ++i;
                }
            
                if (word.length() < 3) continue;
                sort(word.begin() + 1, word.end() - 1);
                ans *= traverse(word);
            }
            cout << ans << "\n";
        }
    }

}