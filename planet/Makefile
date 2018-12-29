all : planet

SRC:=$(wildcard *.cpp)
OBJ:=$(subst .cpp,.o,$(SRC))

INC=../include

CFLAGS=-Wall -std=c++14 -I$(INC) -g -O0

%.o : %.cpp
	g++ $(CFLAGS) -fPIC -c $^ -o $@

planet: ../lib/libphoton.a $(OBJ)
	g++ $(CFLAGS) -L../lib $^ -o $@ -lphoton -lGL -lglfw -lGLEW 

.PHONY: clean
clean:
	rm -f $(OBJ) planet
