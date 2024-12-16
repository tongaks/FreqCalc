freq-calc: functions.o tui.o xlsx.o
	gcc main.c functions.o tui.o xlsx.o -o freq-calc -lm -lxlsxwriter

functions.o: headers/functions.h src/functions.c
	gcc src/functions.c -c functions.o

tui.o: headers/functions.h src/tui.c
	gcc -c src/tui.c -o tui.o

xlsx.o: headers/functions.h src/xlsx.c
	gcc -c src/xlsx.c -o xlsx.o

clean:
	rm *.o