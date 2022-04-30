#include <bits/stdc++.h>

class Graph{
private:
    std::vector<long long> parent;
    std::ifstream f;
    long long num_nodes, num_edges;
public:
    Graph(std::string);

    long long get_num_nodes();
    long long get_num_edges();
    long long get_parent(long long);
    std::vector<long long> get_neighbors(long long);
    
    long long bfs(long long);
    void reset_parents();
};


Graph::Graph(std::string file){
    f.open(file.c_str(), std::ios::binary);
    f.read((char*)&num_nodes, sizeof(num_nodes));
    f.read((char*)&num_edges, sizeof(num_edges));
    parent.resize(num_nodes+1, 0);
}

void Graph::reset_parents(){
    std::fill(parent.begin(), parent.end(), 0);
}

long long Graph::get_num_nodes(){
    return num_nodes;
} 

long long Graph::get_num_edges(){
    return num_edges;
} 

long long Graph::get_parent(long long node){
    return parent[node];
}

std::vector<long long> Graph::get_neighbors(long long node){
    long long low = 0, high = num_edges;
        
    long long from;
    while(low<high){
        long long mid = low + (high-low)/2;

        f.seekg((2+2*mid)*sizeof(long long), std::ios::beg);
        f.read((char*)&from, sizeof(from));
    
        if(node <= from)
            high = mid;
        else
            low = mid+1;    
    }
    
    f.seekg((2+2*low)*sizeof(long long));
    std::vector<long long> neighbors;
    
    while(true){
        long long from, to;
        f.read((char*)&from, sizeof(from));
        if(f.eof())
            break;
        f.read((char*)&to, sizeof(to));
        if(from != node)
            break;
        neighbors.push_back(to);
    }
    return neighbors;
}

long long Graph::bfs(long long root){
    reset_parents();

    std::queue<long long> q;
    std::vector<int> dep(num_nodes+1, -1);
    dep[root] = 0;
    q.push(root);

    while(!q.empty()){
        long long node = q.front();
        q.pop();

        std::vector<long long> neighbors = get_neighbors(node);
        for(auto &child : neighbors){
            if(dep[child] == -1){
                q.push(child);
                parent[child] = node;
                dep[child] = dep[node]+1;
                //std::cout << child << " " << parent[child] << " " << dep[child] << "\n";
            }
        } 
    }

    return *std::max_element(dep.begin(), dep.end());
}