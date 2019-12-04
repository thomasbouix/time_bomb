#$^ : liste des dépendances
#$@ : nom de la cible
#$< : nom de la première dépendance

CC=g++
CCFLAGS= -Wall -Werror -std=c++11 -g
SRC= $(wildcard sources/*.cc)
OBJ= $(SRC:.cc=.o)
EXEC= programme 

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LIBFLAGS) $^ -o $@

%.o: %.cc
	$(CC) $(CCFLAGS) -o $@ -c $<

.depend:
	g++ -MM $(SRC) > .depends
-include .depends

clean:
	rm -f $(OBJ) $(EXEC)


