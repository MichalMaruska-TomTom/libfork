bin_PROGRAMS = forkto

forkto_SOURCES = fork-to.c

AM_CFLAGS = -I$(top_srcdir)/include \
	    $(XI_CFLAGS) \
	    $(MALLOC_ZERO_CFLAGS) \
	    $(CWARNFLAGS)

forkto_LDFLAGS = -no-undefined -lX11 -L../lib/ -lfork

EXTRA_DIST =
