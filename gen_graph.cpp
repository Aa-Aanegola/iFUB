#include <bits/stdc++.h>

using namespace std;

vector<vector<long long>> adj;

void gen_graph(long long n, long long m, string file_name){
    int len = n-2;
    vector<long long> prufer(len);

    for(int i = 0; i<len; i++){
        prufer[i] = 1 + rand()%(len+2);
    }

    vector<long long> vertex_set(n, 0);
    vector<set<long long>> adj(n); 

    for(int i = 0; i<n-2; i++)
        vertex_set[prufer[i]-1] += 1;
    
    int j = 0;

    for(int i = 0; i<n-2; i++){
        for(j = 0; j<n; j++){
            if(vertex_set[j] == 0){
                vertex_set[j] = -1;
                adj[j].insert(prufer[i]-1);
                adj[prufer[i]-1].insert(j);
                vertex_set[prufer[i]-1] -= 1;
                break;
            }
        }
    }

    j = 0;

    long long l = -1, r = -1;
    for(int i = 0; i<n; i++){
        if(vertex_set[i] == 0 && j == 0){
            l = i;
            j = 1;
        }
        else if(vertex_set[i] == 0 && j == 1)
            r = i;
    }
    adj[l].insert(r);
    adj[r].insert(l);

    long long cur = n-1;

    while(cur < m){
        long long from = rand()%n;
        long long to = rand()%n;
        while(to == from)
            to = rand()%n;
        adj[from].insert(to);
        adj[to].insert(from);
        cur++;
    }

    m = 0;
    for(int i = 0; i<n; i++)
        m += adj[i].size();

    cout << n << " " << m/2 << "\n";

    if(file_name == "display"){
        
        for(int i = 0; i<n; i++){
            cout << i+1 << ": ";
            for(auto &j : adj[i])
                cout << j+1 << " ";
            cout  << "\n";
        }
        return;
    }

    ofstream of(file_name, ios::binary);
    
    of.write((char*)&n, sizeof(n));
    of.write((char*)&m, sizeof(m));

    for(int i = 0; i<n; i++){
        for(auto &j : adj[i]){
            long long l = i+1;
            long long r = j+1;
            of.write((char*)&l, sizeof(l));
            of.write((char*)&r, sizeof(r));
        }
    }
}

int main(int argc, char *argv[]){
    srand(time(0));

    long long n = stoi(argv[1]);
    long long m = stoi(argv[2]);
    string file = argv[3];
    gen_graph(n, m, file);
}