all: main

main: main.o draw.o animate.o levels.o
	g++ -L/usr/local/lib -Wall main.o draw.o levels.o animate.o -o main -lalleg

main.o: main.c
	g++ -c main.c

draw.o: draw.c
	g++ -c draw.c

animate.o: animate.c
	g++ -c animate.c

levels.o: levels.c
	g++ -c levels.c


clean:
	rm -rf *o main
