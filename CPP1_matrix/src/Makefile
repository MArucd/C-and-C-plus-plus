CC = g++ -std=c++14
# -Wall -Werror -Wextra -g #-fsanitize=address
COVFLAGS = -fprofile-arcs -lcheck 
# -ftest-coverage

all: s21_matrix_oop.a

gcov_report: test
	gcov -f *.gcda
	lcov -t "test" -o test.info -c -d . --rc lcov_branch_coverage=0
	genhtml -o report test.info  --rc lcov_branch_coverage=0
	open report/index.html

test: s21_matrix_oop.a
		$(CC) -c test.cc 
		$(CC) --coverage -o test.out test.o -lgtest -lgtest_main -L. s21_matrix_oop.a
		./test.out

s21_matrix_oop.a: s21_matrix_oop.o
		ar rc s21_matrix_oop.a s21_matrix_oop.o
		ranlib s21_matrix_oop.a

s21_matrix_oop.o:
		$(CC) -c $(COVFLAGS) s21_matrix_oop.cc

mytest: s21_matrix_oop.a
		$(CC) -c mytest.cc 
		$(CC) --coverage -o mytest.out mytest.o s21_matrix_oop.a
		./mytest.out

leaks: clean test
		leaks -atExit -- ./test.out

cppcheck:
		cppcheck --enable=all --suppress=missingIncludeSystem *.cc

style:
		@cp ../materials/linters/.clang-format .
		clang-format -n *.cc *.h
		@rm -rf .clang-format

clean:
		@rm -rf *.out *.o *.a *.gcov *.gcda *.gcno *.info report