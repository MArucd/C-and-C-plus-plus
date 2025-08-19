TEST_FLAGS= -lgtest_main -pthread -lgtest
GCC= g++ -Wall -Wextra -Werror -std=c++17
GCO= --coverage
GTEST_INCLUDE= -I/usr/src/googletest/googletest/include
GTEST_LIBS= -L/usr/local/lib
SRC_DIR := .
EXTENSIONS := cc cpp h

find_files = $(foreach ext,$(EXTENSIONS),$(wildcard $(1)/*.$(ext))) $(foreach d,$(wildcard $(1)/*),$(call find_files,$(d)))
SRC_FILES := $(call find_files,$(SRC_DIR))


CC_FILES := $(filter-out ./gui/desktop/main.cc ./gui/desktop/SnakeView.cc, $(filter %.cc,$(SRC_FILES)))

RM_RULE= rm -rf main test *.dSYM report res *.info *.gcda *.gcno snake_game

UNAME := $(shell uname -s)

FILES= $(wildcard *.cc)
OBJ=$(patsubst %.cc,%.o,${FILES})

all: install tests dvi run_desktop

install:
	mkdir ../build
	cp -rf images ../build
	cd ../build && cmake ../ && make

.PHONY : install

uninstall:
	rm -rf ../build

.PHONY : uninstall

desktop: clean
	mkdir ../build
	cp -rf images ../build
	cd ../build && cmake ../ && make desktopBrickGame && ./desktopBrickGame

.PHONY : desktop

run_desktop:
	cd ../build && ./desktopBrickGame

.PHONY : run_desktop

cli: clean
	mkdir ../build
	cp -rf images ../build
	cd ../build && cmake ../ && make consoleBrickGame

.PHONY : cli

run_cli:
	cd ../build && ./consoleBrickGame

.PHONY : run_cli

tests:
	clear
	$(GCC) $(TEST_FLAGS) -g -o test tests/test_snake.cc tests/test_tetris.cc brick_game/snake/SnakeModel.cc brick_game/tetris/TetrisModel.cc brick_game/tetris/Tetromino.cc
	./test

.PHONY : tests

test_docker:
	$(GCC) -Wno-sign-compare $(GTEST_INCLUDE) $(GTEST_LIBS) ./tests/*.cc brick_game/snake/SnakeModel.cc brick_game/tetris/TetrisModel.cc brick_game/tetris/Tetromino.cc $(TEST_FLAGS) -o s21_tests

.PHONY : test_docker
clean:
	$(RM_RULE)
	rm -rf ../build ../BrickGames ../BrickGames.tgz coverage_report SnakeScore.txt TetrisScore.txt
	make style
	clear

.PHONY : clean

dvi:
	open ./dvi/dvi.pdf

.PHONY : dvi

dist: install
	mkdir -p BrickGames
	touch BrickGames/Makefile
	echo ".PHONY: all dvi \nall: dvi run_desktop\nrun_cli:\n\tcd build && ./consoleBrickGame\n\nrun_desktop:\n\tcd build && ./desktopBrickGame\ndvi:\n\topen dvi/dvi.pdf" >> BrickGames/Makefile
	cp -R ../build ./dvi images BrickGames/
	tar cvzf BrickGames.tgz BrickGames/
	mv BrickGames.tgz ../
	rm -rf BrickGames/

.PHONY : dist


gcov_report:
	$(GCC) --coverage tests/test_snake.cc tests/test_tetris.cc brick_game/snake/SnakeModel.cc brick_game/tetris/TetrisModel.cc brick_game/tetris/Tetromino.cc $(TEST_FLAGS) -o report.out
	./report.out
	lcov -t "report" -o report.info --ignore-errors mismatch --no-external -c -d .
	genhtml -o ./report report.info
	rm -rf *.gcda *.gcno *.info *.out
	xdg-open report/index.html
.PHONY : gcov_report

style:
	@cp ../materials/linters/.clang-format .
	clang-format -n $(SRC_FILES)
	clang-format -i $(SRC_FILES)
	@rm -rf .clang-format

.PHONY : style