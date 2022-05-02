#include "graph.hpp"
#include<omp.h>
#ifndef DIAMETER_H
#define DIAMETER_H



std::pair<long long, long long> naive_diameter_parallel(Graph &G, long long k){

    long long diameter = 0;

#pragma omp parallel for num_threads(omp_get_max_threads()) shared(G, diameter)
    for (int i = 1; i <= G.get_num_nodes(); i++){
        diameter = std::max(diameter, G.get_ecc(i));
    }
    return std::make_pair(diameter, G.get_num_nodes());
}

std::pair<long long, long long> naive_diameter(Graph &G, long long k){
    long long diameter = 0;

    for (int i = 1; i <= G.get_num_nodes(); i++){
        diameter = std::max(diameter, G.bfs(i));
    }
    return std::make_pair(diameter, G.get_num_nodes());
}

std::pair<long long, long long> iFUB(Graph &G, long long k){
    long long start = G.four_sweep();
    long long dep = G.bfs(start);
    std::vector<long long> bfs_tree = G.get_parents();
    std::vector<long long> depths = G.get_depths();

    long long max_depth = 0;
    for(int i = 1; i<bfs_tree.size(); i++){
        max_depth = std::max(max_depth, depths[i]);
    }

    std::vector<std::vector<long long>> fringe_sets;
    
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
        for(auto &i : fringe_sets[cur])
            max_ecc = std::max(max_ecc, G.bfs(i));

        total_bfs += fringe_sets[cur].size();

        lb = std::max(lb, max_ecc);
        if(std::max(lb, max_ecc) > 2*(cur-1))
            break;
        ub = 2*(cur-1);
        cur -= 1;
    }
    return std::make_pair(lb, total_bfs+5);
}


std::pair<long long, long long> iFUB_parallel(Graph &G, long long k){
    long long start = G.four_sweep();
    long long dep = G.bfs(start);
    std::vector<long long> bfs_tree = G.get_parents();
    std::vector<long long> depths = G.get_depths();

    long long max_depth = 0;
    for(int i = 1; i<bfs_tree.size(); i++){
        max_depth = std::max(max_depth, depths[i]);
    }

    std::vector<std::vector<long long>> fringe_sets;
    
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
        for(int i = 0; i<fringe_sets[cur].size(); i++)
            max_ecc = std::max(max_ecc, G.get_ecc(fringe_sets[cur][i]));
        
        total_bfs += fringe_sets[cur].size();

        lb = std::max(lb, max_ecc);
        if(std::max(lb, max_ecc) > 2*(cur-1))
            break;
        ub = 2*(cur-1);
        cur -= 1;
    }
    return std::make_pair(lb, total_bfs+5);
}

#endif