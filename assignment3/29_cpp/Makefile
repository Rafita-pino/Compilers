OBJECTS = lexer.o calculator.tab.o emitter.o symbol.o init.o error.o main.o
EXE = infix2postfix
CFLAGS += -Wall -g

$(EXE):	$(OBJECTS)
	g++ $(CFLAGS) -o $(EXE) $(OBJECTS)

calculator.tab.o: calculator.tab.cpp calculator.tab.hpp global.h
	g++ $(CFLAGS) -c calculator.tab.cpp

calculator.tab.cpp calculator.tab.hpp: calculator.ypp
	bison -d calculator.ypp

main.o: 	main.cpp global.h
	g++ $(CFLAGS) -c main.cpp

lexer.o:	lexer.cpp calculator.tab.hpp global.h
	g++ $(CFLAGS) -c lexer.cpp

emitter.o: 	emitter.cpp global.h
	g++ $(CFLAGS) -c emitter.cpp

symbol.o: 	symbol.cpp global.h
	g++ $(CFLAGS) -c symbol.cpp

init.o: 	init.cpp global.h
	g++ $(CFLAGS) -c init.cpp

error.o: 	error.cpp global.h
	g++ $(CFLAGS) -c error.cpp

clean: 
	rm -f $(EXE) $(OBJECTS) 29.tar.gz 29.zip *~

archives: clean
	cd ..; rm 29.tar 29.zip 29/29.tar 29/29.zip; tar -cvf 29.tar 29; gzip -9 29.tar; zip -r 29.zip 29; mv 29.zip 29/29.zip; mv 29.tar.gz 29/29.tar.gz
