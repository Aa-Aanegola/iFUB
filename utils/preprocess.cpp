#include<bits/stdc++.h>
#define ll long long

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 3)
        return 1;
    
    ifstream in_file(argv[1]);
    ofstream out_file(argv[2], ios::binary);

    string str;
    bool first = false;
    
    vector<set<ll>> adj;
    ll num_nodes, num_edges;

    string prevstr;
    while(true){
        getline(in_file, str);
        if(!str.length() or str==prevstr)
            break;
        prevstr = str;
        if(str[0] == '%')
            continue;

        stringstream s;
        if(!first){
            s << str;
            s >> num_nodes >> num_nodes >> num_edges;
            cout << num_nodes << " " << num_edges << "\n";

            adj.resize(num_nodes+1);    
            first = true;
            continue;
        }
    
        s << str;
        ll from, to;
        s >> from >> to;

        adj[from].insert(to);
        adj[to].insert(from);
    }
    
    num_edges = 0;
    for(int i = 1; i<adj.size(); i++){
        num_edges += adj[i].size();
    }

    out_file.write((char*)&num_nodes, sizeof(num_nodes));
    out_file.write((char*)&num_edges, sizeof(num_edges));
    

    for(long long i = 1; i<adj.size(); i++){
        for(auto &node : adj[i]){
            out_file.write((char*)&i, sizeof(i));
            out_file.write((char*)&node, sizeof(node));
        }
    }

    return 0;
}