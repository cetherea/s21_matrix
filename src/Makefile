CC = gcc
CFLAGS =  -Wall -Werror -Wextra -std=c11

TARGET = s21_matrix.a

OBJ = core/s21_create_matrix.o core/s21_remove_matrix.o comparison/s21_eq_matrix.o

CHECK_LIBS = -lcheck -lsubunit -lm -lpthread

GCOV_FLAGS = -fprofile-arcs -ftest-coverage

all: $(TARGET)

$(TARGET): $(OBJ)
	ar rcs $(TARGET) $(OBJ)


core/s21_create_matrix.o: core/s21_create_matrix.c
	$(CC) $(CFLAGS) -c core/s21_create_matrix.c -o core/s21_create_matrix.o

core/s21_remove_matrix.o: core/s21_remove_matrix.c
	$(CC) $(CFLAGS) -c core/s21_remove_matrix.c -o core/s21_remove_matrix.o

comparison/s21_eq_matrix.o: comparison/s21_eq_matrix.c
	$(CC) $(CFLAGS) -c comparison/s21_eq_matrix.c -o comparison/s21_eq_matrix.o



test : clean $(TARGET)
	$(CC) $(CFLAGS) tests/s21_runner.c tests/core/s21_remove_matrix_test.c tests/core/s21_create_matrix_test.c tests/comparison/s21_eq_matrix_test.c $(TARGET) $(CHECK_LIBS) -o test
	./test


gcov_report: clean
	$(CC) $(CFLAGS) $(GCOV_FLAGS) tests/core/s21_create_matrix_test.c tests/s21_runner.c core/s21_create_matrix.c tests/core/s21_remove_matrix_test.c core/s21_remove_matrix.c  tests/comparison/s21_eq_matrix_test.c comparison/s21_eq_matrix.c $(CHECK_LIBS) -o test_gcov
	./test_gcov
	lcov --capture --directory . --base-directory . --output-file coverage.info --no-external --ignore-errors inconsistent
	genhtml coverage.info --output-directory report --ignore-errors source


style:
	clang-format -i  core/*.c tests/*.c tests/core/*.c


clean:
	rm -f $(TARGET) test test_gcov coverage.info
	rm -f core/*.o comparison/*.o
	rm -f core/*.gcda core/*.gcno comparison/*.gcda comparison/*.gcno *.gcda *.gcno
	rm -rf report


.PHONY: all test clean gcov_report styl