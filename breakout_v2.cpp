// Problem: Breakout (SER D2 2025, F)
// Idea: count boxes clockwise vs counterclockwise from X, take the min
// Complexity: O(N + M)
// Space: O(1)
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vi vector<int>
#define vb vector<bool>
#define vl vector<ll>
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define per(i,a,b) for(int i=(b)-1;i>=(a);i--)
#define pb push_back
#define F first
#define S second

const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

void solve(){
    int N, X, M;
    cin >> N >> X >> M;

    int clw_count = 0;
    int ccw_count = 0;

    // Process queries on-the-fly without storing a large vector
    rep(i, 0, M) {
        int box;
        cin >> box;
        if (box < X) {
            clw_count++;
        } else {
            ccw_count++;
        }
    }

    cout << min(clw_count, ccw_count) << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}