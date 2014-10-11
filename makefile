all: kiosk.o logwrite.o
	cc -o kiosk kiosk.o logwrite.o -lncurses

kiosk.o: kiosk.c
	cc -c -Wunused-variable kiosk.c

logwrite.o: logwrite.c
	cc -c -Wunused-variable logwrite.c

clean:
	rm *.o
