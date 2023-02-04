# <In terms of Make, a phony target is simply a target that is always out-of-date, 
# so whenever you ask make <phony_target>, it will run, independent from the state
# of the file system>
#.PHONY clean
OS := $(shell uname -s)
ifeq ($(OS), Linux)
	CC = clang++
else
	CC = gcc
endif
CFLAGS = -Wall -Wextra -Werror -std=c++17
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
LIBS = -lgtest -lpthread

MAIN_FILE = s21_matrix.cpp
TESTS_FILE = unit_tests.cpp


test:
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $(MAIN_FILE) $(TESTS_FILE) -o test.out $(LIBS)
	./test.out

#--no-external flag is for not include any files, except our src
gcov_report: test
	lcov -t "./test" -o test.info --no-external -c -d ./
	genhtml -o report test.info
	open report/index.html

clean:
	rm *.gcno
	rm *.gcda
	rm *.out
	rm *.info
	rm -rf report
