GCC_FLAGS= -Wall -Wextra -Werror -std=c11
VG_FLAGS= --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=vgres.log
LDFLAGS= $(shell pkg-config --cflags --libs check) -lm

all: s21_3DViewer.a install

s21_3DViewer.a: clean
	gcc ${GCC_FLAGS} -c -g *.c
	ar rc s21_3DViewer.a *.o
	ranlib s21_3DViewer.a
	rm -rf *.o

install:
	mkdir -p build/
	cd build/ && qmake6 ../s21_3DViewer/s21_3DViewer.pro && make

test: clean s21_3DViewer.a
	gcc -g ${GCC_FLAGS} c_tests/*.c file_parser.c affine.c s21_3DViewer.a -o tests ${LDFLAGS}
	./tests

valgrind: clean s21_3DViewer.a
	gcc -g ${GCC_FLAGS} c_tests/*.c s21_3DViewer.a -o tests ${LDFLAGS}
	valgrind ${VG_FLAGS} ./tests

gcov_report: s21_3DViewer.a
	gcc -g ${GCC_FLAGS} --coverage c_tests/*.c file_parser.c affine.c ${LDFLAGS} -o run_test
	./run_test
	lcov -t "tests_coverage" --no-external -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

dist:
	mkdir Archive_3DViewer_v1.0
	cp Makefile *.c *.h -R c_tests -R models -R s21_3DViewer -R documentation Archive_3DViewer_v1.0/
	tar cvzf Archive_3DViewer_v1.0.tgz Archive_3DViewer_v1.0/
	rm -rf Archive_3DViewer_v1.0

dvi: 
	#open documentation/readme.dvi
	open documentation/readme.pdf

style_check:
	clang-format --style=Google -n *.c *.h c_tests/*.c c_tests/*.h s21_3DViewer/*.cpp s21_3DViewer/*.h

style_set:
	clang-format --style=Google -i *.c *.h c_tests/*.c c_tests/*.h s21_3DViewer/*.cpp s21_3DViewer/*.h

uninstall:
	rm -rf build/

clean:
	rm -rf tests run_test* *.o *.a vgres.log report* *info *.g* tests.dSYM *.out* *.log

rebuild: clean all
