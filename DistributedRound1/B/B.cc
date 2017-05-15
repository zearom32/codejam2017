#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <cstdlib>
#include <message.h>
#include "pancakes.h"

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

const LL master = 0;
const LL myid = MyNodeId();
const LL nodes = NumberOfNodes();
const LL M = GetStackSize();
const LL N = GetNumDiners();
const LL inf = 1LL << 32;
int main()
{
    vector<LL> index = split_nodes(M, nodes);
    LL cur = 0;
    LL minn = inf;
    LL pre = -1;
    LL ans0 = 0;
    for (LL i = index[myid]; i < index[myid+1]; i++) {
        LL cur = GetStackItem(i);
        if (cur < pre) ans0 ++;
        pre = cur;
    }
    PutLL(master, ans0);
    Send(master);

    if (myid == master) {
        LL ans = 0;
        for (LL i = 0; i < nodes; i++) {
            Receive(i);
            LL k = GetLL(i);
            ans += k;
        }

        for (LL i = 1; i < nodes; i++) {
            if (index[i] != index[i-1] && index[i] < M) {
                LL p = GetStackItem(index[i]-1);
                LL q=  GetStackItem(index[i]);
                if (q < p) ans++;
            }
        }
        cout << ans + 1 << endl;
    }
    return 0;
}
