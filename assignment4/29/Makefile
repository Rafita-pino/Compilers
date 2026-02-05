OBJECTS = calculator.tab.o emitter.o symbol.o init.o error.o main.o lex.yy.o
EXE = infix2postfix
CFLAGS += -Wall -g

$(EXE):	$(OBJECTS)
	gcc $(CFLAGS) -o $(EXE) $(OBJECTS)

calculator.tab.o:	calculator.tab.c calculator.tab.h global.h
	gcc $(CFLAGS) -c calculator.tab.c

calculator.tab.c calculator.tab.h:	calculator.y
	bison -d calculator.y

main.o: 	main.c global.h
	gcc $(CFLAGS) -c main.c

lex.yy.o:	lex.l calculator.tab.h global.h
	flex -o lex.yy.c lex.l 
	gcc $(CFLAGS) -c lex.yy.c -o lex.yy.o

emitter.o:	emitter.c global.h
	gcc $(CFLAGS) -c emitter.c

symbol.o: 	symbol.c global.h
	gcc $(CFLAGS) -c symbol.c

init.o: 	init.c global.h
	gcc $(CFLAGS) -c init.c

error.o: 	error.c global.h
	gcc $(CFLAGS) -c error.c

clean: 
	rm -f $(EXE) $(OBJECTS) 29.tar.gz 29.zip *~