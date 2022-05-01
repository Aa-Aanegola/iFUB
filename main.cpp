#include<bits/stdc++.h>
#include"graph.hpp"

using namespace std;

pair<long long, long long> iFUB(Graph &G, long long k){
    long long start = G.four_sweep();
    cout << "start node: " << start << "\n";
    long long dep = G.bfs(start);
    vector<long long> bfs_tree = G.get_parents();
    vector<long long> depths = G.get_depths();

    long long max_depth = 0;
    for(int i = 0; i<bfs_tree.size(); i++){
        max_depth = max(max_depth, depths[i]);
    }

    vector<vector<long long>> fringe_sets;
    
    fringe_sets.resize(max_depth+1);
    for(int i=1; i<depths.size(); i++){
        if(depths[i] == -1)
            continue;
        fringe_sets[depths[i]].push_back(i);
    }

    cout << "fringe sets created\n";

    long long lb = max_depth, ub = 2*max_depth, cur = max_depth, total_bfs=0;
    while(ub-lb > k){
        cout << "current lower and upper bounds " << lb << " " << ub << "\n";
        long long max_ecc = 0;
        cout << "number in fringe set " << cur << " " << fringe_sets[cur].size() << "\n";
        int c= 0;
        for(auto &i : fringe_sets[cur]){
            cout << "currently on: " << c++ << "\r";
            flush(cout);
            max_ecc = max(max_ecc, G.bfs(i));
            total_bfs += 1;
        }
        cout << "\n";
        
        lb = max(lb, max_ecc);
        if(max(lb, max_ecc) > 2*(cur-1))
            break;
        ub = 2*(cur-1);
        cur -= 1;
    }
    return make_pair(lb, total_bfs);
}

int main(int argc, char* argv[]){
    if(argc != 2)
        return 1;
    Graph graph(argv[1]);

    auto res = iFUB(graph, 0);
    cout << res.first << " " << res.second << "\n";
    return 0;
}