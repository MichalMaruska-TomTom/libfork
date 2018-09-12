SUBDIRS = lib src

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = fork.pc

MAINTAINERCLEANFILES = ChangeLog INSTALL


CFLAGS += $(@XI_CFLAGS@)
LDFLAGS += $(@XI_LDFLAGS@) -lX11


.PHONY: ChangeLog INSTALL

INSTALL:
	$(INSTALL_CMD)

ChangeLog:
	$(CHANGELOG_CMD)

dist-hook: ChangeLog INSTALL
