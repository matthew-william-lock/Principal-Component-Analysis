CC=g++
LIBS= -std=c++11 -g 
EIGEN= -I ./eigen/

analyser: analyser.o CSV.o 
	$(CC) $(EIGEN) -o analyser analyser.o CSV.o $(LIBS) 

analyser.o: analyser.cpp
	$(CC) $(EIGEN) -c -o analyser.o analyser.cpp $(LIBS)	

CSV.o: CSV.cpp CSV.h
	$(CC) $(EIGEN) -c -o CSV.o CSV.cpp $(LIBS)
	
clean:
	rm -f ./*.o
	rm analyser

run:
	./analyser