#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){

    int n, m, s;
    cin >> n >> m;

    int ans = -1;

    vector<string> arrivals(n);
    vector<string> departures(m);
    vector<int> hours_arr(n), minutes_arr(n), seconds_arr(n);
    vector<int> hours_dep(m), minutes_dep(m), seconds_dep(m);

    // pre-processing
    for(int i = 0; i < n; i++){
        string time;
        cin >> time;
        arrivals[i] = time;
    }
    for(int i = 0; i < m; i++){
        string time;
        cin >> time;
        departures[i] = time;
    }

    cin >> s;

    // getting arrivals and departures times
    for(int i = 0; i < n; i++){
        hours_arr[i] = stoi(arrivals[i].substr(0,2));
        minutes_arr[i] = stoi(arrivals[i].substr(3,2));
        seconds_arr[i] = stoi(arrivals[i].substr(6,2));
    }
    for(int i = 0; i < m; i++){
        hours_dep[i] = stoi(departures[i].substr(0,2));
        minutes_dep[i] = stoi(departures[i].substr(3, 2));
        seconds_dep[i] = stoi(departures[i].substr(6, 2));
    }

    vector<int> arrival_total(n);
    vector<int> departure_total(m);

    for(int i = 0; i < n; i++){
        arrival_total[i] = hours_arr[i] * 3600 + minutes_arr[i] * 60 + seconds_arr[i];
    }
    for(int i = 0; i < m; i++){
        departure_total[i] = hours_dep[i] * 3600 + minutes_dep[i] * 60 + seconds_dep[i];
    }

    for(int i = 0; i < n && i < m; i++){
        int diff = departure_total[i] - arrival_total[i];
        if(diff == s)
            ans = s;
    }

    cout << ans;

    return 0;
}