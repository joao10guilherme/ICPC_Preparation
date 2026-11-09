#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int main(){

    int ds, ys, dm, ym;
    cin >> ds >> ys;
    cin >> dm >> ym;

    int result = (ys-ds)*(ym-dm);
    cout << result;
    return 0;
}