CC=g++
LIBS= -std=c++11 -g

analyser: analyser.o 
	$(CC) -o analyser analyser.o $(LIBS)

analyser.o: analyser.cpp
	$(CC) -c -o analyser.o analyser.cpp $(LIBS)	
	
clean:
	rm -f ./*.o
	rm analyser