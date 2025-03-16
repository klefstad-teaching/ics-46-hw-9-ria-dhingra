#include "dijkstras.h"
int main() {
    Graph G;
    file_to_graph("src/small.txt", G);

    int src = 0;
    vector<int> previous(G.numVertices, -1);

    vector<int> distances = dijkstra_shortest_path(G, src, previous);

    for(int i = 0; i < G.numVertices; i++) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }

    return 0;
}
