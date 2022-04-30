#include<bits/stdc++.h>
#include"graph.hpp"

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 2)
        return 1;
    Graph graph(argv[1]);

    cout << graph.get_num_nodes() << " " << graph.get_num_edges() << "\n";

    cout << graph.bfs(7299) << "\n";
    cout << graph.get_parent(694) << "\n";
    cout << graph.get_degree(1) << "\n";
    cout << graph.four_sweep() << "\n";

    return 0;
}