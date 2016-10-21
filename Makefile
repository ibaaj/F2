CC=gcc
CFLAGS= -std=c99 -Wall -pedantic -Wextra -Werror -O3 -w

.SUFFIXES: .c .o

PRGS = arithm_test enumerate_irreductible enumerate_primitive f2_poly_test f2_poly_random f2_poly_interface count_irreductible count_primitive
all:\
	$(PRGS)

arithm_test:\
	arithm_test.o arithm.o
	$(CC)  arithm_test.o arithm.o  -o $@

count_irreductible:\
	count_irreductible.o f2_poly.o arithm.o
	$(CC) count_irreductible.o f2_poly.o arithm.o -o $@

count_primitive:\
	count_primitive.o f2_poly.o arithm.o
	$(CC) count_primitive.o f2_poly.o arithm.o -o $@

enumerate_irreductible:\
	enumerate_irreductible.o f2_poly.o  arithm.o
	$(CC) enumerate_irreductible.o  f2_poly.o arithm.o -o $@

enumerate_primitive:\
	enumerate_primitive.o f2_poly.o arithm.o
	$(CC) enumerate_primitive.o  f2_poly.o arithm.o -o $@

f2_poly_test:\
	f2_poly_test.o f2_poly.o arithm.o
	$(CC) f2_poly_test.o f2_poly.o arithm.o -o $@

f2_poly_random:\
	f2_poly_random.o f2_poly.o arithm.o
	$(CC) f2_poly_random.o f2_poly.o arithm.o -o $@

f2_poly_interface:\
	f2_poly_interface.o f2_poly.o arithm.o
	$(CC) f2_poly_interface.o f2_poly.o arithm.o -o $@

.c.o: \
	$*.h $*.c
	@echo $*
	$(CC) $(CFLAGS) -c $<

clean:
	find . -name '*.o' -exec rm -f {} ';'
	find . -name '*~' -exec rm -f {} ';'
	find . -name '#*#' -exec rm -f {} ';'
	find . -name '.#*' -exec rm -f {} ';'
	find . -name 'core' -exec rm -f {} ';'
	find . -name '*.core' -exec rm -f {} ';'
	find . -name '.DS_Store' -exec rm -f {} ';'
	-rm -rf $(PRGS)
