#include <bits/stdc++.h>

#define FOR(i, j, k, in) for(int i=j; i<k; i+=in)
#define REP(i, n) FOR(i, 0, n, 1)
#define ll long long
using namespace std;

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, b % a);
}

ll extgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

ll lcm(ll x, ll y) {
    return x*(y / gcd(x, y));
}

vector<bool> primes;
void erathostenes(ll n) {
    primes.resize(n+1, true);
    primes[0] = primes[1] = 0;
    REP(i, n+1) {
        if (primes[i]) {
            FOR(j, i*i, n, i) primes[j] = 0;
        }
    }
}

// --------------- TESTS -----------------
int main() {
    erathostenes(101);
    REP(i, 102) {
        if (primes[i]) {
            cout << i << endl;
        }
    }
}