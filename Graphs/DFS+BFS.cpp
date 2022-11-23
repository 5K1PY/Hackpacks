#include <bits/stdc++.h>

#define FOR(i, j, k, in) for(int i=j; i<k; i+=in)
#define REP(i, n) FOR(i, 0, n, 1)
#define ll long long
#define vi vector<int>
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
        int a, b;
        cin >> a >> b;
        a--; b--;
        nodes[a].edges.PB({a, b});
        nodes[b].edges.PB({a, b});
    }
}

void bfs(int s) {
    ll t=0;
    vi a={s}, b;
    while (a.size()) {
        b = {};
        for (auto v: a) {
            if (nodes[v].time > -1) {
                continue;
            }
            nodes[v].time = t;
            for (auto e: nodes[v].edges) {
                b.PB(e.next(v));
            }
        }
        a = b;
        t++;
    }
}

int dfs(int s) {
    if (nodes[s].time > -1) return 0;
    nodes[s].time = 1;
    for (auto e: nodes[s].edges) {
        nodes[s].time += dfs(e.next(s));
    }
    return nodes[s].time;
}

// ---- TESTS ------
int main() {
    load();
    dfs(0);
    REP(i, n) {
        cout << nodes[i].time << endl;
    }
}