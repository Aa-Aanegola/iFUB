#include <bits/stdc++.h>
#include <omp.h>
#include "graph.hpp"
#include "diameter.hpp"

using namespace std;
using namespace std::chrono;


int main(int argc, char* argv[]){
    if(argc != 2)
        return 1;
    cout << std::fixed << std::setprecision(4);
    Graph graph(argv[1]);


    cout << "number of nodes: " << graph.get_num_nodes() << " number of edges: " << graph.get_num_edges()/2 << "\n";
    auto start = high_resolution_clock::now();
    auto res = iFUB_parallel(graph, 0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "parallelized iFUB computed diameter: " << res.first << " number of BFS's: " << res.second << " time taken: " << duration.count()/1e6 << " seconds\n";
    return 0; 
}