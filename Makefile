com:
	g++ -O1 main.cpp fns.cpp Population.cpp Chromosome.cpp utils.cpp -std=c++11 -o lab
comO2:
	g++ -O2 main.cpp fns.cpp Population.cpp Chromosome.cpp utils.cpp -std=c++11 -o lab
comO3:
	g++ -O3 main.cpp fns.cpp Population.cpp Chromosome.cpp utils.cpp -std=c++11 -o lab
run: com
	./lab
