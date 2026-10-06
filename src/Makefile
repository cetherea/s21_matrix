CC = gcc
CFLAGS =  -Wall -Werror -Wextra -std=c11

TARGET = s21_matrix.a

OBJ = core/s21_create_matrix.o core/s21_remove_matrix.o comparison/s21_eq_matrix.o opyration/s21_sum_matrix.o opyration/s21_sub_matrix.o

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

opyration/s21_sum_matrix.o: opyration/s21_sum_matrix.c
	$(CC) $(CFLAGS) -c opyration/s21_sum_matrix.c -o opyration/s21_sum_matrix.o

opyration/s21_sub_matrix.o: opyration/s21_sub_matrix.c
	$(CC) $(CFLAGS) -c opyration/s21_sub_matrix.c -o opyration/s21_sub_matrix.o

test : clean $(TARGET)
	$(CC) $(CFLAGS) tests/s21_runner.c tests/core/s21_remove_matrix_test.c tests/core/s21_create_matrix_test.c tests/comparison/s21_eq_matrix_test.c tests/opyration/s21_sum_matrix_test.c tests/opyration/s21_sub_matrix_test.c  $(TARGET) $(CHECK_LIBS) -o test
	./test


gcov_report: clean
	$(CC) $(CFLAGS) $(GCOV_FLAGS) tests/core/s21_create_matrix_test.c tests/s21_runner.c core/s21_create_matrix.c tests/core/s21_remove_matrix_test.c core/s21_remove_matrix.c  tests/comparison/s21_eq_matrix_test.c comparison/s21_eq_matrix.c tests/opyration/s21_sum_matrix_test.c opyration/s21_sum_matrix.c tests/opyration/s21_sub_matrix_test.c opyration/s21_sub_matrix.c $(CHECK_LIBS) -o test_gcov
	./test_gcov
	lcov --capture --directory . --base-directory . --output-file coverage.info --no-external --ignore-errors inconsistent
	genhtml coverage.info --output-directory report --ignore-errors source


style:
	clang-format -i  core/*.c tests/*.c tests/core/*.c tests/opyration/*.c opyration/*.c tests/comparison/*.c comparison/*.c


clean:
	rm -f $(TARGET) test test_gcov coverage.info
	rm -f core/*.o comparison/*.o opyration/s21_sum_matrix.o
	rm -f core/*.gcda core/*.gcno comparison/*.gcda comparison/*.gcno opyration/*.gcda cpyration/*.gcno *.gcda *.gcno
	rm -rf report


.PHONY: all test clean gcov_report style