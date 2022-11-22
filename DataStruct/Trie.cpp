#include <bits/stdc++.h>

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

using namespace std;

struct trie {
    bool word = false;
    vector<trie*> sons;

    trie() { sons.resize(26, NULL); }
};

void insert_word(trie *t, string s) {
    REP(i, s.size()) {
        if (t->sons[s[i] - 'a'] == NULL) t->sons[s[i] - 'a'] = new trie();
        t = t->sons[s[i] - 'a'];
    }
    t->word = true;
}

bool search_word(trie *t, string s) {
    REP(i, s.size()) {
        if (t->sons[s[i] - 'a'] == NULL) return false;
        t = t->sons[s[i] - 'a'];
    }
    return t->word;
}

void del_word(trie *t, string s) {
    REP(i, s.size()) {
        if (t->sons[s[i] - 'a'] == NULL) return;
        t = t->sons[s[i] - 'a'];
    }
    t->word = false;
}


// --------------- TESTS -----------------
int main() {
    trie *t = new trie();
    insert_word(t, "aba");
    insert_word(t, "abc");
    cout << search_word(t, "aba") << endl;
    cout << search_word(t, "ab") << endl;
    cout << search_word(t, "abc") << endl;
    cout << search_word(t, "abd") << endl;
    del_word(t, "abc");
    cout << search_word(t, "abc") << endl;
}


