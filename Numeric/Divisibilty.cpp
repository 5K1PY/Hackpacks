#include <bits/stdc++.h>

#define ll long long
using namespace std;

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, b % a);
}

ll lcm(ll x, ll y) {
    return x*(y / gcd(x, y));
}

int main() {

}