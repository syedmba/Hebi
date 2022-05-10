# Makefile
# Created on 9 May 2022 by S M Bin Asif

FLAGS = -pedantic-errors -std=c++11

LDFLAGS = -l ncurses -o $@

game.o: game.cpp game.h
	g++ $(FLAGS) -c $<

main.o: main.cpp game.h
	g++ $(FLAGS) -c $<

main: main.o game.o
	g++ $(LDFLAGS) main.o game.o

clean:
	rm -f game game.o walk.o battle.o skeletonart.o printterrain.o npcdialogueone.o inventory.o nextarea.o game.tgz

.PHONY: clean


# nextarea.o: nextarea.cpp nextarea.h
# 	g++ $(FLAGS) -c $<

# inventory.o: inventory.cpp inventory.h
# 	g++ $(FLAGS) -c $<

# skeletonart.o: skeletonart.cpp skeletonart.h
# 	g++ $(FLAGS) -c $<

# npcdialogueone.o: npcdialogueone.cpp npcdialogueone.h
# 	g++ $(FLAGS) -c $<

# battle.o: battle.cpp battle.h skeletonart.h
# 	g++ $(FLAGS) -c $<

# walk.o: walk.cpp walk.h printterrain.h battle.h skeletonart.h npcdialogueone.h inventory.h nextarea.o
# 	g++ $(FLAGS) -c $<

# printterrain.o: printterrain.cpp printterrain.h
# 	g++ $(FLAGS) -c $<

# game.o: game.cpp walk.h printterrain.h battle.h skeletonart.h npcdialogueone.h inventory.h nextarea.h
# 	g++ $(FLAGS) -c $<

# game: game.o walk.o printterrain.o battle.o skeletonart.o npcdialogueone.o inventory.o nextarea.o
# 	g++ $(FLAGS) $^ -o $@



