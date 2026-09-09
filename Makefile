CXXFLAGS = -std=c++11 -g -Wall -Wextra -Wpedantic
CC = g++

myshell: myshell.o param.o parse.o
	${CC} -o myshell myshell.o param.o parse.o

myshell.o: myshell.cpp param.hpp
	${CC} -c ${CXXFLAGS} myshell.cpp

param.o: param.cpp param.hpp
	${CC} -c ${CXXFLAGS} param.cpp

parse.o: parse.cpp parse.hpp param.hpp
	${CC} -c ${CXXFLAGS} parse.cpp

clean:
	rm -f myshell *.o
