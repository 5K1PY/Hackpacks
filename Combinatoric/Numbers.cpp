#include <bits/stdc++.h>

#define ll long long
#define MOD 1000000007
using namespace std;

vector<ll> factorial(2, 1);

ll mod_pow(ll a, ll b) {
    if (b == 0) return 1;
    ll r = mod_pow(a, b/2);
    return (b % 2 ? r*r*a : r*r) % MOD;
}

ll mod_inv(ll a) {
    return mod_pow(a, MOD-2);
}

ll fact(ll n) {
    if (factorial.size() <= n) {
        ll so_far = factorial.size();
        factorial.resize(n+1, 1); 
        for (ll i=so_far; i<=n; i++) {
            factorial[i] = (i*factorial[i-1]) % MOD;
        }
    }
    return factorial[n];
}

ll comb_num(ll a, ll b) {
    return ((fact(a) * mod_inv(fact(a-b))) % MOD * mod_inv(fact(b))) % MOD;
}

// ---- TESTS -----
int main() {
    for (int i=0; i<=100; i++) {
        ll r = 1;
        for (int j=0; j<=9; j++) {
            if (r%MOD != mod_pow(i, j)) {
                cout << i << j;
                return 0;
            }
            r *= i;
        }
    }
}
