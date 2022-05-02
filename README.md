# iFUB
This repository contains an implementation of the iFUB algorithm for graph diameter computation along with some auxiliary helper files. For more details about the implementation, please refer to [](report.pdf). 
To compile the files, simply run ```make all```. The executables will be created in the ```out/``` directory. For more granular control over what executables are created use the following: 
- ```make ifub``` : Compile the iFUB and parallelized iFUB testing programs
- ```make apsp``` : Compile the naive and parallelized diameter computation algorithm testing programs 
- ```make util``` : Compile the graph generation and preprocessing programs


### Generating graphs
To generate a random graph, run the following commands:

```
./out/gen_graph <n> <m> <output-file>
```

This will create a graph with ```n``` nodes and at most ```m``` edges and dump it to the specified binary output file. The graphs generated are guaranteed to be connected, and if ```m<=n-1```, a tree will be returned. 

### Loading graphs from mtx files
A popular format to store graphs and matrices is the ```.mtx``` format. This however poses challenges to our implementation as text files inhibit random access to the edge list (due to variable line length). In order to solve this, we provide code that converts a ```.mtx``` file into a binary file that can be used with our program. 

```
./out/preprocess <path-to-mtx> <path-to-binary>
```

### Running diameter computation algorithms
There are four diameter computation algorithms: 
- iFUB: ```./out/iFUB <path-to-graph>```
- parallel iFUB: ```./out/parallel_iFUB <path-to-graph>```
- apsp: ```./out/apsp <path-to-graph>```
- parallel apsp: ```./out/parallel_apsp <path-to-graph>``` 

path-to-graph represents the path to the binary graph whose diameter we wish to compute.