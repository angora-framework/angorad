bin_PROGRAMS = angorad
angorad_SOURCES = main.gen.c
BUILT_SOURCES = main.gen.c
CLEANFILES = $(BUILT_SOURCES)

$(BUILT_SOURCES): %.gen.c: $(srcdir)/%.c Makefile
	$(CPYC) <$< >$@
