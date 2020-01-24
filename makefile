all:
	gcc -o mapper mapper.c
	gcc -o reducer reducer.c
	gcc -o combiner combiner.c

mapper:
	gcc -o mapper mapper.c
reducer:
	gcc -o reducer reducer.c
combiner:
	gcc -o combiner combiner.c

clean:
	$(RM) mapper
	$(RM) reducer
	$(RM) combiner

run:
	gcc -o mapper mapper.c
	gcc -o reducer reducer.c
	gcc -o combiner combiner.c
	./combiner