#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

void flip(vector<int>& a, int start, int len) {
    for (int i = start; i != start + len; i++) {
        a[i] ^= 1;
    }
}

void solve() {
    string s;
    cin >> s;
    vector<int> a(s.size());
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '-') {
            a[i] = 1;
        }
    }
    int k;
    cin >> k;
    int ans = 0;
    for (int i = 0; i <= s.size() - k; i++) {
        if (a[i]) {
            flip(a, i, k);
            ans++;
        }
    }

    int flag = 0;
    for (int i = 0; i < s.size(); i++) {
        if (a[i]) {
            flag = 1;
        }
    }

    if (flag) {
        cout <<"IMPOSSIBLE"<<endl;
    } else {
        cout << ans << endl;
    }
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
