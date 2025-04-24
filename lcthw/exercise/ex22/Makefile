CFLAGS= -Wall -g

ex22_main : ex22.o ex22_main.o
	cc $(CFLAGS) -DNDEBUG -o ex22_main ex22_main.o ex22.o
ex22_main.o : ex22_main.c ex22.h dbg.h
	cc $(CFLAGS) -DNDEBUG -c -o ex22_main.o ex22_main.c
ex22.o : ex22.c ex22.h dbg.h
	cc $(CFLAGS) -c -o ex22.o ex22.c

clean:
	rm -r ex22.o ex22_main.o ex22_main
