OBJS = add.o sub.o mul.o div.o test.o

test:${OBJS}
	g++ ${OBJS} -o test

add.o:add.cpp
	g++ -c add.cpp -o add.o

sub.o:sub.cpp
	g++ -c sub.cpp -o sub.o

mul.o:mul.cpp
	g++ -c mul.cpp -o mul.o

div.o:div.cpp
	g++ -c div.cpp -o div.o

test.o:test.cpp
	g++ -c test.cpp -o test.o

clean:
	rm -rf ${OBJS} test
