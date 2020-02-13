#$^ : liste des dépendances
#$@ : nom de la cible
#$< : nom de la première dépendance

CC=g++
CCFLAGS= -Wall -Werror -std=c++11 -g
LIBFLAGS=-I/usr/include/SDL2 -lSDL2_image -lSDL2_ttf -lSDL2 -lpthread
SRC_SERV= $(wildcard sources/server/*.cc)
SRC_CLI= $(wildcard sources/client/*.cc)
OBJ_SERV= $(SRC_SERV:.cc=.o)
OBJ_CLI= $(SRC_CLI:.cc=.o)
EXEC_SERV= timebomb_serv
EXEC_CLI= timebomb_cli

all: $(EXEC_SERV) $(EXEC_CLI) 

$(EXEC_CLI): $(OBJ_CLI)
	$(CC) $^ -o $@ $(LIBFLAGS)

$(EXEC_SERV): $(OBJ_SERV)
	$(CC) $^ -o $@ $(LIBFLAGS)

%.o: %.cc
	$(CC) $(CCFLAGS) -o $@ -c $< $(LIBFLAGS)

.depend:	
	g++ -MM $(SRC_SERV) $(SRC_CLI) > .depends
-include .depends	# inclu le .depends dans le makefile

clean:
	rm -f $(OBJ_SERV) $(OBJ_CLI) $(EXEC_SERV) $(EXEC_CLI) 
