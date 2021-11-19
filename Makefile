BIN = prog
TAR = defalt_name

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
ENTETE = $(wildcard *.h)

CFLAGS = -Wall -ansi -pedantic -lm

OBJECTSPATH = objects/

CC = gcc




all: $(BIN)
	./$< in1.txt

debug: $(BIN)                 # J'ai rajouter une option pour faire l'executable tout en l'executant avec le debugger ddd
	ddd $<

$(BIN): $(OBJ)
	$(CC) $(OBJECTSPATH)$^ $(CFLAGS) -o $@
	 
%.o: %.c                   # Je rejoute l'option -g pour pouvoir utiliser le debugger   
	$(CC) -g -c $< -o $(OBJECTSPATH)$@

dist: mrproper   #tar -cf $(TAR).tar $(SRC) $(ENTETE)
	tar -zcvf $(TAR).tar.gz [^Makefile]*

mrproper: clear
	rm -f $(BIN)
	
clear:
	rm -f $(OBJECTSPATH)*.o
