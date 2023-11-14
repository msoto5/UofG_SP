CFLAGS=-W -Wall -Werror

PROGRAMS=cfcopy collapws genword genword2 lcount lfcopy wcount

all: $(PROGRAMS)

cfcopy: cfcopy.o
	clang -o cfcopy cfcopy.o

collapws: collapws.o
	clang -o collapws collapws.o

genword: genword.o
	clang -o genword genword.o

genword2: genword2.o
	clang -o genword2 genword2.o

lcount: lcount.o
	clang -o lcount lcount.o

lfcopy: lfcopy.o
	clang -o lfcopy lfcopy.o

wcount: wcount.o
	clang -o wcount wcount.o

clean:
	rm -f *.o $(PROGRAMS)
