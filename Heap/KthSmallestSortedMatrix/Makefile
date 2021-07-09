CXX = g++
CXXFLAG = -std=c++17 -O3
OBJS = KthSmallestSortedMatrix_alg.o \
	   main.o

PROGRAMNAME = a.out

all:${PROGRAMNAME}

run : ${PROGRAMNAME}
	./$<

${PROGRAMNAME}: ${OBJS}
	${CXX} ${OBJS} -o $@

${OBJS}: main.cpp KthSmallestSortedMatrix_alg.cpp KthSmallestSortedMatrix_alg.h
	${CXX} ${CXXFLAG} -c KthSmallestSortedMatrix_alg.cpp main.cpp

clean:
	rm -f *.o *~ *.out