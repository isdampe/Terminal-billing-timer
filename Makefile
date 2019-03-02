CXX = gcc
src = $(wildcard src/*.c)
obj = $(src:.c=.o)

LDFLAGS = -std=c11 -O3
OSFLAGS = -lncurses

tbt: $(obj)
	@mkdir -p bin
	$(CXX) -g -o bin/$@ $^ $(LDFLAGS) $(OSFLAGS)

clean:
	rm $(obj)

install:
	@cp bin/tbt /usr/local/bin/tbt

uninstall:
	@rm /usr/local/bin/tbt
