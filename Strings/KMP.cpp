#include <bits/stdc++.h>

#define ll long long

using namespace std;

vector<int> back;

int _kmp_step(int pos, char c, string * needle) {
    // Uncomment for non-crossing finds
    // if (pos == needle->size()) {
    //     return 0;
    // }
    while (pos == needle->size() || (needle->at(pos) != c && pos > 0)) {
        pos = back[pos-1];
    }
    if (needle->at(pos) == c) {
        return pos+1;
    } else {
        return 0;
    }
}

vector<int> kmp(string haystack, string needle) {
    back.resize(needle.size(), 0);
    for (int i=1; i<needle.size(); i++) {
        back[i] = _kmp_step(i-1, needle[i], &needle);
    }

    int state = 0;
    vector<int> results;
    for (int i=0; i<haystack.size(); i++) {
        state = _kmp_step(state, haystack[i], &needle);
        if (state == needle.size()) {
            results.push_back(i - needle.size() + 1);
        }
    }
    return results;
}

// ----- DRIVER CODE -----
int main() {
    ll n;
    cin >> n;
    string a, b;
    for (int i=0; i<n; i++) {
        cin >> a >> b;
        auto x = kmp(a, b);
        if (x.size()) {
            cout << x.size() << endl;
            for (int i: x) {
                cout << i+1 << " ";
            }
            cout << endl;
        } else {
            cout << "Not Found" << endl;
        }
        cout << endl;
    }
}