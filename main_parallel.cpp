#include <bits/stdc++.h>
#include <omp.h>
#include "graph.hpp"

using namespace std;
using namespace std::chrono;

pair<long long, long long> naive_diameter_parallel(Graph &G, long long k)
{

    long long diameter = 0, bfs_count = 0;

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

pair<long long, long long> iFUB(Graph &G, long long k){
    long long start = G.four_sweep();
    long long dep = G.bfs(start);
    vector<long long> bfs_tree = G.get_parents();
    vector<long long> depths = G.get_depths();

    long long max_depth = 0;
    for(int i = 1; i<bfs_tree.size(); i++){
        max_depth = max(max_depth, depths[i]);
    }

    vector<vector<long long>> fringe_sets;
    
    fringe_sets.resize(max_depth+1);
    for(int i=1; i<depths.size(); i++){
        if(depths[i] == -1)
            continue;
        fringe_sets[depths[i]].push_back(i);
    }

    
    long long lb = max_depth, ub = 2*max_depth, cur = max_depth, total_bfs=0;
    while(ub-lb > k){
        long long max_ecc = 0;
        int c= 0;
        for(auto &i : fringe_sets[cur]){
            max_ecc = max(max_ecc, G.bfs(i));
            total_bfs += 1;
        }
        
        lb = max(lb, max_ecc);
        if(max(lb, max_ecc) > 2*(cur-1))
            break;
        ub = 2*(cur-1);
        cur -= 1;
    }
    return make_pair(lb, total_bfs+5);
}


pair<long long, long long> iFUB_parallel(Graph &G, long long k){
    long long start = G.four_sweep();
    long long dep = G.bfs(start);
    vector<long long> bfs_tree = G.get_parents();
    vector<long long> depths = G.get_depths();

    long long max_depth = 0;
    for(int i = 1; i<bfs_tree.size(); i++){
        max_depth = max(max_depth, depths[i]);
    }

    vector<vector<long long>> fringe_sets;
    
    fringe_sets.resize(max_depth+1);
    for(int i=1; i<depths.size(); i++){
        if(depths[i] == -1)
            continue;
        fringe_sets[depths[i]].push_back(i);
    }


    long long lb = max_depth, ub = 2*max_depth, cur = max_depth, total_bfs=0;
    while(ub-lb > k){
        long long max_ecc = 0;
        int c= 0;

#pragma omp parallel for num_threads(omp_get_max_threads()) shared(G, max_ecc, total_bfs)
        for(int i = 0; i<fringe_sets[cur].size(); i++){
            max_ecc = max(max_ecc, G.get_ecc(fringe_sets[cur][i]));
            total_bfs += 1;
        }
        
        lb = max(lb, max_ecc);
        if(max(lb, max_ecc) > 2*(cur-1))
            break;
        ub = 2*(cur-1);
        cur -= 1;
    }
    return make_pair(lb, total_bfs+5);
}

int main(int argc, char *argv[])
{
    cout << std::fixed << std::setprecision(4);
    if (argc != 2)
        return 1;

    Graph graph(argv[1]);

    // cout << "Running sequential iFUB Diameter\n";
    // auto start = high_resolution_clock::now();
    // auto res = iFUB(graph, 0);
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // cout << "Sequential iFUB Diameter Time taken: " << duration.count()/1e6 << "s. Got value: " << res.first << '\n';

    cout << "Running Parallel iFUB\n";
    auto start = high_resolution_clock::now();
    auto res = iFUB_parallel(graph, 0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Parallel iFUB Diameter Time taken: " << duration.count()/1e6 << "s. Got value: " << res.first << '\n';
}