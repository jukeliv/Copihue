@echo off

REM TODO: PORT THIS TO CUILD ( ALSO UPDATE CUILD )

g++ -c src/utility.cpp -o obj/utility.o

g++ -c src/token.cpp -o obj/token.o

g++ -c src/assembler.cpp -o obj/assembler.o

g++ -c src/main.cpp -o obj/main.o

g++ obj/utility.o obj/token.o obj/assembler.o obj/main.o -o Copihue.exe -O3