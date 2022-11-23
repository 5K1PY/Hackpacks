#include <bits/stdc++.h>

using namespace std;

struct dfu_item {
    dfu_item * father=NULL;
    long long rank=0;
    long long value;
};

dfu_item * dfu_find(dfu_item * item) {
    if (item->father == NULL) {
        return item;
    } else {
        item->father = dfu_find(item->father);
        return item->father;
    }
}

bool dfu_same(dfu_item * a, dfu_item * b) {
    return dfu_find(a) == dfu_find(b);
}

void dfu_union(dfu_item * a, dfu_item * b) {
    a = dfu_find(a);
    b = dfu_find(b);
    if (a == b) return;
    if (a->rank < b->rank) {
        a->father = b;
    } else {
        b->father = a;
        a->rank += a->rank == b->rank;
    }
}


// --------------- TESTS -----------------
int main() {
    int n = 10;
    vector<dfu_item> v(n);
    for (int i=0; i<n; i++) {
        v[i].value = i;
    }
    for (int i=0; i<n-1; i++) {
        if (dfu_same(&v[0], &v[i+1])) {
            cout << "bug!" << endl;
        }
        dfu_union(&v[i], &v[i+1]);
        if (!dfu_same(&v[0], &v[i+1])) {
            cout << "bug!" << endl;
        }
    }   
}
