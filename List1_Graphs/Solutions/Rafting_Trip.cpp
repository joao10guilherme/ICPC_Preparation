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

int R, C; // number of rows / cols of the grid;
vector<string> grid; // raw grid chars

vector<int> segLeft, segRight, segCnt;

int newNode(int l, int r, int c){
    segLeft.push_back(l);
    segRight.push_back(r);
    segCnt.push_back(c);
    return (int)segLeft.size() - 1;
}

int totalSpots = 0;

// update(node, lo, hi, pos)
//   "node" is the version (root index) of the segment tree BEFORE the insertion,
//   restricted to the range [lo, hi]. We want to set position "pos" to 1 and return the
//   index of the (possibly brand new) node representing the range [lo, hi] AFTER the
//   insertion.
//
//   If "pos" was already 1 we change nothing and simply return the very same node index
//   we were given -- this is what keeps duplicate spots from being counted twice, and it
//   is also what saves us from creating new nodes when nothing actually changed.
int update(int node, int lo, int hi, int pos){
    if(lo == hi){
        // we reached the single leaf that represents "pos"
        if(segCnt[node] == 1) return node; // already present -> nothing to do
        return newNode(0,0,1);             // brand new leaf holding a single 1
    }

    int mid = (lo + hi) / 2;
    if(pos <= mid){
        int newLeft = update(segLeft[node], lo, mid, pos);
        if(newLeft == segLeft[node]) return node; // nothing changed below us
        int rightChild = segRight[node];
        return newNode(newLeft, rightChild, segCnt[newLeft] + segCnt[rightChild]);
    }else{
        int newRight = update(segRight[node], mid+1, hi, pos);
        if(newRight == segRight[node]) return node; // nothing changed below us
        int leftChild = segLeft[node];
        return newNode(leftChild, newRight, segCnt[leftChild] + segCnt[newRight]);
    }
}

inline int insertSpot(int ver, int s){
    if(totalSpots == 0) return ver;
    return update(ver, 0, totalSpots - 1, s);
}

