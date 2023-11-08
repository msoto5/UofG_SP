TXT_FILES := $(wildcard *.txt)		# All .txt files
OUT_FILES := $(TXT_FILES:.txt=.out)	# All .out files

all: $(OUT_FILES)

tldmonitor: tldmonitor.o date.o tldlist.o
	clang -Wall -Werror -o tldmonitor tldmonitor.o date.o tldlist.o

date.o: date.h date.c
	clang -Wall -Werror -o date.o -c date.c

tldlist.o: tldlist.h tldlist.c
	clang -Wall -Werror -o tldlist.o -c tldlist.c

tldmonitor.o: tldmonitor.c date.h tldlist.h
	clang -Wall -Werror -o tldmonitor.o -c tldmonitor.c

clean:
	rm -f *.o tldmonitor

%.out: %.txt tldmonitor
    ./tldmonitor 01/01/2000 01/09/2020 < $< | sort -n | diff - $@