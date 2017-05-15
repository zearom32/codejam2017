#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <cstdlib>
#include <message.h>
#include "weird_editor.h"

using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

const LL mod = 1000000007;

vector<LL> split_nodes(LL N, LL nodes) {
    LL step = (N - 1) / nodes + 1;
    vector<LL> ans;
    LL st = 0;
    for (LL i = 0; i <= nodes; i++) {
        ans.push_back(st);
        st = min(N, st + step);
    }
    return ans;
}

const LL master = 0;
const LL myid = MyNodeId();
LL nodes = NumberOfNodes();
const LL N = GetNumberLength();
const LL inf = 1LL << 32;


void solve(vector<LL>& a, vector<LL>& b, LL& len) {
    len = 0;
    if (a.size() == 0) return;
    b[0] = a[0]; len++;
    for (LL i = 1; i < a.size(); i++) {
        while (len > 0 && a[i] > b[len-1]) len--;
        b[len++] = a[i];
    }
}

int main()
{
    vector<LL> index = split_nodes(N, nodes);
    LL cur = 0;
    LL minn = inf;
    LL pre = -1;
    LL ans0 = 0;

    if (myid > N-1) {
        return 0;
    }

    nodes = min(nodes, N);

    vector<LL> a;
    for (LL i = index[myid]; i < index[myid+1]; i++) {
            LL k = GetDigit(i);
            a.push_back(k);
    }

    vector<LL> b = a;
    LL len = 0;
    solve(a, b, len);
    LL ans = 0;
    PutLL(master, len);

    for (LL i = 0; i < len; i++) {
        PutLL(master, b[i]);
    }
    Send(master);

    if (myid == master) {
        len = 0;
        b.resize(N);
        for (LL i = 0; i < nodes; i++) {
            if (i == master) {
                Receive(i);
                LL k = GetLL(i);
                for (LL j = 0; j < k; j++) {
                    LL w = GetLL(i);
                    b[len++] = w;
                }
            } else {
                Receive(i);
                LL k = GetLL(i);
                if (k > 0) {
                    LL w = GetLL(i);
                    while (len > 0 && b[len-1] < w) len--;
                    b[len++] = w;
                }
                for (LL j = 1; j < k; j++) {
                    LL w = GetLL(i);
                    b[len++] = w;
                }
            }
        }

        for (LL i = len; i < N; i++) {
            b[i] = 0;
        }
        ans = 0;
        for (LL i = 0; i < N; i++) {
            ans = (ans*10 + b[i]) % mod;
        }
        ans = ans % mod;
        ans = (ans + mod) % mod;
        cout << ans << endl;
    }


    return 0;
}