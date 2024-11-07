CC= gcc -std=c11
CFLAGS= -Wall -Wextra -Werror
CAT= s21_cat.c

all: s21_cat

s21_cat:
	$(CC) $(CFLAGS) $(CAT) -o s21_cat

test1:
	chmod 777 test.sh 
	./test.sh
Test2:
	chmod 777 t_cat.sh
	,/t_cat.sh

clean:
	rm -rf s21_cat
	rm -rf *.a *.out *.o *.dSYM

check:
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extension=c *.c *.h