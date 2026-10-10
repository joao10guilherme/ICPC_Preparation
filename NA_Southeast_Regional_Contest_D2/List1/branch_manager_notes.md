# Branch Manager — 2022 ICPC Southeast USA D2, Problem L

**Limits:** 2 ≤ n, m ≤ 2·10⁵, time limit 4 s
**Solution:** `branch_manager.cpp` — O(n log n + m)

## Problem in short

- n cities, n − 1 one-way roads `a → b` with `a < b`, forming a rooted tree with root 1.
- m people, in order, each start at city 1 with a destination `d`.
- At every city a person takes the road to the **smallest-labeled** open child. They stop at `d`, or fail at a dead end.
- Before each person you may **permanently** close any roads.
- As soon as one person fails, everyone after them leaves.
- **Output:** the maximum number of people routed correctly.

## Key observations

### 1. Only close roads you're forced to

To reach `d`, at each city on the path you **must** close the roads to children smaller than the next city on the path. Closing anything else never helps anyone, so the closures are fully determined.

### 2. The closures cut off everything "to the left" of `d`

Draw the tree with children sorted smallest → largest, left → right. People move through it left to right.
Routing someone to `d` closes every subtree to the left of `d`'s path.

Number the cities in **DFS preorder** (smallest child first):

- `tin[c]` = position of city c in the visit order ("time in")
- `tout[c]` = last position inside c's subtree = `tin[c] + subSize[c] − 1`
- c's subtree occupies exactly the positions `[tin[c], tout[c]]`

After routing someone to `d`, every city with `tin < tin[d]` is unreachable, **except** `d`'s ancestors (they're on the path).

### 3. Only the rightmost destination so far matters

Let `mx` = max `tin` of all earlier destinations. Person `i` going to `d` succeeds iff

```
mx <= tout[d]
```

- `mx` inside `[tin[d], tout[d]]` → an earlier person went **below** d; the path to d is still open. ✓
- `mx < tin[d]` → everyone before went **left** of d; nothing on d's path was closed. ✓
- `mx > tout[d]` → someone went **right** of d's subtree, which closed a road on d's path. ✗

## Sample 1

```
            1 (0)                    cities with (tin)
          /       \
      2 (1)        4 (4)
      /   \       /  |  \
  3 (2)  5 (3)  6(5) 7(6) 8(7)
```

     | City | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
    |---|---|---|---|---|---|---|---|---|---|
    | `tin` | 0 | 1 | 2 | 4 | 3 | 5 | 6 | 7 |
| `subSize` | 8 | 3 | 1 | 4 | 1 | 1 | 1 | 1 |
   | `tout` | 7 | 3 | 2 | 7 | 3 | 5 | 6 | 7 |

Destinations: 5, 2, 6, 4, 8 (`mx` starts at −1)

| Person | d | `tout[d]` | `mx > tout[d]`? | new `mx` | ans |
|---|---|---|---|---|---|
| 1 | 5 | 3 | −1 > 3 no | 3 | 1 |
| 2 | 2 | 3 | 3 > 3 no | 3 | 2 |
| 3 | 6 | 5 | 3 > 5 no | 5 | 3 |
| 4 | 4 | 7 | 5 > 7 no | 5 | 4 |
| 5 | 8 | 7 | 5 > 7 no | 7 | 5 |

**Answer: 5.** What really happens:

| # | Goal | Roads closed before them | Path |
|---|---|---|---|
| 1 | 5 | 2→3 | 1 → 2 → 5 |
| 2 | 2 | — | 1 → 2 (stops at destination) |
| 3 | 6 | 1→2 | 1 → 4 → 6 |
| 4 | 4 | — | 1 → 4 |
| 5 | 8 | 4→6, 4→7 | 1 → 4 → 8 |

Person 2 is the tight case: `mx = 3 = tout[2]` because city 5 is inside city 2's subtree — that's why the check is `>`, not `>=`.

## Sample 2

Tree `1 → {2, 3, 4}`, destinations 3, 2, 3, 4. Preorder: 1(0) 2(1) 3(2) 4(3).

- Person 1 → 3: ok, must close 1→2. `mx = 2`.
- Person 2 → 2: `tout[2] = 1`, `2 > 1` → fails. Line stops.

**Answer: 1.**

## Code walkthrough

```cpp
// 1. read the tree: n - 1 edges (a tree with n nodes has exactly n - 1 edges)
rep(i,0,N-1){ cin >> a >> b; adj[a].pb(b); par[b] = a; }

// 2. people pick the smallest label -> DFS must visit children in ascending order
rep(u,1,N+1) sort(all(adj[u]));

// 3. iterative preorder DFS; push children in REVERSE so the smallest is popped first
vi st = {1};
while (!st.empty()){
    int u = st.back(); st.pop_back();
    tin[u] = timer++;
    per(i,0,sz(adj[u])) st.pb(adj[u][i]);
}

// 4. subtree sizes without a second DFS: children have bigger labels than parents,
//    so counting u down from N finishes every child before its parent
per(u,2,N+1) subSize[par[u]] += subSize[u];
rep(u,1,N+1) tout[u] = tin[u] + subSize[u] - 1;

// 5. answer
int ans = 0, mx = -1;
rep(i,0,M){
    cin >> d;
    if (mx > tout[d]) break;
    mx = max(mx, tin[d]);
    ans++;
}
```

## Pitfalls

- **Read n − 1 edges, not n.** Reading n would swallow the first destination as a road.
- **Sort the child lists.** Without it, preorder doesn't match the order people choose roads.
- **`per`, not `rep`, when pushing to the stack.** A stack is last-in-first-out; pushing in reverse makes the smallest child come out first.
- **Iterative DFS.** A chain of 2·10⁵ cities would overflow the call stack with recursion.
- **Don't store destinations in a queue and search it.** That's O(m) per lookup; the solution never needs it.
- **Don't delete from `adj[u]` while iterating over it** — undefined behavior. Here nothing needs deleting at all.

## Reusable techniques

- **Euler tour / preorder numbering:** `tin`/`tout` turn "is x in c's subtree?" into `tin[c] <= tin[x] <= tout[c]`.
- **Subtree sizes by label order** when every edge goes from a smaller to a larger label.
- **Iterative DFS with an explicit stack** for deep trees.
