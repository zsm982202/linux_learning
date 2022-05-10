all: read_fifo write_fifo

read_fifo:6read_fifo.cpp
	g++ $< -o $@

write_fifo:5write_fifo.cpp
	g++ $< -o $@

.PHONY:clean
clean:
	rm -rf read_fifo write_fifo
