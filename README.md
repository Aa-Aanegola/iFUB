# iFUB
This repository contains an implementation of the iFUB algorithm for graph diameter computation along with some auxiliary helper files. For more details about the implementation, please refer to [](report.pdf). 

### Generating graphs
To generate a random graph, run the following commands:

```
g++ gen_graph.cpp -o gen_graph
./gen_graph <n> <m> <output-file>
```

This will create a graph with ```n``` nodes and at most ```m``` edges and dump it to the specified binary output file. The graphs generated are guaranteed to be connected, and if ```m<=n-1```, a tree will be returned. 

### Loading graphs from mtx files
A popular format to store graphs and matrices is the ```.mtx``` format. This however poses challenges to our implementation as text files inhibit random access to the edge list (due to variable line length). In order to solve this, we provide code that converts a ```.mtx``` file into a binary file that can be used with our program. 

```
g++ preprocess.cpp -o preprocess
./preprocess <path-to-mtx> <path-to-binary>
```

### Comparing iFUB and the naive algorithm
Our goal was to compare the iFUB algorithm with a naive diameter computation algorithm, and this has been implemented in ```main.cpp```. 
```
g++ main.cpp -o iFUBvsNaive
./iFUBvsNaive <path-to-binary>
```