MAINTAINERCLEANFILES = Makefile.in

noinst_LIBRARIES = libXmd.a

noinst_PROGRAMS = onHelp

libXmd_a_SOURCES = Help.c Menus.c Print.c RegEdit.c AdjView.c

noinst_HEADERS = AdjView.h \
Help.h HelpP.h \
Menus.h \
Print.h PrintP.h \
RegEdit.h RegEditI.h

LDADD = libXmd.a ../../../lib/Xm/libXm.la

AM_CPPFLAGS = -I$(top_builddir)/lib -I$(srcdir)/../../../lib ${X_CFLAGS} 

EXTRA_DIST = Imakefile

