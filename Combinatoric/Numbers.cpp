#include <bits/stdc++.h>

#define ll long long
#define MOD 1000000007
using namespace std;

vector<ll> factorial(2, 1);

ll mod_pow(ll a, ll b){
    ll ans = 1;
    while(b) {
        if (b&1) ans = (ans*a) % MOD;
        b /= 2;
        a = (a*a) % MOD;
    }
    return ans;
}

ll mod_inverse(ll a) {
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

ll combination_number(ll a, ll b) {
    return ((fact(a) * mod_inverse(fact(a-b))) % MOD * mod_inverse(fact(b))) % MOD;
}

// ---- TESTS -----
int main() {
    cout << "100: " << fact(100) << endl;
    for (int i=0; i<=10; i++) {
        cout << i << ": " << fact(i) << endl;
    }
}