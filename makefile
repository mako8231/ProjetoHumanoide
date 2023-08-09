all:
	gcc *.c *.h  -lGL -lglut -lGLU -o main.out && ./main.out
