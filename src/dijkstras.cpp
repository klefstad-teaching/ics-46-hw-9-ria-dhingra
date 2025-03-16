#include "dijkstras.h"
#include <queue>
#include <algorithm>
using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);

    distances[source] = 0;
    previous[source] = -1;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});

    while(!minHeap.empty()) {
        int u = minHeap.top().first;
        minHeap.pop();
        if(visited[u]) continue;
        visited[u] = true;
        for(Edge edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if(!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    int curr = destination;

    while(curr != -1) {
        path.push_back(curr);
        curr = previous[curr];
    }

    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    if (total == INF) {
        cout << "No path found." << endl;
        return;
    }

    // cout << "Shortest path: " << endl;
    for(size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if(i != v.size() - 1) {
            cout << " ";
        }
    }
    
    cout << endl;
    cout << "Total cost is " << total << endl;
}