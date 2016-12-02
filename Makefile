SRC:=$(wildcard src/*.cpp)
OBJ:=$(subst .cpp,.o,$(SRC))
LIB:=lib/libphoton.so

INC=include

CFLAGS=-Wall -std=c++11 -I$(INC)

lib/libphoton.a: $(OBJ)
	ar rcs libphoton.a $^
	mkdir -p lib
	mv libphoton.a lib/

#libphoton: $(OBJ)
#	g++ -shared -fPIC $^ -o libphoton.so
#	mkdir -p lib
#	mv libphoton.so lib/

%.o : %.cpp
	g++ $(CFLAGS) -fPIC -c $^ -o $@

tester: lib/libphoton.a test/tester.cpp
	g++ $(CFLAGS) -Llib $^ -o $@ -lphoton -lGL -lglfw -lGLEW 

#tester: test/tester.cpp
#	g++ $(CFLAGS) -Llib $^ -o $@ -lphoton -lGL -lglfw -lGLEW 
#	mv tester test/tester


.PHONY: clean
clean:
	rm -f $(OBJ) tester
