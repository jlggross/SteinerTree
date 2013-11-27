# makefile pro Steinertree

OBJS = entrada.o grafo.o main.o solucao.o set.o busca.o listabu.o
CC = g++
INC_PATH = ../includes/
OPTS = -g #-pg #necessario para fazer o profiling
EXTRA_CFLAGS = -DLOG_AVAL

all: steinertree

steinertree:	$(OBJS)
		$(CC) -o steinertree $(EXTRA_CFLAGS) $(OBJS) $(OPTS)

entrada.o:	entrada.cpp $(INC_PATH)steiner.h
		$(CC) -c entrada.cpp -o entrada.o $(OPTS)

grafo.o:	grafo.cpp $(INC_PATH)grafo.h
		$(CC) -c grafo.cpp -o grafo.o $(OPTS)
			
main.o:		main.cpp $(INC_PATH)steiner.h $(INC_PATH)buscas.h
		$(CC) -c main.cpp -o main.o $(OPTS)
			
solucao.o:	solucao.cpp $(INC_PATH)solucao.h
		$(CC) -c solucao.cpp -o solucao.o $(OPTS)

set.o:		set.cpp $(INC_PATH)set.h
		$(CC) -c set.cpp -o set.o $(OPTS)

busca.o:	busca.cpp $(INC_PATH)buscas.h
		$(CC) -c busca.cpp -o busca.o $(OPTS)

listabu.o:	listabu.cpp $(INC_PATH)listabu.h
		$(CC) -c listabu.cpp -o listabu.o $(OPTS)
			
clean:	
	rm -f steinertree
	rm -f $(OBJS)

