FLAGS ?= -std=c++11 -Wall -Wextra -Iinclude
ALL = bin/qb-stat-grapher

all: $(ALL)

clean:
	rm -f obj/* bin/*

obj/Quarterback.o: src/Quarterback.cpp include/Quarterback.hpp
	g++ -c $(FLAGS) -o obj/Quarterback.o src/Quarterback.cpp

bin/qb-stat-grapher: src/main.cpp obj/Quarterback.o
	g++ $(FLAGS) -o bin/qb-stat-grapher src/main.cpp obj/Quarterback.o