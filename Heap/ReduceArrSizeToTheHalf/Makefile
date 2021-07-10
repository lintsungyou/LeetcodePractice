CXX = g++
CXXFLAG = -std=c++17 -O3
OBJS = ReduceArrSizeToTheHalf_alg.o \
	   main.o

PROGRAMNAME = a.out

all:${PROGRAMNAME}

run : ${PROGRAMNAME}
	./$<

${PROGRAMNAME}: ${OBJS}
	${CXX} ${OBJS} -o $@

${OBJS}: main.cpp ReduceArrSizeToTheHalf_alg.cpp ReduceArrSizeToTheHalf_alg.h
	${CXX} ${CXXFLAG} -c ReduceArrSizeToTheHalf_alg.cpp main.cpp

clean:
	rm -f *.o *~ *.out