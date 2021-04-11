
CC=gcc
# Use c11 standard
# Ignore warnings
# Use pthread library
CFLAGS= -std=c11 -w -I.
LDFLAGS=-pthread -w -lm
# Add dependencies
DEPS=include/color.h include/validator.h include/car.h
# Add source codes
SRC_CD=src/validator.c

TARGET=main main.o

%.o: %.c $(DEPS)
	@echo Compiling dependencies ...
	$(CC) -c -o $@ $< $(CFLAGS)

mainmake: main.o
	@echo Compiling target ...
	$(CC) -o $(TARGET) $(SRC_CD) $(LDFLAGS)

clean:
	@echo Clean compiled files ...
	rm *.o main
