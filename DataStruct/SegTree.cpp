#include <bits/stdc++.h>

using namespace std;


struct segtree {
    enum Mode {st_sum, st_min, st_max};
    struct _update {
        enum Mode {add, set};
        Mode mode;
        long long value;
    };

    struct _node {
        vector<_update> updates;
        int start, end;
        long long value;
    };

    // ---- change this part ----
    Mode mode=st_sum;

    // identity value config
    long long identity_value;
    void _init_mode() {
        switch (mode)
        {
            case st_sum:
                identity_value = 0; break;
            case st_min:
                identity_value = numeric_limits<long long>::max(); break;
            case st_max:
                identity_value = numeric_limits<long long>::min(); break;
        }
    }

    // operation config and node building
    long long _op(long long a, long long b) {
        switch (mode)
        {
            case st_sum:
                return a + b; break;
            case st_min:
                return min(a, b);; break;
            case st_max:
                return max(a, b); break;
        }
    }
    _node _build_node(_node * a, _node * b) {
        _node c;
        c.value = _op(a->value, b->value);
        c.start = a->start;
        c.end = b->end;
        return c;
    }

    // events evaluation
    _update _merge_updates(_update * a, _update * b) {
        if (b->mode == _update::set) {
            return {_update::set, b->value};
        } else if (a->mode == _update::set && b->mode == _update::add) {
            return {_update::set, a->value + b->value};
        } else if (a->mode == _update::add && b->mode == _update::add) {
            return {_update::add, a->value + b->value};
        }
    }

    void _apply_update(_node * a, _update * u) {
        if (mode == st_sum) {
            if (u->mode == _update::add) {
                a->value += (a->end - a->start) * u->value;
            } else if (u->mode == _update::set) {
                a->value = (a->end - a->start) * u->value;
            }
        } else if (mode == st_min || mode == st_max) {
            if (u->mode == _update::add) {
                a->value += u->value;
            } else if (u->mode == _update::set) {
                a->value = u->value;
            }
        }
    }
    // --------------------------

    int leaves;
    vector<_node> nodes;
    segtree(vector<long long> * values) {
        _init_mode();

        leaves=1;
        while (leaves < values->size()) {
            leaves *= 2;
        }
        nodes.resize(2*leaves-1);
        for (int i=nodes.size()-1; i>=0; i--) {
            if (i >= leaves - 1) {
                int j = i - (leaves - 1);
                if (j < values->size()) {
                    nodes[i].value = values->at(j);
                } else {
                    nodes[i].value = identity_value;
                }
                nodes[i].start = j;
                nodes[i].end = j+1;
            } else {
                nodes[i] = _build_node(&nodes[2*i+1], &nodes[2*i+2]);
            }
        }
    }

    long long query(int start, int end, int index=0) {
        // start included, end excluded

        if (start >= end) {
            // invalid query
            return identity_value;
        } else if (end <= nodes[index].start || nodes[index].end <= start) {
            // no intersection
            return identity_value;
        } else if (start <= nodes[index].start && nodes[index].end <= end) {
            // full intersection
            _push_updates(index);
            return nodes[index].value;
        } else {
            // partial intersection
            _push_updates(index);
            return _op(
                query(start, end, 2*index+1),
                query(start, end, 2*index+2)
            );
        }
    }

    void update(int start, int end, _update u, int index=0) {
        // start included, end excluded

        if (start >= end) {
            // invalid query
        } else if (end <= nodes[index].start || nodes[index].end <= start) {
            // no intersection
            _push_updates(index);
        } else if (start <= nodes[index].start && nodes[index].end <= end) {
            // full intersection
            nodes[index].updates.push_back(u);
            _push_updates(index);
        } else {
            // partial intersection
            _push_updates(index);
            update(start, end, u, 2*index+1);
            update(start, end, u, 2*index+2);
            nodes[index] = _build_node(&nodes[2*index+1], &nodes[2*index+2]);
        }
    }

    void _push_updates(int index) {
        if (nodes[index].updates.size() == 0) {
            return;
        }
        reverse(nodes[index].updates.begin(), nodes[index].updates.end());
        for (int i=nodes[index].updates.size()-1; i>0; i--) {
            _update u = _merge_updates(&nodes[index].updates[i], &nodes[index].updates[i-1]);
            nodes[index].updates.pop_back();
            nodes[index].updates.pop_back();
            nodes[index].updates.push_back(u);
        }
        _apply_update(&nodes[index], &nodes[index].updates[0]);
        if (index < leaves - 1) {
            // not a leaf
            nodes[2*index+1].updates.push_back(nodes[index].updates[0]);
            nodes[2*index+2].updates.push_back(nodes[index].updates[0]);
        }
        nodes[index].updates.pop_back();
    }
};



// --------------- TESTS -----------------
bool test_query(segtree * s, vector<long long> * vals, int start, int end) {
    cout << "q? " << start << " " << end << endl;
    long long x = s->query(start, end);
    
    long long res;
    if (s->mode == segtree::st_sum) {
        res = 0;
        for (int i=start; i<end; i++) {
            res += vals->at(i);
        }
    } else if (s->mode == segtree::st_min) {
        res = numeric_limits<long long>::max();
        for (int i=start; i<end; i++) {
            res = min(res, vals->at(i));
        }
    } else if (s->mode == segtree::st_max) {
        res = numeric_limits<long long>::min();
        for (int i=start; i<end; i++) {
            res = max(res, vals->at(i));
        }
    }
    cout << "q! (" << x << ", " << res << ")" << endl;
    return x == res;
}

int main() {
    srand(time(NULL));

    int n = 1000;
    vector<long long> vals(n, 0);
    for (int i=0; i<n; i++) {
        vals[i] = rand() % 1000;
        // cout << vals[i] << " ";
    }
    cout << endl;
    segtree s(&vals);

    int t;
    // for (int i=0; i<100; i++) {
    //     int start = rand() % (n-1);
    //     int end = (rand() % (n-start)) + start;
        
    //     if (!test_query(&s, &vals, start, end)) {
    //         return 0;
    //     }
    // }
    // cout << "done";
    // return 0;

    for (int i=0; i<1000; i++) {
        t = rand() % 2;
        int start = rand() % (n-1);
        int end = (rand() % (n-start)) + start;
        
        if (t == 0) {
            if (!test_query(&s, &vals, start, end)) {
                return 0;
            }
        } else {
            t = rand() % 5;
            if (t == 0) {
                t = rand() % 10;
                cout << "set " << start << " " << end << " " << t << endl;
                s.update(start, end, {segtree::_update::set, t});
                for (int i=start; i<end; i++) {
                    vals[i] = t;
                }
            } else {
                t = rand() % 10 + 1;
                cout << "add " << start << " " << end << " " << t << endl;
                s.update(start, end, {segtree::_update::add, t});
                for (int i=start; i<end; i++) {
                    vals[i] += t;
                }
            }
        }
    }
    cout << "done" << endl;
}
