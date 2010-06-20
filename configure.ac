dnl Process this file with autoconf to create configure.

AC_PREREQ([2.60])

AC_INIT(libfork, 1.3, [https://bugs.freedesktop.org/enter_bug.cgi?product=xorg], libfork)
AM_INIT_AUTOMAKE([foreign dist-bzip2])
AM_MAINTAINER_MODE

# Require xorg-macros: XORG_DEFAULT_OPTIONS
m4_ifndef([XORG_MACROS_VERSION],
          [m4_fatal([must install xorg-macros 1.5 or later before running autoconf/autogen])])
XORG_MACROS_VERSION(1.5)
XORG_DEFAULT_OPTIONS

# Check for progs
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_SED

# Checks for pkg-config packages
PKG_CHECK_MODULES(libfork, [kbproto >= 1.0.4] [x11 >= 1.2.99.1])

AC_OUTPUT([Makefile
	   src/Makefile
           fork.pc])

