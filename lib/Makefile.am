lib_LTLIBRARIES = libfork.la

fork_sources = fork.c

libfork_la_SOURCES = $(fork_sources)


libfork_la_LIBADD = $(fork_LIBS)

AM_CFLAGS = -I$(top_srcdir)/include \
	    -I$(top_srcdir)/include/X11 \
	    -I$(top_srcdir)/include/X11/extensions \
	    $(XI_CFLAGS) \
	    $(MALLOC_ZERO_CFLAGS) \
	    $(CWARNFLAGS)

#AM_LDFLAGS = -lX11


libfork_la_LDFLAGS = -version-number 6:1:0 -no-undefined -lX11

libforkincludedir = $(includedir)/X11/extensions
libforkinclude_HEADERS = $(top_srcdir)/include/fork.h

EXTRA_DIST =
