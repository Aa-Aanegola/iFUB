#include <bits/stdc++.h>
#include <omp.h>
#include "graph.hpp"

using namespace std;
using namespace std::chrono;

pair<long long, long long> naive_diameter_parallel(Graph &G, long long k)
{

    long long diameter = 0, bfs_count = 0;

    cout << "Running on " << omp_get_max_threads() << " threads\n";

#pragma omp parallel for num_threads(omp_get_max_threads()) shared(G, diameter, bfs_count)
    for (int i = 1; i <= G.get_num_nodes(); i++)
    {
        bfs_count++;
        diameter = max(diameter, G.get_ecc(i));
    }
    return make_pair(diameter, bfs_count);
}

pair<long long, long long> naive_diameter(Graph &G, long long k)
{
    long long diameter = 0, bfs_count = 0;

    for (int i = 1; i <= G.get_num_nodes(); i++)
    {
        bfs_count++;
        diameter = max(diameter, G.bfs(i));
    }
    cout << "\n";
    return make_pair(diameter, bfs_count);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;

    Graph graph(argv[1]);

    cout << "number of nodes: " << graph.get_num_nodes() << " number of edges: " << graph.get_num_edges() / 2 << "\n";
    cout << "Running Serial Naive Diameter\n";
    auto start = high_resolution_clock::now();
    auto res = naive_diameter(graph, 0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Serial Naive Diameter Time taken: " << duration.count() << "ms. Got value: " << res.first << '\n';

    cout << "Running Parallel Naive Diameter\n";
    start = high_resolution_clock::now();
    res = naive_diameter_parallel(graph, 0);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Parallel Naive Diameter Time taken: " << duration.count() << "ms. Got value: " << res.first << '\n';
}