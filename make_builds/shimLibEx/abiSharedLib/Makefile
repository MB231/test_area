CC=g++
CFLAGS=-Wall -g
BINS=shimTest.elf shimLib.so

all: $(BINS)
%.so: %.cpp
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^

%.elf: %.cpp
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(BINS)
	rm -r *.so
