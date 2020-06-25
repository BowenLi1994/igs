
Debug_Level=-O3 -Wall 
CC=g++
CXXFLAGS=-c  $(Debug_Level) -std=c++11
 


all: OBJ_FILE 

OBJ_FILE: 
	$(CC) $(CXXFLAGS) ./*.cpp
	$(CC) -o  oracle  *.o 

clean:
	rm -f ./*.o ./*.d ./*exe ./*stackdump oracle 
