all: proje
	./proje

proje: main.o project.o
	gcc main.o project.o -o proje

main.o: main.c project.h
	gcc -c main.c

project.o: project.c project.h
	gcc -c project.c