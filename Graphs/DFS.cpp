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

    long long in_time=-1, out_time=-1;
    bool visited=false;
};

struct graph {
    int n, m;
    vector<node> nodes;
};

int dfs(graph * g, int start, int time=0) {
    if (g->nodes[start].visited) {
        return time;
    }
    // open node
    g->nodes[start].visited = true;
    g->nodes[start].in_time = time++;

    for (int j=0; j<g->nodes[start].edges.size(); j++) {
        time = dfs(g, g->nodes[start].edges[j].next(start), time);
    }
    // close node
    g->nodes[start].out_time = time++;
    return time;
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
    dfs(&g, 0);
    for (int i=0; i<g.n; i++) {
        cout << g.nodes[i].id << ": " << g.nodes[i].in_time << " " << g.nodes[i].out_time << endl;
    }
}