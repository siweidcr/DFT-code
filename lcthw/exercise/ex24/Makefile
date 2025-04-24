CFLAGS= -Wall -g

ex24 : ex24.o
	cc $(CFLAGS) -DNDEBUG -o ex24 ex24.o
ex24.o : ex24.c dbg.h
	cc $(CFLAGS) -DNDEBUG -c -o ex24.o ex24.c

clean:
	rm -r ex24.o ex24
