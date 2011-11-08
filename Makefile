CC := gcc
CFLAGS := -Wall -Wextra -g3 -ggdb -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE
LDFLAGS := -lm  -lfl

default: all

instructionparser.c: instructionparser.rl
	ragel -T1 -o instructionparser.c instructionparser.rl

instructionparser.ps: instructionparser.rl
	ragel -Vp instructionparser.rl | dot -Tps -o instructionparser.ps

%.c: %.o
	$(CC) $@ -c -o $^ $(CFLAGS)

all:	reporting.c runcmd.c helper.c rce.o analyze.o pmcma.o pwnage.o aslr_perfs.o instructionparser.o
	cd beaengine/ && :>CMakeCache.txt && cmake . && make
	$(CC) reporting.c -o reporting.o -c $(CFLAGS) -I ./beaengine/include/
	$(CC) runcmd.c -o runcmd.o -c $(CFLAGS) -I ./beaengine/include/
	$(CC) helper.c -o helper.o -c $(CFLAGS)  -I ./beaengine/include/
	$(CC) -w -o pmcma instructionparser.o aslr_perfs.o pwnage.o pmcma.o analyze.o reporting.o runcmd.o rce.o helper.o $(CFLAGS) $(LDFLAGS) -I ./beaengine/include/ ./beaengine/lib/Linux.gnu.Debug/libBeaEngine_s_d.a
	cd shells && make

testcases::
	cd testcases && make
install::
	cp pmcma /usr/bin/
	cp pmcma.1 /usr/share/man/man1/
clean::
	rm helper.o pmcma rce.o runcmd.o reporting.o analyze.o pwnage.o pmcma.o aslr_perfs.o
	rm -rf report-* core
	rm lex.yy.c
	cd shells && make clean

