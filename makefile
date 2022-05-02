all: ifub apsp util

ifub: 
	mkdir -p out
	g++ iFUB.cpp -o iFUB -fopenmp
	g++ parallel_iFUB.cpp -o parallel_iFUB -fopenmp 
	mv iFUB out/ 
	mv parallel_iFUB out/

apsp:
	mkdir -p out 
	g++ apsp.cpp -o apsp -fopenmp
	g++ parallel_apsp.cpp -o parallel_apsp -fopenmp
	mv apsp out/
	mv parallel_apsp out/

util: 
	mkdir -p out/
	g++ utils/gen_graph.cpp -o gen_graph
	g++ utils/preprocess.cpp -o preprocess 
	mv gen_graph out/ 
	mv preprocess out/

clean: 
	rm -rf out/