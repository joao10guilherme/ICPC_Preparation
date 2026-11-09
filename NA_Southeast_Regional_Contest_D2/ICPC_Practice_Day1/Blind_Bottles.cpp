#include <iostream>
#include <vector>
using namespace std;

int main(){

    int n;
    cin >> n;

    vector<int> list(n);

    for(int i = 0; i < n; i++){
        list[i] = i+1;
    }

    return 0;
}