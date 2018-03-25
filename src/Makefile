all: tunit punit bunit C-app-test

tunit: trnslist.h trnslist.c tlist-test-unit.c
	gcc trnslist.c tlist-test-unit.c -o tunit

punit: puzzle.h puzzle.c puzzle-test-unit.c
	gcc puzzle.c puzzle-test-unit.c sha1/sha1.c -o punit

bunit: puzzle.h puzzle.c trnslist.h trnslist.c block.h block.c block-test-unit.c
	gcc puzzle.c trnslist.c block.c block-test-unit.c sha1/sha1.c -o bunit

C-app-test: puzzle.h puzzle.c trnslist.h trnslist.c block.h block.c blockchain.h blockchain.c
	gcc puzzle.c trnslist.c block.c blockchain.c sha1/sha1.c -o C-app-test

clean:
	@rm -f *.o tunit punit bunit C-app-test