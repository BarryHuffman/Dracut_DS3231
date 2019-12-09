
systemd_systemdir = @SYSTEMDDIR@/system
systemd_shutdowndir = @SYSTEMDDIR@/system-shutdown

systemd_system_DATA = lcdnetmon.service lcdbootmsg.service

systemd_shutdown_DATA = lcdbootmsg.shutdown

EXTRA_DIST = $(DATA)

install-data-hook:
	chmod 755 $(DESTDIR)$(systemd_shutdowndir)/lcdbootmsg.shutdown
