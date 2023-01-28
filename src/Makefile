# <In terms of Make, a phony target is simply a target that is always out-of-date, 
# so whenever you ask make <phony_target>, it will run, independent from the state
# of the file system>
#.PHONY clean

test: clean
	g++ -fprofile-arcs -ftest-coverage -Wall -Wextra -Werror -std=c++17 s21_matrix.cpp unit_tests.cpp -o test.out -lgtest -lpthread
	./test.out

clean:
	rm *.gcno
	rm *.out
