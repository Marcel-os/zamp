__start__: obj ../libs/Interp4Move.so obj ../libs/Interp4Rotate.so ../libs/Interp4Set.so ../libs/Interp4Pause.so 
	@echo "  Tworzenie wtyczek: Move, Rotate, Set, Pause zostalo zakonczone."
	@echo

obj:
	mkdir obj

CPPFLAGS=-Wall -fPIC -pedantic -std=c++11 -Iinc -I../inc
LDFLAGS=-Wall -shared


../libs/Interp4Move.so: obj/Interp4Move.o
	g++ ${LDFLAGS} -o ../libs/Interp4Move.so obj/Interp4Move.o
	@echo
	@echo "  Wtyczka dla polecenia 'Move' zostala utworzona."
	@echo

obj/Interp4Move.o: src/Interp4Move.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Move.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Move.o src/Interp4Move.cpp



../libs/Interp4Rotate.so: obj/Interp4Rotate.o
	g++ ${LDFLAGS} -o ../libs/Interp4Rotate.so obj/Interp4Rotate.o
	@echo
	@echo "  Wtyczka dla polecenia 'Rotate' zostala utworzona."
	@echo

obj/Interp4Rotate.o: src/Interp4Rotate.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Rotate.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Rotate.o src/Interp4Rotate.cpp



../libs/Interp4Set.so: obj/Interp4Set.o
	g++ ${LDFLAGS} -o ../libs/Interp4Set.so obj/Interp4Set.o
	@echo
	@echo "  Wtyczka dla polecenia 'Set' zostala utworzona."
	@echo

obj/Interp4Set.o: src/Interp4Set.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Set.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Set.o src/Interp4Set.cpp



../libs/Interp4Pause.so: obj/Interp4Pause.o
	g++ ${LDFLAGS} -o ../libs/Interp4Pause.so obj/Interp4Pause.o
	@echo
	@echo "  Wtyczka dla polecenia 'Pause' zostala utworzona."
	@echo

obj/Interp4Pause.o: src/Interp4Pause.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Pause.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Pause.o src/Interp4Pause.cpp


clean:
	rm -f obj/*

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
