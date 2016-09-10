CFLAGS =  -g -Wall

TARGET = cssParser

cssParser: src/main.o src/parser.o src/util.o 
	cc -o $(TARGET) $(CFLAGS) src/main.o src/parser.o src/util.o

main.o: src/main.c 
	cc -c -o src/main.o $(CFLAGS) src/main.c

parser.o: src/parser.c src/parser.h 
	cc -c -o src/parser.o $(CFLAGS) src/parser.c 

util.o: src/util.c src/util.h 
	cc -c -o src/util.o $(CFLAGS) src/util.c 

.PHONY: clean

clean:
	@rm -f cssParser src/*.o
