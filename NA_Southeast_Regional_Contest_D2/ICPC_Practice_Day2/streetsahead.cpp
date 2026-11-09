#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main(){

    int n,q;
    cin >> n >> q;
    unordered_map<string, int> map;
    string s;
    vector<int> answers(q);
    for (int i = 0;i < n; i++) {
        cin >> s;
        map[s] = i+1;
        
    }
    for (int i = 0;i < q; i++) {
        string start, end;
        cin >> start >> end;
        int result = abs(map[end] - map[start]);
        if (result < 2) {
            answers.push_back(0);
        }
        else {
            cout << "got here";
            answers.push_back(result);
        }

    }
    for (int i = 0; i < q; i++) {
        cout << answers[i] << "\n";
    }
    return 0;
}