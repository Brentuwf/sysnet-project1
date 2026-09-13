CXXFLAGS = -std=c++11 -g -Wall -Wextra -Wpedantic
CC = g++

OBJS = myshell.o shell.o process.o param.o parse.o 
SRC = myshell.cpp shell.cpp process.cpp param.cpp parse.cpp 
HDR = shell.hpp process.hpp param.hpp parse.hpp 
BINARY = myshell

${BINARY}: ${OBJS} 
	${CC} -o ${BINARY} ${OBJS}

${OBJS}: ${SRC} ${HDR} 
	${CC} -c ${CXXFLAGS} ${SRC}

memory-test: ${BINARY}
	valgrind -s --leak-check=full --show-leak-kinds=all ./${BINARY} -Debug

clean:
	rm -f ${BINARY} *.o
