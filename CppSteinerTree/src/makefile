OBJS = entry.o graph.o main.o solution.o set.o search.o tabulist.o
CC = g++
INC_PATH = ../includes/
OPTS = -g

all: steinertree

steinertree: $(OBJS)
	$(CC) -o steinertree $(OBJS) $(OPTS)

entry.o: entry.cpp $(INC_PATH)steiner.h
	$(CC) -c entry.cpp -o entry.o $(OPTS)

graph.o: graph.cpp $(INC_PATH)graph.h
	$(CC) -c graph.cpp -o graph.o $(OPTS)
			
main.o:	main.cpp $(INC_PATH)steiner.h $(INC_PATH)search.h
	$(CC) -c main.cpp -o main.o $(OPTS)
			
solution.o: solution.cpp $(INC_PATH)solution.h
	$(CC) -c solution.cpp -o solution.o $(OPTS)

set.o: set.cpp $(INC_PATH)set.h
	$(CC) -c set.cpp -o set.o $(OPTS)

search.o: search.cpp $(INC_PATH)search.h
	$(CC) -c search.cpp -o search.o $(OPTS)

tabulist.o: tabulist.cpp $(INC_PATH)tabulist.h
	$(CC) -c tabulist.cpp -o tabulist.o $(OPTS)
			
clean:	
	rm -f steinertree
	rm -f $(OBJS)

