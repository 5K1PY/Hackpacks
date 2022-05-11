#include <bits/stdc++.h>

using namespace std;

long long gcd(long long x, long long y) {
    if (x > y) {
        return gcd(y, x);
    }
    if (x == 0) {
        return y;
    }
    return gcd(y%x, x);
}

long long lcm(long long x, long long y) {
    return x*(y / gcd(x, y));
}

int main() {

}