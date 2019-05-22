SOURCES = AdjView.c  Help.c  Menus.c  Print.c  RegEdit.c
OBJECTS = *.o
LDFLAGS = -lXt -lXm -lX11

default:
	gcc -g -c -fPIC $(SOURCES)
	gcc -g $(OBJECTS) -shared -o libXmd.so -lXt -lXm -lX11

clean:
	- rm *.o *.so

