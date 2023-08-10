all:
	gcc *.c *.h  -lGL -lglut -lGLU -lm -o main.out && ./main.out
