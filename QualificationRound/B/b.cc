#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

const int M = 20;
vector<vector<long long>> a(10, vector<long long>(M));
vector<vector<long long>> b(10, vector<long long>(M));

void init() {
    for (int i = 0; i < 10; i++) a[i][1] = 1;
    for (int m = 2; m < 20; m++) {
        for (int i = 9; i >= 0; i--) {
            if ( i == 9) {
                a[i][m] = a[i][m-1];
            } else {
                a[i][m] = a[i+1][m] + a[i][m-1];
            }
        }
    }

    for (int m = 1; m < 20; m++) {
        for (int i = 0; i < 10; i++) {
            if (i == 0) {
                b[i][m] = a[i][m];
            } else {
                b[i][m] = b[i-1][m] + a[i][m];
            }
        }
    }
}


string _solve(long long n) {
    string ans;

    vector<int> digit;
    while (n) {
        digit.push_back(n % 10);
        n = n / 10;
    }

    for (int i = digit.size() -1; i>= 0; i--) {
        int k = digit[i];
        int flag = 0;
        for (int j = i-1; j >= 0; j--) {
            if (digit[j] < k){
                flag = 1;
                break;
            }
            if (digit[j] > k) {
                break;
            }
        }

        if (flag) {
            ans += to_string(k-1);
            for (int j = 0; j < i; j++) ans += '9';
            return ans;
        }
        ans += to_string(k);
    }
    return ans;
}

void solve() {
    long long n;
    long long ans = 0;
    vector<int> digit;
    cin >> n;
    cout << stoll(_solve(n)) << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    init();
    for (int i = 1; i <= t; i++) {
        cout <<" Case #" << i << ": ";
        solve();
    }
    return 0;
}
