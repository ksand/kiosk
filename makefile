all: kiosk.o routines.o
	cc -o kiosk kiosk.o routines.o -lncurses

kiosk.o: kiosk.c
	cc -c -Wunused-variable kiosk.c

routines.o: routines.c
	cc -c -Wunused-variable routines.c

clean:
	rm *.o
