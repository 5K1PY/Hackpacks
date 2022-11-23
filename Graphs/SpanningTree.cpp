#include <bits/stdc++.h>

#define FOR(i, j, k, in) for(int i=j; i<k; i+=in)
#define REP(i, n) FOR(i, 0, n, 1)
#define ALL(a) a.begin(), a.end()
#define ll long long
#define vi vector<int>
#define pll pair<ll, ll>
#define PB push_back

using namespace std;

struct edge {
    int a, b;
    ll val=1;
    int next(int c) {
        if (a == c) return b;
        return a;
    }
};

struct node {
    int id=-1;
    vector<edge> edges;
    ll val=0;
    ll time=-1;
};

int n, m;
vector<node> nodes;

void load() {
    cin >> n >> m;
    nodes.resize(n);
    REP(i, m) {
        int a, b; ll c;
        cin >> a >> b >> c;
        a--; b--;
        nodes[a].edges.PB({a, b, c});
        nodes[b].edges.PB({a, b, c});
    }
}

ll kruskal(int s) {
    ll v, t, c=0;
    vector<pll> h = {{0, s}};
    while (h.size()) {
        pop_heap(ALL(h));
        tie(t, v) = h[h.size()-1]; t*=-1;
        h.pop_back();
        if (nodes[v].time > -1) continue;
        c += t; nodes[v].time = 1;

        for (auto e: nodes[v].edges) {
            h.PB({-e.val, e.next(v)});
            push_heap(ALL(h));
        }
    }
    return c;
}


// ---- TESTS ------
int main() {
    load();
    cout << kruskal(0) << endl;
}