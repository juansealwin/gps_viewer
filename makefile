CC = gcc
CCFLAGS = -Wall -ansi -pedantic

all:gpsviwer

gpsviwer: main.o TDA_vector.o procesador_gps.o registros_gps.o errores.o impresor.o
	$(CC) $(CCFLAGS) -o gpsviwer main.o TDA_vector.o procesador_gps.o registros_gps.o impresor.o errores.o
main.o: main.c types.h TDA_vector.h procesador_gps.h registros_gps.h impresor.h errores.h
	$(CC) $(CCFLAGS) -c main.c
TDA_vector.o: TDA_vector.c types.h registros_gps.h
	$(CC) $(CCFLAGS) -c TDA_vector.c
procesador_gps.o: procesador_gps.c types.h TDA_vector.h registros_gps.h
	$(CC) $(CCFLAGS) -c procesador_gps.c
registros_gps.o: registros_gps.c types.h TDA_vector.h
	$(CC) $(CCFLAGS) -c registros_gps.c
impresor.o: impresor.c TDA_vector.h registros_gps.h types.h
	$(CC) $(CCFLAGS) -c impresor.c
errores.o: errores.c types.h
	$(CC) $(CCFLAGS) -c errores.c
clean:
	rm *.o
