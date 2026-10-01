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

// Idea: number the cities in DFS preorder, visiting children smallest label first.
// Routing a person to d forces closing every smaller sibling along the path,
// which cuts off exactly the cities that come before d in preorder (except d's ancestors).
// So person i succeeds iff no earlier destination lies to the right of d_i's subtree:
//     max(tin[d_j], j < i) <= tout[d_i]

void solve(){
    int N, M;
    cin >> N >> M;

    vector<vi> adj(N + 1);
    vi par(N + 1, 0);
    rep(i,0,N-1){
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        par[b] = a;
    }
    // people always pick the smallest label first
    rep(u,1,N+1) sort(all(adj[u]));

    // iterative preorder DFS (no recursion -> no stack overflow on a chain)
    vi tin(N + 1);
    int timer = 0;
    vi st = {1};
    while (!st.empty()){
        int u = st.back(); st.pop_back();
        tin[u] = timer++;
        // push in reverse so the smallest child is popped first
        per(i,0,sz(adj[u])) st.pb(adj[u][i]);
    }

    // subtree sizes: roads go from lower to higher label,
    // so every child has a bigger label than its parent
    vi subSize(N + 1, 1);
    per(u,2,N+1) subSize[par[u]] += subSize[u];

    // tout[u] = last preorder index inside u's subtree
    vi tout(N + 1);
    rep(u,1,N+1) tout[u] = tin[u] + subSize[u] - 1;

    int ans = 0;
    int mx = -1; // rightmost preorder index reached so far
    rep(i,0,M){
        int d;
        cin >> d;
        if (mx > tout[d]) break; // a road on d's path was already closed
        mx = max(mx, tin[d]);
        ans++;
    }

    cout << ans << '\n';
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
