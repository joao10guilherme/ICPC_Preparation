#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    int freq[51] = {0};
    vector<int> ans;

    for(int i = 0; i < 10*n; i++){
        
        int a,b,c,d,e;
        cin >> a >> b >> c >> d >> e;
        freq[a]++;
        freq[b]++;
        freq[c]++;
        freq[d]++;
        freq[e]++;

    }

    for(int i = 1; i <= 50; i++){
        if(freq[i] > (20/(10*n))){
            ans.push_back(i);
        }
    }

    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " ";
    }cout << "\n";

    return 0;
}