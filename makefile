compile:
	gcc -o mapper mapper.c
	gcc -o reducer reducer.c
	gcc -o combiner combiner.c

clean:
	$(RM) mapper
	$(RM) reducer
	$(RM) combiner

run:
	gcc -g -Wall -o mapper mapper.c
	gcc -g -Wall -o reducer reducer.c
	gcc -g -Wall -o combiner combiner.c
	./combiner