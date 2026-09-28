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

void solve(){

    // input constants
    int N, X, M;
    cin >> N >> X >> M;

    // populate rooms vector
    vector<int> rooms(N + 1);
    for(int i = 1; i <= N; i++){
        rooms[i] = i;
    }

    // populate boxes vector -> based on M queries
    vector<bool> boxes(N + 1, false);
    for(int i = 1; i <= M; i++){
        int box;
        cin >> box;
        boxes[box] = true;
    }

    // clw traversal
    int clw_count = 0;
    for(int i = 1; i <= X; i++){
        if(boxes[i] == true)
            clw_count++;
    }

    // ccw traversal
    int ccw_count = 0;
    for(int i = N; i >= X; i--){
        if(boxes[i] == true)
            ccw_count++;
    }

    cout << "Output: " << min(clw_count, ccw_count) << endl;

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}