#include <bits/stdc++.h>

using namespace std;

struct edge {
    int node1, node2;
    int next(int node) {
        if (node1 == node) {
            return node2;
        } 
        return node1;
    }
    long long value=0;
};

struct node {
    int id=-1;
    vector<edge> edges;
    long long value;

    long long time=-1;
    bool visited=false;
};

struct graph {
    int n, m;
    vector<node> nodes;
};

void bfs(graph * g, int start) {
    vector<int> now = {start};
    vector<int> next;
    int time=0;
    while (now.size()) {
        next.resize(0);
        for (int i: now) {
            if (g->nodes[i].visited) {
                continue;
            }
            g->nodes[i].visited = true;
            g->nodes[i].time = time;
            for (int j=0; j<g->nodes[i].edges.size(); j++) {
                next.push_back(g->nodes[i].edges[j].next(i));
            }
        }
        time++;
        now = next;
    }
}


// ------ TESTS ---------
graph load_graph(bool valued_nodes=false, bool valued_edges=false, bool decrease=false, bool oriented=false) {
    graph g;
    cin >> g.n >> g.m;
    g.nodes.resize(g.n);
    for (int i=0; i<g.n; i++) {
        g.nodes[i].id = i;
        if (valued_nodes) {
            cin >> g.nodes[i].value;
        }
    }
    for (int i=0; i<g.m; i++) {
        int a, b; long long c=0;
        cin >> a >> b;
        if (valued_edges) {
            cin >> c;
        }
        if (decrease) {
            a--; b--;
        }
        g.nodes[a].edges.push_back({a, b, c});
        if (!oriented) {
            g.nodes[b].edges.push_back({a, b, c});
        }
    }
    return g;
}

int main() {
    graph g = load_graph();
    bfs(&g, 0);
    for (int i=0; i<g.n; i++) {
        cout << g.nodes[i].id << ": " << g.nodes[i].time << endl;
    }
}