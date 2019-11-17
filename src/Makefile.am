bin_PROGRAMS = lcdcontrol
sbin_PROGRAMS = lcdnetmon
lcdcontrol_CFLAGS = @CFLAGS_CHECKS@ @CFLAGS_WARNINGS@ -I $(top_srcdir)/lib
lcdcontrol_LDADD = @LDFLAGS_CHECKS@ @LDFLAGS_WARNINGS@ $(top_builddir)/lib/librpi-lcd.la

lcdnetmon_CFLAGS = @CFLAGS_CHECKS@ @CFLAGS_WARNINGS@ -I $(top_srcdir)/lib
lcdnetmon_LDADD = @LDFLAGS_CHECKS@ @LDFLAGS_WARNINGS@ $(top_builddir)/lib/librpi-lcd.la -leconf

CLEANFILES = lcdcontrol lcdnetmon
