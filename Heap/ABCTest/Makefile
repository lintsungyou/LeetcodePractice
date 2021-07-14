CXX = g++
CXXFLAG = -std=c++17 -O3
OBJS = ABCTest_alg.o \
	   main.o

PROGRAMNAME = a.out

all:${PROGRAMNAME}

run : ${PROGRAMNAME}
	./$<

${PROGRAMNAME}: ${OBJS}
	${CXX} ${OBJS} -o $@

${OBJS}: main.cpp ABCTest_alg.cpp ABCTest_alg.h
	${CXX} ${CXXFLAG} -c ABCTest_alg.cpp main.cpp

clean:
	rm -f *.o *~ *.out