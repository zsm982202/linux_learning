OBJS = add.o sub.o mul.o div.o test.o

test:${OBJS}
	g++ $^ -o $@

%.o:%.cpp
	g++ -c $^ -o $@

clean:
	rm -rf ${OBJS} test
