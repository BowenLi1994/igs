
Debug_Level=-O3 -Wall 
CC=g++
CXXFLAGS=-c  $(Debug_Level) -std=c++11  -Wall 
 


all: OBJ_FILE 

OBJ_FILE: 
	$(CC) $(CXXFLAGS) ./*.cpp
	$(CC) -o  adaptive_sibling *.o 

clean:
	rm -f ./*.o ./*.d ./*exe ./*stackdump adaptive_sibling 
