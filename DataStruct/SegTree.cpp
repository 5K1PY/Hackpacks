#include <bits/stdc++.h>

#define FOR(i, j, k, in) for(int i=j; i<k; i+=in)
#define RFOR(i, j, k, in) for(int i=j; i>=k; i-=in)
#define REP(i, n) FOR(i, 0, n, 1)
#define RREP(i, n) RFOR(i, n, 0, 1)
#define ll long long
#define vll vector<ll>

using namespace std;

struct segtree {
    int ival=0; // identity value
    int n; // num of nodes
    vll v; // values
    vll up; // updates

    segtree(vll &vals) {
        n = 1;
        while (n < vals.size()) n *= 2;
        n = 2*n-1;

        v.resize(n, ival);
        up.resize(n, 0);
        REP(i, vals.size()) {
            v[n/2+i] = vals[i];
        }
        RREP(i, n/2-1) {
            v[i] = op(v[2*i+1], v[2*i+2]);
        }
    }

    ll op(ll a, ll b) {
        return a + b;
    }

    // queries
    ll query(int l, int r) {
        return q(0, min(l, r), max(l, r)+1, 0, n/2+1);
    }

    ll q(int i, int l, int r, int s, int e) {
        push(i, s, e);
        if (s >= r || e <= l) return ival;
        if (l <= s && e <= r) return v[i];
        int m = (s+e)/2;
        return op(q(2*i+1, l, r, s, m), q(2*i+2, l, r, m, e));
    }

    // updates
    void update(int l, int r, ll val) {
        u(0, min(l, r), max(l, r)+1, 0, n/2+1, val);
    }

    void u(int i, int l, int r, int s, int e, ll val) {
        push(i, s, e);
        if (s >= r || e <= l) return;
        if (l <= s && e <= r) { up[i] += val; push(i, s, e); return; }    
        int m = (s+e)/2;
        u(2*i+1, l, r, s, m, val); u(2*i+2, l, r, m, e, val);
        v[i] = op(v[2*i+1], v[2*i+2]);
    }

    void push(int i, int l, int r) {
        v[i] += up[i]*(r-l);
        if (i < n/2) {
            up[2*i+1] += up[i];
            up[2*i+2] += up[i];
        }
        up[i] = 0;
    }
};



// --------------- TESTS -----------------
bool test_query(segtree * s, vector<long long> * vals, int start, int end) {
    cout << "q? " << start << " " << end << endl;
    long long x = s->query(start, end);
    
    ll res = 0;
        for (int i=start; i<=end; i++) {
            res += vals->at(i);
        }
        cout << "q! (" << x << ", " << res << ")" << endl;
    
    return x == res;
}

int main() {
    srand(time(NULL));

    int n = 4;
    vector<long long> vals(n, 0);
    for (int i=0; i<n; i++) {
        vals[i] = rand() % 1000;
        // cout << vals[i] << " ";
    }
    cout << endl;
    segtree s(vals);

    int t;
    // for (int i=0; i<100; i++) {
    //     int start = rand() % (n-1);
    //     int end = (rand() % (n-start)) + start;
        
    //     if (!test_query(&s, &vals, start, end)) {
    //         return 0;
    //     }
    // }

    for (int i=0; i<1000; i++) {
        t = rand() % 2;
        int start = rand() % (n-1);
        int end = (rand() % (n-start-1)) + start;
        
        if (t == 0) {
            if (!test_query(&s, &vals, start, end)) {
                return 0;
            }
        } else {
            t = rand() % 5;
            
            t = rand() % 10 + 1;
            cout << "add " << start << " " << end << " " << t << endl;
            s.update(start, end, t);
            for (int i=start; i<=end; i++) {
                vals[i] += t;
            }
            
        }
    }
    cout << "done" << endl;
}
