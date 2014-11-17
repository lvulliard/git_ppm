all:ppm

ppm: ppm.o image_manipulation.o image_operations.o
	gcc -o ppm ppm.o image_manipulation.o image_operations.o

ppm.o: ppm.c image_manipulation.h image_struc.h image_operations.h
	gcc -o ppm.o -c ppm.c -Wall

image_manipulation.o: image_manipulation.c image_manipulation.h image_struc.h
	gcc -o image_manipulation.o -c image_manipulation.c -Wall

image_operations.o: image_operations.c image_operations.h image_struc.h
	gcc -o image_operations.o -c image_operations.c -Wall

clean:
	rm -rf *.o

mrproper: clean
	rm -rf ppm