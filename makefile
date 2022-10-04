FLAGS ?= -std=c++11 -Wall -Wextra -Iinclude
ALL = bin/qb-stat-grapher

all: $(ALL)

clean:
	rm -f obj/* bin/*

obj/Quarterback.o: src/Quarterback.cpp include/Quarterback.hpp
	g++ -c $(FLAGS) -o obj/Quarterback.o src/Quarterback.cpp

bin/qb-stat-grapher: src/main.cpp obj/Quarterback.o
	g++ $(FLAGS) -o bin/qb-stat-grapher src/main.cpp obj/Quarterback.o

generate:
	./bin/qb-stat-grapher 2021.csv ./jgraph_files/top_eight_touchdowns.jgr top touchdowns 8
	./jgraph -P ./jgraph_files/top_eight_touchdowns.jgr | ps2pdf - | convert -density 300 - -quality 100 ./image_results/top_eight_touchdowns.jpg
	./bin/qb-stat-grapher 2021.csv ./jgraph_files/bottom_eight_touchdowns.jgr bottom touchdowns 8
	./jgraph -P ./jgraph_files/bottom_eight_touchdowns.jgr | ps2pdf - | convert -density 300 - -quality 100 ./image_results/bottom_eight_touchdowns.jpg
	./bin/qb-stat-grapher 2021.csv ./jgraph_files/top_four_longest.jgr top longest_pass 4
	./jgraph -P ./jgraph_files/top_four_longest.jgr | ps2pdf - | convert -density 300 - -quality 100 ./image_results/top_four_longest.jpg
	./bin/qb-stat-grapher 2021.csv ./jgraph_files/top_four_age.jgr top age 4
	./jgraph -P ./jgraph_files/top_four_age.jgr | ps2pdf - | convert -density 300 - -quality 100 ./image_results/top_four_age.jpg
