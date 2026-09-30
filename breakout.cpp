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

void solve(){

    // input constants
    int N, X, M;
    cin >> N >> X >> M;

    // populate boxes vector -> based on M queries
    vi boxes(N + 1, 0);
    rep(i,1,M+1){
        int box;
        cin >> box;
        boxes[box]++;
    }

    // clw traversal
    int clw_count = 0;
    rep(i,1,X){
        if(boxes[i] !=0)
            clw_count+=boxes[i];
    }

    // ccw traversal
    int ccw_count = 0;
    rep(i,X,N+1){
        if(boxes[i]!=0)
            ccw_count+=boxes[i];
    }

    cout << min(clw_count, ccw_count) << endl;

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}