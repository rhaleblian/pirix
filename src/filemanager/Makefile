SOURCES = actions.c \
convert.c \
filemanager.c \
interface.c \
readdir.c
OBJECTS = *.o
CFLAGS = -I.. -g
LDFLAGS = -L../Xmd -lX11 -lXm -lXt -lXmd

filemanager: $(SOURCES)
	gcc $(CFLAGS) $(SOURCES) -o filemanager $(LDFLAGS)

test: filemanager
	LD_LIBRARY_PATH=../Xmd gdb ./filemanager

clean:
	- rm filemanager *.o

