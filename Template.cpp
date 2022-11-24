#include <bits/stdc++.h>

using namespace std;

// types
#define ll long long
#define vi vector<int>
#define vll vector<ll>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vpii vector<pii>
#define vpll vector<pll>

// iterators
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(a) a.begin(), a.end()
#define RALL(a) a.end(), a.begin()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)

// shortcuts
#define F first
#define S second
#define PB push_back
#define MP make_pair

// constants
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
#define INF numeric_limits<ll>::max()
#define NINF numeric_limits<ll>::min()
#define INF_I numeric_limits<int>::max()
#define NINF_I numeric_limits<int>::min()

template<typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& p) {
    os << p.F << " " << p.S;
    return os;
}

string SEP = " ";
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    string s;
    for (auto&& x : v) {
        os << s << x;
        s = SEP;
    }
    return os;
}

struct DBG {};
DBG dbg;

template<typename T>
DBG& operator<<(DBG& d, const T& x) {
#ifdef DEBUG
    cout << x;
#endif
    return dbg;
}

// Support for endl
DBG& operator<<(DBG& d, ostream& (*f)(ostream& os)) {
#ifdef DEBUG
    cout << f;
#endif
    return dbg;
}

void solve() {

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n=1;
    cin >> n;
    for (ll i=0; i<n; i++) {
        solve();
    }
    return 0;
}
