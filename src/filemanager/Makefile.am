MAINTAINERCLEANFILES = Makefile.in

bindir = ${prefix}/share/Xm/filemanager
datadir = ${prefix}/share/Xm/filemanager

bin_PROGRAMS = filemanager
filemanager_SOURCES = filemanager.c actions.c readdir.c convert.c \
                      interface.c filemanager.h
EXTRA_DIST = filemanager.man filemanager.help XmdFilemanager.ad \
           Imakefile code.xpm dir.xpm exec.xpm file.xpm none.xpm \
           obj.xpm pix.xpm s_dir.xpm s_exec.xpm s_file.xpm \
           s_none.xpm s_pix.xpm
data_DATA = $(EXTRA_DIST) $(filemanager_SOURCES)
#LDADD = ../../lib/Xmd/libXmd.a ../../../lib/Xm/libXm.la
LDADD = -lXm -lXt -lX11
#AM_CPPFLAGS = -I$(srcdir)/../../lib -I$(srcdir)/../../../lib -I$(top_builddir)/lib ${X_CFLAGS} 

