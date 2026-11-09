#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int main(){

    int n;
    double x1, y1, x2, y2;

    cin >> n;

    vector<double> y_int;

    int count = 0;
    do{
        cin >> x1 >> y1 >> x2 >> y2;
        double m = (double)(y2 - y1)/(x2 - x1);
        double b = (double)y1 - m*x1;
        // cout << b << "y-intercept\n"; 
        y_int.push_back(b);
        count++;
    } while(count < n);

    sort(y_int.begin(), y_int.end());

    if(y_int[0] < 0){
        cout << -1.0;
    }else{
        cout << y_int[0];
    }

    return 0;
}