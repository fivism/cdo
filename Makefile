CC=gcc
CLFAG=-Wall -Wextra -Wpedantic -std=c11

cdo: cdo.c cdofunc.c
	$(CC) $(CFLAGS) $^ -o $@

clean: 
	rm -f cdo
	rm -f .cdo_dat
