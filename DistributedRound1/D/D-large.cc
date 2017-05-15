//
// Created by yaozerong on 17-5-14.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <cstdlib>
#include <message.h>
#include "todd_and_steven.h"

using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

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

const LL mod = 1000000007;
const LL master = 0;
const LL myid = MyNodeId();
const LL nodes = NumberOfNodes();
const LL tl = GetToddLength();
const LL sl = GetStevenLength();

const LL inf = 1LL << 32;

LL get_idx2(LL st) {
    LL l = 1; LL r = sl;
    while (l != r) {
        LL mid = (l + r) / 2;
        LL k = GetStevenValue(mid);
        if (k < st) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

LL get_idx1(LL st) {
    LL l = 1; LL r = tl;
    while (l != r) {
        LL mid = (l + r) / 2;
        LL k = GetToddValue(mid);
        if (k < st) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

int main()
{
    // vector<LL> index = split_nodes(M, nodes);
    LL cur = 0;
    LL pre = -1;
    LL ans = 0;

    vector<LL> numbers;

    LL minn = GetToddValue(0);
    LL maxn = GetToddValue(tl-1);
    minn = min(minn, GetStevenValue(0)) - 100;
    maxn = max(maxn, GetStevenValue(sl-1)) + 100;

    LL len = maxn - minn;

    // firstly split into 100
    vector<LL> index1 = split_nodes(len, 100);

    for (LL piece = 0; piece != 100; piece++) {
        LL st = index1[piece]; LL ed = index1[piece+1];
        LL n = ed - st;
        vector<LL> index2 = split_nodes(n, nodes);

        LL l = st + index2[myid]; LL r = st + index2[myid+1];
        vector<LL> c;
        if (r != l ) {
            LL s1 = get_idx1(l);
            LL s2 = get_idx2(l);

            while (1) {
            }
        }
    }



    if (myid == master) {

        for ( LL i = 0; i < numbers.size(); i++) {
            ans = (ans + (numbers[i]^i)) % mod;
        }
        cout << ans << endl;
    }

    return 0;
}