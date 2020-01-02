#$^ : liste des dépendances
#$@ : nom de la cible
#$< : nom de la première dépendance

CC=g++
CCFLAGS= -Wall -Werror -std=c++11 -g
SRC= $(wildcard sources/*.cc)
OBJ= $(SRC:.cc=.o)
EXEC= timebomb_serv

all: $(EXEC) timebomb_client

timebomb_client :
	g++ $(CCFLAGS) sources/client/timebomb_cli.cc -o timebomb_cli -lpthread

$(EXEC): $(OBJ)
	$(CC) $(LIBFLAGS) $^ -o $@ -lpthread

%.o: %.cc
	$(CC) $(CCFLAGS) -o $@ -c $<

.depend:
	g++ -MM $(SRC) > .depends
-include .depends

clean:
	rm -f $(OBJ) $(EXEC) timebomb_cli
