#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){

    int r, c, v, h;
    cin >> r >> c >> v >> h;

    vector<int> height(v), width(h);

    for(int i = 0; i < v; i++){
        cin >> height[i];
    }
    for(int i = 0; i < h; i++){
        cin >> width[i];
    }
    vector<string> board(r, string(c, ' '));

    int row = 0;

    for(int i = 0; i < v; i++){

        int col = 0;

        for(int j = 0; j < h; j++){
            
            char color;

            if((i+j) % 2 == 0){
                color = 'B';
            }else{
                color = 'W';
            }

            for(int y = row; y < row + height[i]; y++){
                for(int x = col; x < col + width[j]; x++){
                    board[y][x] = color;
                }
            }

            col += width[j];

        }

        row += height[i];
    }

    for(int i = 0; i < r; i++){
        cout << board[i] << '\n';
    }

    return 0;
}