#include<iostream>
#include <bits/stdc++.h>
using namespace std;


int main() {
    // input
    int size;
    cin >> size;
    int current_rating;
    int problems_excluded = 0;
    // Check which elements are odd and add to output(problems_excluded)
    for(int i = 0; i < size; i++) {
        cin >> current_rating;
        if(current_rating % 2 != 0) { // odd rating
            problems_excluded++;
        }
    }

    
    cout << problems_excluded;
    return 0;
}