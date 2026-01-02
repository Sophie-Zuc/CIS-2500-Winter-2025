zuccoloSophieA1: zuccoloSophieA1.o zuccoloSophieA1Main.o
	gcc zuccoloSophieA1.o zuccoloSophieA1Main.o -lm -o zuccoloSophieA1

zuccoloSophieA1.o: zuccoloSophieA1.c givenA1.h helper.h
	gcc -Wall -std=c99 -c zuccoloSophieA1.c

zuccoloSophieA1Main.o: zuccoloSophieA1Main.c givenA1.h helper.h
	gcc -Wall -std=c99 -c zuccoloSophieA1Main.c

clean:
	rm *.o zuccoloSophieA1
