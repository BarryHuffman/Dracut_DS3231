lib_LTLIBRARIES = librpi-lcd.la
librpi_lcd_la_SOURCES = rpi-lcd.c
librpi_lcd_la_CFLAGS = -D_REENTRANT=1 @CFLAGS_CHECKS@ @CFLAGS_WARNINGS@
librpi_lcd_la_CPPFLAGS = -I$(top_srcdir)/lib
librpi_lcd_la_LDFLAGS = @LDFLAGS_CHECKS@ @CFLAGS_WARNINGS@ \
	-version-info 0:0:0 -Wl,--no-undefined
#	-Wl,--version-script=$(top_srcdir)/lib/librpi-lcd.map

include_HEADERS = rpi-lcd.h

CLEANFILES = *~
DISTCLEANFILES = *.pc
#EXTRA_DIST = librpi-lcd.map
pkgconfig_DATA = librpi-lcd.pc
