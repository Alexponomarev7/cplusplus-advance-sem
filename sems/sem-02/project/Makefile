CC=g++
LINK=g++
CFLAGS=-fPIC

UNAME=$(shell uname -s)
ifeq ($(UNAME), Darwin)
	OS=APPLE
endif
ifeq ($(UNAME), Linux)
	OS=LINUX
endif

build: all

all: library main
	$(LINK) -o alert library.so main.o

library: 
	$(CC) -shared $(CFLAGS) library.cpp -o library.so

main: 
	$(CC) -c $(CFLAGS) main.cpp -o main.o

clean:
	rm -rf *.o || true
	
distclean: clean
	rm -rf alert library.so || true

fmt:
	clang-format -i --style=Google *.cpp *.h
