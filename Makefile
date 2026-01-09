FLAGS	=	-Wall -Wextra -g

composed: composed.o containers.o
	gcc -o composed src/composed.c src/containers.c

composed.o: src/composed.c include/containers.h
	gcc -c src/composed.c

containers.o: src/containers.c include/containers.h
	gcc -c src/containers.c