#include <iostream>
#include <vector>
using namespace std;

int main(){

    int a, b;
    cin >> a >> b;

    int ans = 0;

    while(a != b){
        if(a < b){
            a++;
        }else if((a % 2) == 0){
            a = a/2;
        }else{
            a++;
        }

        ans++;
    }

    cout << ans << '\n';

    return 0;
}