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

const int MAXN = 50005;
const int LOG = 17;

// ----------------
// DSU Structures
//-----------------
// parent_node keeps track of the root of each subset for cycle detection
int parent_node[MAXN];

int find_set(int v){
    if(v == parent_node[v]) return v;
    return parent_node[v] = find_set(parent_node[v]);
}

void union_sets(int a, int b){
    a = find_set(a); 
    b = find_set(b);
    if(a != b){
        parent_node[b] = a;
    }
}

// ---------------------------
// tree and extra edges data
// ---------------------------
vector<int> tree_adj[MAXN];
pair<int, int> extra_edges[2];
int extra_count = 0;

// -----------------------
// LCA Structures
// -----------------------
// tin and tout track entry/exit times to easily check if a node
// is an ancestor of another
int up[MAXN][LOG];
int tin[MAXN], tout[MAXN], timer = 0;

void dfs_lca(int v, int p){
    tin[v] = ++timer;
    up[v][0] = p;
    // binary lifting table population: the 2^i ancestor is the 2^(i-1) ancestor of the 2^(i-1) ancestor
    for(int i = 1; i < LOG; ++i){
        up[v][i] = up[up[v][i-1]][i-1];
    }
    for(int u : tree_adj[v]){
        if(u != p) dfs_lca(u, v);
    }
    tout[v] = ++timer;
}

//check if u is above v in the tree using DFS entry/exit times
bool is_ancestor(int u, int v){
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int get_lca(int u, int v){
    if(is_ancestor(u, v)) return u;
    if(is_ancestor(v, u)) return v;
    for(int i = LOG - 1; i >= 0; --i){
        if(!is_ancestor(up[u][i], v)){
            u = up[u][i];
        }
    }
    return up[u][0];
}

// --------------------
// intersection logic
// --------------------
// checks if two purely ascending paths (u1 up to w1, and u2 up to w2) share any vertices
bool asc_intersect(int u1, int w1, int u2, int w2){
    int L = get_lca(u1, u2);
    return is_ancestor(w1, L) && is_ancestor(w2, L);
}

bool paths_intersect(pair<int, int> p1, pair<int, int> p2){
    int A = p1.first, B = p1.second;
    int C = p2.first, D = p2.second;

    int L1 = get_lca(A, B);
    int L2 = get_lca(C, D);

    if(asc_intersect(A, L1, C, L2)) return true;
    if(asc_intersect(A, L1, D, L2)) return true;

    if(asc_intersect(B, L1, C, L2)) return true;
    if(asc_intersect(B, L1, D, L2)) return true;
    return false;
}

//validates a full candidate path by ensuring all its semented tree-traversal are disjoint
bool is_valid_path(const vector<pair<int, int>>& segments){
    for(size_t i = 0; i < segments.size(); i++){
        for(size_t j = i + 1; j < segments.size(); j++){
            if(paths_intersect(segments[i], segments[j])) return false;
        }
    }
    return true;
}

void solve() {
    
    int n, q;
    cin >> n >> q;

    for(int i = 1; i <= n; i++){
        parent_node[i] = i;
    }

    for(int i = 0; i < n+1; i++){
        int u, v;
        cin >> u >> v;
        if(find_set(u) != find_set(v)){
            union_sets(u, v);
            tree_adj[u].push_back(v);
            tree_adj[v].push_back(u);
        }else{
            extra_edges[extra_count++] = {u, v};
        }
    }

    dfs_lca(1, 1);

    // treating queries
    for(int i = 0; i < q; i++){
        
        int u, v; 
        cin >> u >> v;
        int valid_paths = 0;

        // base case: the single, guaranteed path entirely within the spanning tree
        valid_paths += is_valid_path({{u, v}});

        if(extra_count >= 1){
            int a = extra_edges[0].first;
            int b = extra_edges[0].second;
            // add paths using exactly the 1st extra edge
            valid_paths += is_valid_path({{u, a}, {b, v}});
            valid_paths += is_valid_path({{u, b}, {a, v}});
        }

        if(extra_count == 2){
            int c = extra_edges[1].first, d = extra_edges[1].second;
            int a = extra_edges[0].first, b = extra_edges[0].second;

            // add paths using exactly the 2nd extra value
            valid_paths += is_valid_path({{u, c}, {d, v}});
            valid_paths += is_valid_path({{u, d}, {c, v}});

            // add the 8 permutations usign BOTH extra edges in different orders/directions
            valid_paths += is_valid_path({{u, a}, {b, c}, {d, v}});
            valid_paths += is_valid_path({{u, a}, {b, d}, {c, v}});
            valid_paths += is_valid_path({{u, b}, {a, c}, {d, v}});
            valid_paths += is_valid_path({{u, b}, {a, d}, {c, v}});

            valid_paths += is_valid_path({{u, c}, {d, a}, {b, v}});
            valid_paths += is_valid_path({{u, c}, {d, b}, {a, v}});
            valid_paths += is_valid_path({{u, d}, {c, a}, {b, v}});
            valid_paths += is_valid_path({{u, d}, {c, b}, {a, v}});
        }
        
        cout << valid_paths << endl;
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
