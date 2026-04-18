all:
	gcc *.c \
	-std=c99 \
	-o main -g \
	-Wall -pedantic \
	-DGLEW_STATIC \
	-lglew32s -lfreeglut -lglu32 -lopengl32 -lm \
	-Iglew/include/ \
	-Ifreeglut/include \
	-Lglew/lib \
	-Lfreeglut/lib \

linux:
	i686-w64-mingw32-gcc *.c \
	-std=c99 \
	-o main -g \
	-Wall -pedantic \
	-DGLEW_STATIC \
	-lglew32s -lfreeglut -lglu32 -lopengl32 -lm \
	-Iglew/include/ \
	-Ifreeglut/include \
	-Lglew/lib \
	-Lfreeglut/lib \