CC=		gcc
CFLAGS=		-lraylib -O3 -lm
OUT=		pixab

all: compile strip

compile:
	${CC} -o ${OUT} main.c ${CFLAGS}

strip:
	strip ${OUT}

asm:
	${CC} -S -fverbose-asm main.c ${CFLAGS}
