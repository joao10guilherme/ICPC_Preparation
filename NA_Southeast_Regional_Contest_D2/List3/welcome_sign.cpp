#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){

    int r, c;
    cin >> r >> c;
    string s;
    vector<string> result(r);
    vector<string> message;

    for(int i = 1; i <= r; i++){
        cin >> s;

        if(s.size() == c){
            result[i] = s;
            continue;
        }

        if(s.size() < c){
            int spaces = c - s.size();

            if(i % 2 != 0){
                string displayed_mesage = "";
                if(spaces % 2 == 0){
                    int left, right = spaces / 2;
                    for(int i = 0; i <= left; i++) {
                        displayed_mesage += ".";
                    }
                    displayed_mesage += s;
                    for(int i = 0; i < right; i++) {
                        displayed_mesage += ".";
                    }
                }
                result[i]= displayed_mesage;
                
            }else if(i % 2 == 0){
                string displayed_mesage = "";
                if(spaces % 2 == 0){
                    int left, right = spaces / 2;
                    for(int i = 0; i < left; i++) {
                        displayed_mesage += ".";
                    }
                    displayed_mesage += s;
                    for(int i = 0; i <= right; i++) {
                        displayed_mesage += ".";
                    }
                }
                result[i]= displayed_mesage;
            }
        }
    }

    for(int i = 0; i < r; i++){
        cout << result[i] << endl;
    }

    return 0;
}