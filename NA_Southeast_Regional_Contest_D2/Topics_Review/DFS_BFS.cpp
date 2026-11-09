#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// BFS for single connected components ------------------------
vector<int> bfsNormal(vector<vector<int>>& adj){
    int V = adj.size();
    vector<bool> visited(V, false);
    vector<int> res;

    queue<int> q;

    int src = 0;
    visited[src] = true;
    q.push(src);

    while (!q.empty()){
        int curr = q.front();
        q.pop();
        res.push_back(curr);

        // visit all the unvisited neighbours of current node
        for(int x : adj[curr]){
            if(!visited[x]){
                visited[x] = true;
                q.push(x);
            }
        }
    }

    return res;
}

// BFS for all components (handles disconnected graphs) --------------------------
void bfsConnected(vector<vector<int>>& adj, int src,
                  vector<bool>& visited, vector<int>& res){
    
    queue<int> q;
    visited[src] = true;
    q.push(src);

    while(!q.empty()){
        int curr = q.front();
        q.pop();
        res.push_back(curr);

        // visit all the unvisited neighbours of current node
        for(int x : adj[curr]){
            if(!visited[x]){
                visited[x] = true;
                q.push(x);
            }
        }
    }
}

vector<int> bfs(vector<vector<int>>& adj){
    int V = adj.size();
    vector<bool> visited(V, false);
    vector<int> res;

    for(int i = 0; i < V; i++){
        if(!visited[i]){
            bfsConnected(adj, i, visited, res);
        }
    }
    return res;
}

// DFS ------------------------------------------------------
void dfsRec(vector<vector<int>>& adj, vector<bool> &visited,
            int s, vector<int>& res){
    
    visited[s] = true;
    res.push_back(s);

    // Recursively visit all adjacent vertices
    // that are not visited yet
    for(int i : adj[s]){
        if(visited[i] == false)
            dfsRec(adj, visited, 0, res);
    }
}
vector<int> dfs(vector<vector<int>>& adj){
    vector<bool> visited(adj.size(), false);
    vector<int> res;
    dfsRec(adj, visited, 0, res);
    return res;
}

// DFS Disconnected Graph -----------------------------------
// uses the same dfsRec function.
vector<int> dfsDisc(vector<vector<int>>& adj){
    vector<bool> visited(adj.size(), false);
    vector<int> res;
    // Loop through all vertices
    // to handle disconnected graphs
    for(int i = 0; i < adj.size(); i++){
        if(visited[i] == false){
            dfsRec(adj, visited, i, res);
        }
    }
    return res;
}

int main(){


    
    return 0;
}