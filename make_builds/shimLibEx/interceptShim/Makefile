CC=g++
CFLAGS=-Wall -g
BINS=shimTest.elf shimLib.so

all: $(BINS)
%.so: %.cpp
	$(CC) $(CFLAGS) -fPIC -shared -Wl,--no-as-needed -ldl -o $@ $^

%.elf: %.cpp
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(BINS)
	rm -r *.so
