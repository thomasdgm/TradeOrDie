all:  bin/TradeOrDieTxt bin/TradeOrDie bin/Test

bin/TradeOrDie: obj/mainSDL.o obj/actif.o obj/trader.o obj/simulation.o obj/tradeOrDieSDL.o obj/gestionnaireEvenement.o obj/evenement.o
	g++ obj/mainSDL.o obj/actif.o obj/trader.o obj/simulation.o obj/tradeOrDieSDL.o obj/gestionnaireEvenement.o obj/evenement.o -o bin/TradeOrDie $(shell sdl2-config --libs) -lSDL2 -lSDL2_image -lSDL2_ttf

bin/TradeOrDieTxt: obj/mainTxt.o obj/actif.o obj/trader.o obj/simulation.o obj/tradeOrDieTxt.o obj/gestionnaireEvenement.o obj/evenement.o
	g++ obj/mainTxt.o obj/actif.o obj/trader.o obj/simulation.o obj/tradeOrDieTxt.o obj/gestionnaireEvenement.o obj/evenement.o -o bin/TradeOrDieTxt

bin/Test: obj/mainTest.o obj/actif.o obj/trader.o obj/simulation.o obj/tradeOrDieTxt.o obj/tradeOrDieSDL.o obj/gestionnaireEvenement.o obj/evenement.o
	g++ obj/mainTest.o obj/actif.o obj/trader.o obj/simulation.o obj/tradeOrDieTxt.o obj/tradeOrDieSDL.o obj/gestionnaireEvenement.o obj/evenement.o -o bin/Test $(shell sdl2-config --libs) -lSDL2 -lSDL2_image -lSDL2_ttf

obj/mainSDL.o: src/mainSDL.cpp src/actif.h src/trader.h src/simulation.h src/TradeOrDieSDL.h src/gestionnaireEvenement.h src/evenement.h
	g++ -g -Wall -c src/mainSDL.cpp -o obj/mainSDL.o $(shell sdl2-config --cflags) -I/usr/include/SDL2

obj/mainTxt.o: src/mainTxt.cpp src/actif.h src/trader.h src/simulation.h src/TradeOrDieTxt.h src/gestionnaireEvenement.h src/evenement.h
	g++ -g -Wall -c src/mainTxt.cpp -o obj/mainTxt.o

obj/mainTest.o: src/mainTest.cpp src/actif.h src/trader.h src/simulation.h src/gestionnaireEvenement.h src/evenement.h
	g++ -g -Wall -c src/mainTest.cpp -o obj/mainTest.o $(shell sdl2-config --cflags) -I/usr/include/SDL2

obj/tradeOrDieSDL.o: src/TradeOrDieSDL.cpp src/TradeOrDieSDL.h 
	g++ -g -Wall -c src/TradeOrDieSDL.cpp -o obj/tradeOrDieSDL.o $(shell sdl2-config --cflags) -I/usr/include/SDL2

obj/tradeOrDieTxt.o: src/TradeOrDieTxt.cpp src/TradeOrDieTxt.h
	g++ -g -Wall -c src/TradeOrDieTxt.cpp -o obj/tradeOrDieTxt.o

obj/simulation.o: src/simulation.cpp src/simulation.h src/evenement.h src/gestionnaireEvenement.h
	g++ -g -Wall -c src/simulation.cpp -o obj/simulation.o

obj/trader.o: src/trader.cpp src/trader.h
	g++ -g -Wall -c src/trader.cpp -o obj/trader.o 

obj/actif.o: src/actif.cpp src/actif.h
	g++ -g -Wall -c src/actif.cpp -o obj/actif.o 

obj/gestionnaireEvenement.o: src/gestionnaireEvenement.cpp src/gestionnaireEvenement.h src/evenement.h
	g++ -g -Wall -c src/gestionnaireEvenement.cpp -o obj/gestionnaireEvenement.o

obj/evenement.o: src/evenement.cpp src/evenement.h
	g++ -g -Wall -c src/evenement.cpp -o obj/evenement.o


doc :
	doxygen doc/Doxyfile


clean:
	rm -f obj/*.o bin/*
	rm -rf doc/html

.PHONY: all doc
