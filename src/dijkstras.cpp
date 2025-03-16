#include "dijkstras.h"
#include <queue>
#include <algorithm>
using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);

    previous[source] = -1;
    distances[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});

    while(!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();

        if(visited[u]) continue;
        visited[u] = true;
        for(const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if(!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if(distances[destination] == INF) {
        return path;
    }

    for(int i = destination; i != -1; i = previous[i]) {
        path.insert(path.begin(), i);
    }

    return path;
}

void print_path(const vector<int>& v, int total) {
    if (total == INF) {
        cout << "No path found.";
        return;
    }

    for(size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        cout << " ";
    }
        cout << "\nTotal cost is " << total << endl;
}