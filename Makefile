CXXFLAGS = -std=c++11 -g -Wall -Wextra -Wpedantic
CC = g++

myshell: param.o myshell.cpp 
	${CC} -o myshell myshell.cpp param.o

param.o: param.hpp param.cpp
	${CC} -c ${CXXFLAGS} param.cpp

clean:
	rm -f myshell *.o