void solve() {

    // ------------------------
    // Step 1: Read the grid
    // ------------------------

    cin >> R >> C;
    grid.resize(R);
    for(int i = 0; i < R; i++){
        cin >> grid[i];
    }

    int N = R * C; // total number of cells, each cell gets a single int id = row * C + col

    // -------------------------------------------------------------------------------
    // Step 2: give every sightseeing spot ('#') its own small integer id (0,1,2,...)
    //         this is the coordinate system the persistent segment tree will use.
    // -------------------------------------------------------------------------------

    vector<int> spotId(N, -1);
    int spotCount = 0;

    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            if(grid[i][j] == '#'){
                spotId[i * C + j] = spotCount++;
            }
        }
    }
    totalSpots = spotCount;

    // node 0 of the segment tree = the permanent "empty version" (empty set of spots)
    newNode(0,0,0);
    const int EMPTY_VERSION = 0;

    // ---------------------------------------------------------------------------
    // STEP 3: for every RIVER cell, figure out
    //           (a) isRiver[cell]      -- is this a river cell at all?
    //           (b) nxt[cell]          -- the single next cell the raft goes to,
    //                                      or -1 if the raft leaves the river here
    //                                      (steps onto land, or exits the grid)
    //           (c) spotsOf[cell]      -- list of spot-ids that are adjacent to this
    //                                      river cell (up to 4 of them)
    // ---------------------------------------------------------------------------

    vector<bool> isRiver(N, false);
    vector<int> nxt(N, -1);
    vector<vector<int>> spotsOf(N);

    auto inBounds = [&](int r, int c){
        return r >= 0 && r < R && c >= 0 && c < C;
    };

    auto isRiverChar = [&](char ch){
        return ch == '^' ||
               ch == 'v' ||
               ch == '<' ||
               ch == '>';
    };

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

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){

            char ch = grid[i][j];

            if(!isRiverChar(ch)) continue;

            int idx = i * C + j;
            isRiver[idx] = true;

            // work out where arrow is pointing to
            int ni = i, nj = j;
            if(ch == '^') ni = i - 1;
            else if(ch == 'v') ni = i + 1;
            else if(ch == '<') nj = j - 1;
            else if(ch == '>') nj = j + 1;

            if(inBounds(ni, nj) && isRiverChar(grid[ni][nj])){
                nxt[idx] = ni * C + nj; // raft keeps floating on the river
            }else{
                nxt[idx] = -1; // raft steps onto land, or leaves the grid
            }

            // collect adjacent sightseeing spots (up to 4 neighbours: N,S,W,E)
            for(int d = 0; d < 4; d++){
                // ai (adjacent row), aj (adjacent col)
                int ai = i + dr[d], aj = j + dc[d];
                if(inBounds(ai, aj) && grid[ai][aj] == '#'){
                    spotsOf[idx].push_back(spotId[ai * C + aj]);
                }
            }
        }
    }

    // ---------------------------------------------------------------------------
    // STEP 4: find every CYCLE among the river cells.
    //
    // This is the classic "functional graph" cycle-finding trick:
    //   state[x] = 0  -> haven't looked at x yet
    //   state[x] = 1  -> x is on the path we are CURRENTLY walking (still "open")
    //   state[x] = 2  -> we are completely done with x (already resolved)
    //
    // We repeatedly pick an unvisited river cell and walk forward (state 0 -> 1),
    // recording the path we take. We stop walking as soon as we
    //   - fall off the river (nxt == -1), or
    //   - land on a cell that is already state 1 (this closes a brand new cycle!), or
    //   - land on a cell that is already state 2 (this path merges into already
    //     processed territory, no new cycle here).
    // Every river cell is pushed onto a "current path" list at most once overall, so
    // this whole step only takes O(number of river cells) time in total.
    // ---------------------------------------------------------------------------

    vector<int> state(N, 0);
    vector<bool> inCycle(N, false);
    vector<int> posInPath(N, -1);
    vector<int> path; // reused scratch buffer

    for(int start = 0; start < N; start++){
        if(!isRiver[start] || state[start] != 0) continue;

        path.clear();
        int cur = start;
        while(cur != -1 && state[cur] == 0){
            state[cur] = 1;
            posInPath[cur] = (int)path.size();
            path.push_back(cur);
            cur = nxt[cur];
        }

        if(cur != -1 && state[cur] == 1){
            // We looped back onto a cell that is still "open" -> found cycle
            // Everything in path[] from that cell's position to the end is the cycle
            int idx = posInPath[cur];
            for(int k = idx; k < (int)path.size(); k++) inCycle[path[k]] = true;
        }

        // whether or not we found a cycle, every cell we just walked through is
        // now fully resolved as far as cycle-finding is concerned
        for(int node : path) state[node] = 2;
    }

    // ---------------------------------------------------------------------------
    // STEP 5: build a "reverse" adjacency list.
    //   revAdj[u] = every river cell v such that nxt[v] == u
    // In other words: "who flows INTO u?" We need this to walk backwards later,
    // propagating an already-known answer at u out to all the cells that lead into u.
    // ---------------------------------------------------------------------------

    vector<vector<int>> revAdj(N);

    for(int v = 0; v < N; v++){
        if(isRiver[v] && nxt[v] != -1) revAdj[nxt[v]].push_back(v);
    }

    // ver[v]      = index of the persistent-segment-tree version representing the set
    //               of distinct sightseeing spots visible on the trip that starts at v.
    // resolved[v] = have we already computed ver[v]?
    vector<int>  ver(N, -1);
    vector<char> resolved(N, false);
    queue<int> bfsQueue;

    // ---------------------------------------------------------------------------
    // STEP 6: resolve every CYCLE first.
    //
    // No matter which cell of a cycle you start on, a trip starting anywhere inside
    // that cycle visits ALL the cells of that cycle exactly once before it repeats the
    // starting cell and stops. So every cell in a given cycle shares the exact same
    // "visible spots" set -- the union of the spots next to every cell in the cycle.
    // We build that one shared version and hand it out to every node in the cycle.
    // ---------------------------------------------------------------------------

    vector<char> grouped(N, false);
    
    for(int i = 0; i < N; i++){
        if(!isRiver[i] || !inCycle[i] || grouped[i]) continue;

        // walk around this cycle once, collecting all of its members
        vector<int> cyc;
        int cur = i;
        do{
            cyc.push_back(cur);
            grouped[cur] = true;
            cur = nxt[cur];
        }while(cur != i);

        // insert every spot adjacent to every cell of the cycle into one shared version
        int version = EMPTY_VERSION;
        for(int node : cyc){
            for(int s : spotsOf[node]){
                version = insertSpot(version, s);
            }
        }

        // hand that same version to every cell in the cycle, and seed the BFS with them
        for(int node : cyc){
            ver[node] = version;
            resolved[node] = true;
            bfsQueue.push(node);
        }
    }

    // ---------------------------------------------------------------------------
    // STEP 7: resolve every "dead end" (a river cell whose raft immediately leaves
    //          the river, i.e. nxt[v] == -1). Its visible-spots set is simply its own
    //          adjacent spots (nothing further downstream to add, because there IS no
    //          further downstream).
    // ---------------------------------------------------------------------------

    for(int v = 0; v < N; v++){
        if(isRiver[v] && nxt[v] == -1 && !resolved[v]){
            int version = EMPTY_VERSION;
            for(int s : spotsOf[v]) version = insertSpot(version, s);
            ver[v] = version;
            resolved[v] = true;
            bfsQueue.push(v);
        }
    }

    // ---------------------------------------------------------------------------
    // STEP 8: propagate answers backwards with a breadth-first search.
    //
    // We already know ver[u] for every "resolved" cell u (cycles + dead ends). Any
    // river cell v with nxt[v] == u can now be resolved too:
    //     ver[v] = ver[u] PLUS v's own adjacent spots (duplicates automatically
    //              ignored by the persistent segment tree's update() function).
    // Once v is resolved we push it into the queue as well, so that whatever flows
    // into v gets resolved next, and so on, layer by layer, until every river cell
    // has an answer. This never revisits the same cell twice, so it runs in time
    // proportional to the number of river cells (times the small cost of a handful
    // of segment-tree insertions per cell).
    // ---------------------------------------------------------------------------

    while(!bfsQueue.empty()){
        int u = bfsQueue.front();
        bfsQueue.pop();
        for(int v : revAdj[u]){
            if(resolved[v]) continue; // shouldn't normally happen, but guard anyway
            int version = ver[u];
            for(int s : spotsOf[v]) version = insertSpot(version, s);
            ver[v] = version;
            resolved[v] = true;
            bfsQueue.push(v);
        }
    }

    // ---------------------------------------------------------------------------
    // STEP 9: the answer is simply the largest "set size" (segCnt at the root of the
    //          version) among all possible starting river cells.
    // ---------------------------------------------------------------------------

    int answer = 0;
    for(int v = 0; v < N; v++){
        if(isRiver[v]){
            answer = max(answer, segCnt[ver[v]]);
        }
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