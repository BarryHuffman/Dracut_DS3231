
dracutdir = @DRACUTDIR@/modules.d/99lcdbootmsg

dracut_DATA = module-setup.sh

EXTRA_DIST = $(DATA)

install-data-hook:
	chmod 755 $(DESTDIR)$(dracutdir)/module-setup.sh
