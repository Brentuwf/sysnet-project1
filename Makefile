CXXFLAGS = -std=c++11 -g -Wall -Wextra -Wpedantic
CC = g++

OBJS = myshell.o param.o parse.o 
SRC = myshell.cpp param.cpp parse.cpp process.cpp
HDR = param.hpp parse.hpp process.hpp
BINARY = myshell

${BINARY}: ${OBJS} 
	${CC} -o ${BINARY} ${OBJS}

${OBJS}: ${SRC} ${HDR} 
	${CC} -c ${CXXFLAGS} ${SRC}

memory-test: ${BINARY}
	valgrind -s --leak-check=full --show-leak-kinds=all ./${BINARY} -Debug

clean:
	rm -f ${BINARY} *.o
