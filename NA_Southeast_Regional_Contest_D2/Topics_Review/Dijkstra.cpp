#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> P;

vector<int> dijkstra(vector<vector<P>>& adjList, int src){
    int n = adjList.size();
    vector<bool> isVisited(n, false);
    vector<int> minDistance(n, INT_MAX);
    minDistance[src] = 0;
    priority_queue<P, vector<P>, greater<P>> minHeap;
    minHeap.push({0, src});
    while(!minHeap.empty()){
        auto [currDistance, node] = minHeap.top();
        minHeap.pop();
        isVisited[node] = true;
        for(auto& [neighbor, edgeWeight] : adjList[node]){
            int newDistance = currDistance + edgeWeight;
            if(!isVisited[neighbor] && minDistance[neighbor] > newDistance){
                minDistance[neighbor] = newDistance;
                minHeap.push({newDistance, neighbor});
            }
        }
    }
    return minDistance;
}