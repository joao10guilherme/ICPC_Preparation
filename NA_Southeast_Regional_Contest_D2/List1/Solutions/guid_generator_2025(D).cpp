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

static int hexval(char ch){
    return (ch >= '0' && ch <= '9') ? ch - '0' : ch - 'a' + 10;
}

void solve() {
    
    int n;
    string label;
    cin >> n >> label;
    vector<int> c(n);

    for(int i = 0; i < n; i++) c[i] = hexval(label[i]);

    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // trie[node][char] = child index, 0 means "no child" (root is index 0 and never a child)
    vector<array<int, 16>> trie;
    trie.reserve((size_t)n * n + 2);    // at most n^2 paths -> at most n^2 new nodes
    trie.push_back({});                 // root

    auto step = [&](int node, int ch) -> int{
        int nxt = trie[node][ch];
        if(nxt == 0){
            nxt = (int)trie.size();
            trie.push_back({});
            trie[node][ch] = nxt;
        }
        return nxt;
    };

    struct Frame{ int u, parent, t; };
    vector<Frame> stk;
    stk.reserve(n + 5);

    for(int s = 0; s < n; s++){
        // path consisting of just s
        stk.push_back({s, -1, step(0, c[s])});
        while(!stk.empty()){
            Frame f = stk.back();
            stk.pop_back();
            for(int v : adj[f.u]){
                if(v == f.parent) continue;
                stk.push_back({v, f.u, step(f.t, c[v])});
            }
        }
    }

    cout << (long long)trie.size() - 1 << "\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}