all: crystal

crystal:crystal.c
	gcc -g -Wall -o $@ $<

clean:
	rm crystal

