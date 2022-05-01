#include <bits/stdc++.h>

class Graph{
private:
    std::vector<long long> parent;
    std::vector<long long> depth;
    std::ifstream f;
    long long num_nodes, num_edges;
    
    void reset_parents();
    void reset_depth();
public:
    Graph(std::string);

    long long get_num_nodes();
    long long get_num_edges();
    long long get_parent(long long);
    long long get_depth(long long);
    long long get_degree(long long);
    std::vector<long long> get_neighbors(long long);
    std::vector<long long> get_parents();
    std::vector<long long> get_depths();
    
    long long bfs(long long);
    long long four_sweep();
};


Graph::Graph(std::string file){
    f.open(file.c_str(), std::ios::binary);
    f.read((char*)&num_nodes, sizeof(num_nodes));
    f.read((char*)&num_edges, sizeof(num_edges));
    parent.resize(num_nodes+1, 0);
    depth.resize(num_nodes+1, -1);
}

void Graph::reset_parents(){
    for(auto &i : parent)
        i = 0;
}

void Graph::reset_depth(){
    for(auto &i : depth)
        i = -1;
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

long long Graph::get_depth(long long node){
    return depth[node];
}

std::vector<long long> Graph::get_neighbors(long long node){
    long long low = 0, high = num_edges, from;
    f.clear();
    f.seekg(0, std::ios::beg);

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

std::vector<long long> Graph::get_parents(){
   return parent;
}

std::vector<long long> Graph::get_depths(){
    return depth;
}

long long Graph::get_degree(long long node){
    std::vector<long long> neighbors = get_neighbors(node);
    return neighbors.size();
}

long long Graph::bfs(long long root){
    reset_parents();
    reset_depth();

    std::queue<long long> q;
    depth[root] = 0;
    q.push(root);

    while(!q.empty()){
        long long node = q.front();
        q.pop();

        std::vector<long long> neighbors = get_neighbors(node);
        for(auto &child : neighbors){
            if(depth[child] == -1){
                q.push(child);
                parent[child] = node;
                depth[child] = depth[node]+1;
                // std::cout << node << " " << child << " " << depth[child] << "\n";
            }
        } 
    }

    return *std::max_element(depth.begin(), depth.end());
}

long long Graph::four_sweep(){
    long long r1 = 1, max_degree = 0;
    for(long long node=1; node<=num_nodes; node++){
        long long degree = get_degree(node);
        if(degree > max_degree){
            r1 = node;
            max_degree = degree;
        }
    }

    bfs(r1);
    long long a1 = std::max_element(depth.begin(), depth.end())-depth.begin();
    bfs(a1);
    long long b1 = std::max_element(depth.begin(), depth.end())-depth.begin();
    long long half_depth = *std::max_element(depth.begin(), depth.end())/2;
    long long r2 = b1;
    while(half_depth--)
        r2 = parent[r2];
    
    bfs(r2);
    long long a2 = std::max_element(depth.begin(), depth.end())-depth.begin();
    bfs(a2);
    long long b2 = std::max_element(depth.begin(), depth.end())-depth.begin();
    half_depth = *std::max_element(depth.begin(), depth.end())/2;
    long long ret = b2;
    while(half_depth--)
        ret = parent[ret];

    return ret;
}