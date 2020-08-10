CXX = g++
CFLAGS = -Wall -w -g 
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -ltinyxml2
SRC = main.cpp player.cpp block.cpp map.cpp
OBJ = main.o player.o block.o map.o 
EXECUTABLE = SOKOBAN


${EXECUTABLE}: ${OBJ}
	${CXX} ${CFLAGS} ${SRC} ${LDFLAGS} -o ${EXECUTABLE}

main.o: main.cpp
	${CXX} -c main.cpp -o main.o

player.o: player.cpp
	${CXX} -c player.cpp -o player.o

map.o: map.cpp
	${CXX} -c map.cpp -o map.o

block.o: block.cpp
	${CXX} -c block.cpp -o block.o

clean:
	rm -rf *.o ${EXECUTABLE}

