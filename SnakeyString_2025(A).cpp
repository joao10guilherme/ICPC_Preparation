#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){

    int r, c;
    cin >> r >> c;

    vector<string> grid(r);
    for(int i = 0; i < r; i++){
        string row;
        cin >> row;
        grid[i] = row;
    }

    for(int j = 0; j < c; j++){
        for(int i = 0; i < r; i++){
            if(grid[i][j] != '.'){
                cout << grid[i][j];
            }
        }
    }cout << endl;

    return 0;
}