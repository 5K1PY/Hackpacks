#include <bits/stdc++.h>

#define ll long long
#define PB push_back
using namespace std;

vector<int> back;

int _step(int pos, char c, string& n) {
    // Uncomment for non-crossing finds
    // if (pos == n->size()) {
    //     return 0;
    // }
    while (pos == n.size() || (n[pos] != c && pos > 0)) {
        pos = back[pos-1];
    }
    if (n[pos] == c) {
        return pos+1;
    } else {
        return 0;
    }
}

vector<int> kmp(string h, string n) {
    back.resize(n.size(), 0);
    for (int i=1; i<n.size(); i++) {
        back[i] = _step(back[i-1], n[i], n);
    }

    int state = 0;
    vector<int> results;
    for (int i=0; i<h.size(); i++) {
        state = _step(state, h[i], n);
        if (state == n.size()) {
            results.PB(i - n.size() + 1);
        }
    }
    return results;
}

// ----- TESTS -----
int main() {
    string a, b;
    cin >> a >> b;
    auto x = kmp(a, b);
    cout << x.size() << endl;
}