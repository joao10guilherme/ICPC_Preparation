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

int n;
string s;
vector<vector<int>> adj;
vector<char> stk; // bracket stack for the current path
int top = 0; // current stack size;
long long answer = 0;

char matchOf(char close){
    if(close == ')') return '(';
    if(close == ']') return '[';
    return '{';
}

bool isOpen(char c){ return c == '(' || c == '[' || c == '{'; }

// Walk away form the root; the path so far is root -> ... -> u.
void dfs(int u, int parent){
    char c = s[u];
    bool pushed = false;
    char popped = 0;

    if(isOpen(c)){
        stk[top++] = c;
        pushed = true;
    }else{
        // closing bracket: must match the top of the stack
        if(top == 0 || stk[top - 1] != matchOf(c)) return;
        popped = stk[--top];
    }

    if(top == 0) answer++; // path root -> u is a balanced string

    for(int v : adj[u]){
        if(v != parent) dfs(v, u);
    }

    // undo this node's effect on the stack (backtrack)
    if(pushed) top--;
    else stk[top++] = popped;
}

void solve() {
    
    cin >> n >> s;
    adj.assign(n, {});
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    stk.assign(n + 1, 0);
    for(int root = 0; root < n; root++){
        top = 0; // stack size = 0
        dfs(root, -1);
    }
    
    cout << answer << "\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}