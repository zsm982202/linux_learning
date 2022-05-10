#OBJS = add.o sub.o mul.o div.o test.o
SRC=${wildcard *.cpp}
OBJS=${patsubst %.cpp, %.o, ${SRC}}

test:${OBJS}
	g++ $^ -o $@

%.o:%.cpp
	g++ -c $^ -o $@

.PHONY:clean
clean:
	rm -rf ${OBJS} test
