all:ppm

ppm: ppm.o image_manipulation.o image_operations.o
	g++ -o ppm ppm.o image_manipulation.o image_operations.o

ppm.o: ppm.cpp image_manipulation.h image_class.h image_operations.h
	g++ -o ppm.o -c ppm.cpp -Wall

image_manipulation.o: image_manipulation.cpp image_manipulation.h image_class.h
	g++ -o image_manipulation.o -c image_manipulation.cpp -Wall

image_operations.o: image_operations.cpp image_operations.h image_class.h
	g++ -o image_operations.o -c image_operations.cpp -Wall

clean:
	rm -rf *.o

mrproper: clean
	rm -rf ppm