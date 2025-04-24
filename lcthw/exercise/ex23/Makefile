CFLAGS= -Wall -g

ex23 : ex23.o
	cc $(CFLAGS) -DNDEBUG -o ex23 ex23.o
ex23.o : ex23.c dbg.h
	cc $(CFLAGS) -DNDEBUG -c -o ex23.o ex23.c

clean:
	rm -r ex23.o ex23
