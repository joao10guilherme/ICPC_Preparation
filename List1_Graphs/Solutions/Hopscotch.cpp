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
    
    int n, k;
    cin >> n >> k;

    // positions[x] = all cells containing value x
    vector<vector<pair<int, int>>> positions(k + 1);

    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++){
            int x;
            cin >> x;
            positions[x].push_back({r,c});
        }
    }

    // dp[r][c] = minimum cost to reach cell (r,c)
    vector<vector<int>> dp(n, vector<int>(n, INF));

    // Every 1 can be our starting point
    for(auto [r,c] : positions[1]){
        dp[r][c] = 0;
    }

    // Process 2, 3, ... , k
    for(int x = 2; x <= k; x++){

        vector<vector<int>> new_dp(n, vector<int>(n, INF));

        // Try reaching every cell containing x
        for(auto [r,c] : positions[x]){

            for(auto [pr, pc] : positions[x-1]){

                if(dp[pr][pc] == INF){
                    continue;
                }

                int distance = abs(r - pr) + abs(c - pc);

                new_dp[r][c] = min(
                    new_dp[r][c],
                    dp[pr][pc] + distance
                );

            }

        }

        dp = new_dp;

    }

    int answer = INF;

    for(auto [r,c] : positions[k]){
        answer = min(answer, dp[r][c]);
    }

    if(answer == INF){
        cout << -1 << '\n';
    }else{
        cout << answer << '\n';
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