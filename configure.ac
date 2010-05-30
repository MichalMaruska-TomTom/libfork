dnl Process this file with autoconf to create configure.

AC_PREREQ([2.60])

AC_INIT(libfork, 1.3, [https://bugs.freedesktop.org/enter_bug.cgi?product=xorg], libfork)
AM_INIT_AUTOMAKE([foreign dist-bzip2])
AM_MAINTAINER_MODE

# Require xorg-macros: XORG_DEFAULT_OPTIONS
m4_ifndef([XORG_MACROS_VERSION],
          [m4_fatal([must install xorg-macros 1.6 or later before running autoconf/autogen])])
XORG_MACROS_VERSION(1.6)
XORG_DEFAULT_OPTIONS
XORG_WITH_XMLTO(0.0.20)
XORG_WITH_ASCIIDOC(8.4.5)
AM_CONFIG_HEADER(src/config.h)

# Check for progs
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_SED

# Checks for pkg-config packages
PKG_CHECK_MODULES(XI, [xproto >= 7.0.13] [x11 >= 1.2.99.1] [xextproto >= 7.0.3] [xext >= 1.0.99.1] [inputproto >= 1.9.99.902])


XORG_CHECK_MALLOC_ZERO

AC_OUTPUT([Makefile
	   src/Makefile
           fork.pc])

