bin_PROGRAMS = angorad
BUILT_SOURCES = \
	config/cmd_options.gen.c \
	main.gen.c
angorad_SOURCES = $(BUILT_SOURCES)
CLEANFILES = $(BUILT_SOURCES)
AM_CFLAGS = -DSYSCONF_DIR='"$(sysconfdir)"'

$(BUILT_SOURCES): %.gen.c: $(srcdir)/%.c Makefile
	$(CPYC) <$< >$@
