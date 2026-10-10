#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){

    int r, c;
    cin >> r >> c;

    vector<string> grid(r);

    for(int i = 0; i < r; i++){
        string str;
        cin >> str;
        grid.push_back(str);
    }

    string answer = "";

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if(grid[i][j] != '.'){
                answer += grid[i][j];
            }
        }
    }

    cout << answer << endl;

    return 0;
}