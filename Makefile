com com1:
	g++ -O1 main.cpp fns.cpp Population.cpp Chromosome.cpp utils.cpp -std=c++11 -o lab
com2:
	g++ -O2 main.cpp fns.cpp Population.cpp Chromosome.cpp utils.cpp -std=c++11 -o lab
com3:
	g++ -O3 main.cpp fns.cpp Population.cpp Chromosome.cpp utils.cpp -std=c++11 -o lab

FN?=1
run run1: com
	./lab ${FN}
run2: com2
	./lab ${FN}
run3: com3
	./lab ${FN}
