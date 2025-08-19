CC = gcc
CFLAGS = -Wall -Werror -Wextra

LIB = ./Lib/*.c 
OBJECTS = *.o 
TEST = test.c 

CLANG_PATH = ../materials/linters/
CLANG_COPY = cp $(CLANG_PATH).clang-format .clang-format

OS = $(shell uname)

ifeq ($(OS), Darwin)
 	TEST_FLAGS = -lcheck
	OPEN_CMD = open
else
 	TEST_FLAGS = -lcheck -lsubunit -lrt -lpthread -lm
	OPEN_CMD = xdg-open
endif

.LIFE: all clean rebuild

all: s21_matrix.a test gcov_report

clean:
	rm -rf $(OBJECTS) *.a *.gch *.gcda *.gcno *.info report test .clang-format

test: s21_matrix.a
	$(CC) $(CFLAGS) $(LIB) $(TEST) ./s21_matrix.a $(TEST_FLAGS) -o test
	./test

s21_matrix.a: s21_matrix.o
	ar r s21_matrix.a $(OBJECTS)

s21_matrix.o:
	$(CC) $(CFLAGS) ./s21_matrix.h $(LIB) -c

gcov_report:
	$(CC) $(CFLAGS) --coverage $(TEST) $(LIB) -L. s21_matrix.a $(TEST_FLAGS) -o test
	./test
	lcov -t "test" -o tests.info -c -d .
	genhtml -o report tests.info
	$(OPEN_CMD) ./report/index.html

brew:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

rebuild:
	$(MAKE) clean
	$(MAKE) all

clang:
	$(CLANG_COPY) && clang-format -n ./Lib/*.c *.c *.h
	$(CLANG_COPY) && clang-format -i ./Lib/*.c *.c *.h

verter:
	cd ../materials/build && sh run.sh
	cd ../../


