#this sets these objects as the default target so the makefile automatically uses these when using the make command and makes the executable named lab8.exe
make: main.o matrix.o
	g++ -Wall  main.o matrix.o -o lab8.exe

# Builds the object file using main as the target and makes sure to also grab matrix.hpp because it is included in main.
main.o: main.cpp matrix.hpp
	g++ -Wall  -c main.cpp -o main.o

# this builds the object matrix and grabs matrix.cpp and matrix.hpp because the .cpp needs the hpp headers
matrix.o: matrix.cpp matrix.hpp
	g++ -Wall -c matrix.cpp -o matrix.o

# this part is used to clean up the output of the makefile so the file can be made again
clean:
	rm -f main.o matrix.o lab8.exe