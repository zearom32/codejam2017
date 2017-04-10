#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

using namespace std;


long long _solve(long long n, long long k) {
    map<long long, long long> mm;
    mm[n] = 1;
    long long ans = n;
    while (k > 0) {
        auto number = mm.rbegin()->first;
        ans = number;
        auto count = mm.rbegin()->second;
        if (count > k) {
            count = k; k-= count;
            mm[number] -= count;
        } else {
            k -= count;
            mm.erase(number);
        }
        long long k1 = number / 2;
        long long k2 = (number -1) / 2;
        if (mm.count(k1)) {
            mm[k1] += count;
        } else {
            mm[k1] = count;
        }
        if (mm.count(k2)) {
            mm[k2] += count;
        } else {
            mm[k2] = count;
        }
    }
    return ans;
}

void solve() {
    long long n, k;
    cin >> n >> k;

    long long m = _solve(n, k);
    cout << m / 2 << " " << (m-1) / 2 << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout <<" Case #" << i << ": ";
        solve();
    }
    return 0;
}
