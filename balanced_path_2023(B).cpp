#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vi vector<int>
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

void solve() {
    
    int n;
    cin >> n;
    
    string chars;
    getline(cin, chars);
    
    vector<vector<char>> adjChar(n);
    vector<vector<char>> par(n);
    for(int i = 0; i < n; i++){
        char u, v;
        cin >> u >> v;
        adjChar[chars[u]].pb(chars[v]);
        par[chars[v]].pb(chars[u]);
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < sz(adjChar[i]); j++){
            cout << i << " : [ " << adjChar[i][j]; 
        }
        cout << endl;
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}
