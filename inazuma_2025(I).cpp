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

    int N; // # of cubes
    int M; // # of directed relations
    int K; // # of petals per cube

    cin >> N >> M >> K;

    /*

    1st - Identify which boxe's chains form a tree
          and which is the solitary box.
    2nd - 

    count = 4 + 

            1(8)
           /
          2(9)           5(6) + 4 = 5(10)
         / \
      3(6)  4(9)

       
    */

    vi boxes_litPetals(N + 1);
    vector<vi> boxes_connections(N + 1);
    vector<vi> par(N + 1);

    rep(i, 1, N+1){
        int n;
        cin >> n;
        boxes_litPetals.pb(n);
    }

    rep(i, 1, M + 1){
        int a, b;
        cin >> a >> b;
        boxes_connections[a].pb(b);
        par[b].pb(a);
    }

    // identify root of the tree
    int root = 0;
    rep(i, 1, N+1){
        if(par[i].empty()){
            root = i;
            break;
        }
    }

    // dfs to verify connectivity between all members
    vector<bool> visited(N + 1, false);

    function<void(int)> dfs = [&](int u){
        visited[u] = true;

        for(int v : boxes_connections[u]){
            if(!visited[v]){
                dfs(v);
            }
        }
    };

    dfs(root);

    for(bool i : visited){
        cout << i << " " << visited[i];
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
