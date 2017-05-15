#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <cstdlib>
#include <message.h>
#include "query_of_death.h"

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
const LL N = GetLength();

const LL inf = 1LL << 32;

int main()
{
    vector<LL> index = split_nodes(N, nodes-1);
    LL cur = 0;
    LL minn = inf;
    LL pre = -1;
    LL ans = 0;
    LL sum = 0;
    if (myid != master) {
        vector<LL> a;
        for (LL i = index[myid-1]; i < index[myid]; i++) {
            LL k = GetValue(i);
            a.push_back(k);
            sum += k;
        }
        LL flag = 0;
        LL loop = 1;
        if (N < 110000) {
            loop = 100;
        }

        for (LL j = 0; j < loop; j++) {
            for (LL i = index[myid - 1]; i < index[myid]; i++) {
                LL k = GetValue(i);
                if (a[i - index[myid - 1]] != k) {
                    flag = 1;
                }
            }
        }

        if (flag) {
            PutLL(master, 1);
            PutLL(master, myid);
            Send(master);
            return 0;
        } else {
            PutLL(master, 0);
            PutLL(master, sum);
            Send(master);
        }

        Receive(master);
        LL  st = GetLL(master);
        LL ed = GetLL(master);

        for (LL i = st; i != ed; i++) {
            LL k = GetValue(i);
            for (LL j = 0; j < 100; j++) {
                LL w = GetValue(i);
                if (w != k) {
                    PutLL(master, 1);
                    PutLL(master, i);
                    Send(master);
                    return 0;
                }
            }
        }
        PutLL(master, 0);
        Send(master);
        return 0;
    }

    if (myid == master) {
        sum = 0;
        LL bad_id = 0;
        for (LL i = 1; i < nodes; i++) {
            Receive(i);
            LL flag = GetLL(i);
            if (flag == 0) {
                LL w = GetLL(i);
                sum += w;
            } else {
                bad_id = GetLL(i);
            }
        }

        if (bad_id != 0) {
            LL ux = index[bad_id-1]; LL uy = index[bad_id];
            LL len = uy - ux;
            vector<LL> new_index = split_nodes(len, nodes-2);
            LL idx = 0;
            for (LL i = 1; i < nodes; i++) {
                if (i != bad_id) {
                    LL st = ux + new_index[idx]; LL ed = ux + new_index[idx+1];
                    idx++;
                    PutLL(i, st);
                    PutLL(i, ed);
                    Send(i);
                }
            }

            LL qod = 0;
            for (LL i = 1; i < nodes; i++) {
               if (i != bad_id) {
                   Receive(i);
                   LL flag = GetLL(i);
                   if (flag) {
                       qod = GetLL(i);
                   }
               }
            }

            for (LL i = index[bad_id-1]; i < index[bad_id]; i++) {
                if (i != qod) {
                    LL w = GetValue(i);
                    sum += w;
                }
            }

            LL w = GetValue(qod);
            sum += w;
        }
        cout << sum << endl;
    }

    return 0;
}