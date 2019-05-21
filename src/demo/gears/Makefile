#
# ARMv7 (arm7hf) Raspberry Pi 3
#

LN = ln -s
MV = mv
RM = -rm -rf

TARGETS = gears

GLUT = -lglut
LLDLIBS = $(GLUT) -lGLU -lGL -lXmu -lXext -lX11 -lm
LDFLAGS = $(LLDLIBS)

SRCS =	gears.c
OBJS =	$(SRCS:.c=.o)

LCOPTS = -I$(TOP)/include -fullwarn
LWOFF = ,813,852,827,826
LDIRT = *~ *.bak *.pure

default : $(TARGETS)

gears : $(OBJS) $(GLUT)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

include $(COMMONRULES)
