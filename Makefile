CXXFLAGS = -std=c++11 -g -Wall -Wextra -Wpedantic
CC = g++

OBJS = myshell.o param.o parse.o 
SRC = myshell.cpp param.cpp parse.cpp
HDR = param.hpp parse.hpp
BINARY = myshell

${BINARY}: ${OBJS} 
	${CC} -o ${BINARY} ${OBJS}

${OBJS}: ${SRC} ${HDR} 
	${CC} -c ${CXXFLAGS} ${SRC}

clean:
	rm -f ${BINARY} *.o
