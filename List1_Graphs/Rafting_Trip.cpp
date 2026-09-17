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

    int R, C;
    cin >> R >> C;

    vector<string> grid(R);

    for(string &row : grid){
        cin >> row;
    }

    // total number of cells
    int N = R * C;

    // gets the ID of the cell (r,c) 
    // -> don't matter what, just need to be unique for every cell
    auto getId = [&](int r, int c){
        return r * C + c;
    };

    // verifies if cell (r,c) is inside the grid
    auto inside = [&](int r, int c){
        return r >= 0 && r < R && c >= 0 && c < C;
    };

    auto isRiver = [&](char ch){
        return ch == '^' ||
               ch == 'v' ||
               ch == '>' ||
               ch == '<';
    };

    // next[u] = next river cell after u
    vector<int> next(N, -1);

    // local[u] = sightseeing spots ajacent to u
    vector<vector<int>> local(N);

    /*
    
        How we can check all neighbors easier

                 (r-1,c)
                    ↑
                    |
          (r,c-1) ← # → (r,c+1)
                    |
                    ↓
                 (r+1,c)

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        for(int d = 0; d < 4; d++){

            adjacent row
            int ar = row + dr[d];
            adjacent col
            int ac = col + dc[d];

            -> check (nr, nc)
        }
    
    */

    // change in row = {UP(-1), DOWN(1), LEFT(0), RIGHT(0)}
    int dr[] = {-1, 1, 0, 0};
    //// change in column = {UP(0), DOWN(0), LEFT(-1), RIGHT(1)}
    int dc[] = {0, 0, -1, 1};

    // ---------------------------
    // Build the graph
    // ---------------------------

    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){

            // verifies if it is a river cell
            if(!isRiver(grid[r][c]))
                continue;

            int u = getId(r,c);

            // next row and col
            int nr = r;
            int nc = c;

            //set next row or col depending on flow of river cell
            if(grid[r][c] == '^') nr--;
            if(grid[r][c] == 'v') nr++;
            if(grid[r][c] == '<') nc--;
            if(grid[r][c] == '>') nc++;

            // checks if next cell is a river cell too
            if(inside(nr, nc) && isRiver(grid[nr][nc])){
                next[u] = getId(nr, nc);
            }

            // find sightseeing spots next to u
            for(int d = 0; d < 4; d++){

                int ar = r + dr[d];
                int ac = c + dc[d];

                if(inside(ar, ac) && grid[ar][ac] == '#'){
                    local[u].push_back(getId(ar, ac));
                }
            }
        }
    }

    // ------------------------------
    // Find cycles
    // ------------------------------

    // state : 0(unvisited), 1(inside DFS), 2(completely processed)
    vector<int> state(N, 0);

    // we have many cicles, so they need their ID too -> as they appear
    vector<int> cycleId(N, -1);
    vector<vector<int>> cycles;

    function<void(int)> findCycle = [&](int u){

        state[u] = 1; // we visited u

        int v = next[u]; // v = next cell from u

        if(v != -1){

            if(state[v] == 0){ // checks if v was visited

                findCycle(v); // if yes, go to the next one
            
            }else if(state[v] == 1){ // if v is currently inside our search
                // we found a cycle

                vector<int> cycle;

                int x = v;

                do{
                    cycle.push_back(x);
                    x = next[x];
                }while(x != v);

                int id = cycles.size();

                for(int node : cycle){
                    cycleId[node] = id;
                }

                cycles.push_back(cycle);

            }

        }

        state[u] = 2;

    };

    // run cycle detection
    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){

            if(!isRiver(grid[r][c])) continue;

            int u = getId(r,c);
            
            if(state[u] == 0) findCycle(u);
        }
    }

    // ----------------------------
    // Reverse graph
    // ----------------------------

    vector<vector<int>> reverseGraph(N);

    for(int u = 0; u < N; u++){

        if(next[u] != -1){
            reverseGraph[next[u]].push_back(u);
        }
    }

    // --------------------------------
    // Sets of sightseeing spots
    // --------------------------------

    vector<unordered_set<int>*> dp(N, nullptr);
    vector<bool> calculated(N, false);

    /*
        solve(u) is only called for NON-CYCLE nodes

        the cycle itself is handled separately
    */

    function<unordered_set<int> *(int)> solve = 
        [&](int u) -> unordered_set<int>* {

            if(calculated[u]) return dp[u];

            calculated[u] = true;

            auto *current = new unordered_set<int>();

            // add sightseeing spots directly adjacent to u.
            for(int spot : local[u]){
                current->insert(spot);
            }

            int v = next[u];

            // if v isn't a cycle node, solve it normally
            if(v != -1 && cycleId[v] == -1){
                
                auto *child = solve(v);

                // small-to-large merging
                if(current->size() < child->size()){
                    swap(current, child);
                }

                for(int spot : *child){
                    current->insert(spot);
                }

                delete child;
            }

            dp[u] = current;

            return current;

        };

    int answer = 0;

    // --------------------------
    // process non-cycle nodes
    // --------------------------

    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){

            if(!isRiver(grid[r][c])) continue;

            int u = getId(r, c);

            if(cycleId[u] == -1){
                
                auto *spots = solve(u);

                answer = max(answer, (int)spots->size());
            }
        }
    }

    // -------------------------------------
    // Process cycles
    // -------------------------------------

    for(const vector<int> &cycle : cycles){

        unordered_set<int> cycleSpots;

        // collect every sightseeing spot nect to
        // every cell in the cycle
        for(int u : cycle){
            for(int spot : local[u]){
                cycleSpots.insert(spot);
            }
        }

        answer = max(answer, (int)cycleSpots.size());

        /*
            a node leading into the cycle has:
                its own spots 
                + spots of the rest of the rest of the graph
                + cycle spots
        */

        for(int cycleNode : cycle){
            for(int u : reverseGraph[cycleNode]){

                if(cycleId[u] != -1) continue;

                auto *spots = solve(u);

                int total = cycleSpots.size();

                for(int spot : *spots){
                    if(!cycleSpots.count(spot)) total++;
                }

                answer = max(answer, total);

            }
        }

    }

    cout << answer << '\n';

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}
