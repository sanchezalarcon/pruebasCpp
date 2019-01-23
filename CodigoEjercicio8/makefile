CC = g++
OPCIONES = -Wall -Werror -I. -pthread
AUX = Lista.c ListaNodo.c ListaNodoCuatroReales.c RegresionLineal.c IntegrarSimpson.c IntervaloPrediccion.c Gauss.c
EXE1 = Ejercicio8
OBJ1 = Ejercicio8.o Lista.o ListaNodo.o ListaNodoCuatroReales.o RegresionLineal.o IntegrarSimpson.o IntervaloPrediccion.o Gauss.o
all: clean comp ejec1
comp: 
	$(CC) -c $(AUX) $(OPCIONES)
ejec1: $(OBJ1) 
	$(CC) $(OBJ1) -o $(EXE1) $(OPCIONES)
clean:
	rm -f $(OBJ1) $(EXE1)
