freq-calc: functions.o tui.o
	gcc main.c functions.o tui.o -o freq-calc -lm

functions.o: headers/functions.h src/functions.c
	gcc src/functions.c -c functions.o

tui.o: headers/functions.h src/tui.c
	gcc -c src/tui.c -o tui.o

clean:
	rm *.o