CXX = g++
CXXFLAG = -std=c++17 -O3
OBJS = FindMedianFromStream_alg.o \
	   main.o

PROGRAMNAME = a.out

all:${PROGRAMNAME}

run : ${PROGRAMNAME}
	./$<

${PROGRAMNAME}: ${OBJS}
	${CXX} ${OBJS} -o $@

${OBJS}: main.cpp FindMedianFromStream_alg.cpp FindMedianFromStream_alg.h
	${CXX} ${CXXFLAG} -c FindMedianFromStream_alg.cpp main.cpp

clean:
	rm -f *.o *~ *.out