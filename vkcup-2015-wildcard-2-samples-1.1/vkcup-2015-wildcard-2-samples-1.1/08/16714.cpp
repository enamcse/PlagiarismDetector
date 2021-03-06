#include <algorithm>
#include <iomanip>
#include <istream>
#include <map>
#include <ostream>
#include <set>
#include <sstream>
#include <utility>
#include <vector>
using namespace std;
// Solution template generated by caide

typedef long long ll;

class Solution {
public:
    vector<int> a;
    void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        a.resize(n);
        for (int& i : a)
            in >> i;
        for (int i = 1; i < n; ++i)
            a[i] -= a[0];
        a[0] = 0;
        vector<int> cnt(n);
        int m;
        in >> m;
        for (int i = 0; i < m; ++i) {
            int s;
            in >> s;
            cnt[s-1]++;
        }
        ll whole = m / (2*n-2);
        cnt[0] -= whole;
        cnt[n-1] -= whole;
        for (int i = 1; i < n-1; ++i)
            cnt[i] -= 2*whole;
        if ((m % (2*n-2)) == 0) {
            for (int i = 2; i < n; ++i)
                if (a[i] - a[i-1] != a[1]) {
                    out << -1 << endl;
                    return;
                }
            out << (2 * whole * (ll)a.back() - a[1]) << endl;
            return;
        }
        int res = -1;
        res = solveSmall(cnt);
        if (res == -1)
            res = solveLarge(cnt);
        if (res == -1)
            res = solveMiddle(cnt);

        vector<int> b(n);
        for (int i = 0; i < n; ++i)
            b[i] = a[n-1] - a[n-i-1];
        a.swap(b);
        reverse(cnt.begin(), cnt.end());
        if (res == -1)
            res = solveMiddle(cnt);

        if (res == -1) {
            out << -1 << endl;
            return;
        }
        out << (2 * whole * (ll)a.back() + res) << endl;
    }
    ll solveMiddle(const vector<int>& c) {
        int n = (int)c.size();
        if (c[n-1] != 1 || c[n-2] != 2)
            return -1;
        int j = n-2;
        while (c[j] == 2)
            --j;
        int i = 0;
        if (c[i] > 1)
            return -1;
        while (c[i] == 0)
            ++i;
        for (int u = i; u <= j; ++u) if (c[u] != 1)
            return -1;
        return 2*a[n-1] - a[j+1] - a[i];
    }
    ll solveLarge(const vector<int>& c) {
        int n = (int)c.size();
        if (c[0] != 1 || c[1] != 2 || c[n-2] != 2 || c[n-1] != 1)
            return -1;
        int i = 1;
        while (c[i] == 2)
            ++i;
        int j = n-2;
        while (c[j] == 2)
            --j;
        if (j < i)
            return -1;
        for (int k = i; k <= j; ++k) if (c[k] != 1)
            return -1;
        return 2*a.back() - (a[j+1] - a[i-1]);
    }
    ll solveSmall(const vector<int>& c) {
        int n = (int)c.size();
        int i = 0;
        while (c[i] == 0)
            ++i;
        int j = n-1;
        while (c[j] == 0)
            --j;
        for (int k = i; k <= j; ++k) if (c[k] != 1)
            return -1;
        return a[j] - a[i];
    }
};

void solve(std::istream& in, std::ostream& out)
{
    out << std::setprecision(12);
    Solution solution;
    solution.solve(in, out);
}
#include <fstream>
#include <iostream>

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;

    ostream& out = cout;
    solve(in, out);
    return 0;
}
