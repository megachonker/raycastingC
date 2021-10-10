LDLIBS=-lUwU -lSDL2 -lSDL2_ttf -lm

compile: main.c
	echo "comiling	..."
	gcc	main.c -o main -g $(LDLIBS)
exec:	main
	echo "executing	..."
	./main
clean: 
	echo "cleaning	..."
	rm main
run: compile exec clean
	echo finish	...