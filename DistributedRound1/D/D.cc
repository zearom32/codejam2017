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

int main()
{
   // vector<LL> index = split_nodes(M, nodes);
    LL cur = 0;
    LL minn = inf;
    LL pre = -1;
    LL ans = 0;

    vector<LL> numbers;
    if (myid == master) {
        LL k;
        for (LL i = 0; i < tl; i++) {
            k = GetToddValue(i);
            numbers.push_back(k);
        }
        for (LL i = 0; i < sl; i++) {
            k = GetStevenValue(i);
            numbers.push_back(k);
        }
        sort(numbers.begin(), numbers.end());
        for ( LL i = 0; i < numbers.size(); i++) {
            ans = (ans + (numbers[i]^i)) % mod;
        }
        cout << ans << endl;
    }

    return 0;
}