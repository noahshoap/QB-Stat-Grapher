FLAGS ?= -std=c++11 -Wall -Wextra -Iinclude
ALL = bin/qb-graph-generator

all: $(ALL)

clean:
	rm -f obj/* bin/*

bin/qb-stat-grapher: src/main.cpp include/Quarterback.hpp
	g++ $(FLAGS) -o bin/qb-stat-grapher src/main.cpp