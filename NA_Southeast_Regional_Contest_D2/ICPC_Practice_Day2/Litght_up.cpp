#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){

    int n;
    cin >> n;

    vector<string> grid(n);

    // Read the grid
    for(int i = 0; i < n; i++){
        cin >> grid[i];
    }

    // Matrix to track illuminated cells
    vector<vector<bool>> lit(n, vector<bool>(n, false));

    // Directions: up, down, left, right
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    bool valid = true;

    // 1: process every light bulb
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){

            if(grid[i][j] == '?'){
                
                // exploring 4 directs
                for(int d = 0; d < 4; d++){

                    int x = i + dx[d];
                    int y = j + dy[d];

                    while(x >= 0 && x < n && y >= 0 && y < n){

                        // another bulb -> invalid
                        if(grid[x][y] == '?'){
                            valid = false;
                        }

                        // empty cell is lighten
                        if(grid[x][y] == '.'){
                            lit[x][y] = true;
                        }else{
                            break; // empty cell stops the light
                        }

                        // move next cell
                        x += dx[d];
                        y += dx[d];
                    }
                }

            }
        }
    }

    // 2: check if every empty cell is illuminated
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == '.' && !lit[i][j]){
                valid = false;
            }
        }
    }

    // 3: check numbered cells
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){

            if(grid[i][j] >= '0' && grid[i][j] <= '4'){
                
                int required = grid[i][j] - '0';
                int count = 0;

                for(int d = 0; d < 4; d++){
                    
                    int x = i + dx[d];
                    int y = j + dy[d];

                    // position is inside grid
                    if(x >= 0 && x < n && y >= 0 && y <= n){
                        if(grid[x][y] == '?'){
                            count++;
                        }
                    }
                }

                if(count != required){
                    valid = false;
                }
            }
        }
    }

    cout << (valid ? 1 : 0) << endl;

    return 0;
}