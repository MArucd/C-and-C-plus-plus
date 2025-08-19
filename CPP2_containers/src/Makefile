CC=g++ -std=c++17
CFLAGS=-Wall -Wextra -Werror
TEST_FLAGS=-lgtest -lgtest_main
LIB_NAME=s21_containers


all: clean test

test: 
	$(CC) $(CFLAGS)  array/s21_array_tests.cc list/s21_test_list.cc Map/s21_map_test.cc Multiset/s21_multiset_test.cc queue/s21_test_queue.cc Set/s21_set_test.cc stack/s21_test_stack.cc vector/s21_vector_tests.cc -o test $(TEST_FLAGS)
	./test

clean:
	rm -rf *.o test *.a *.gcno *.gcda *.gcov *.html *.css *.out *.info report/
