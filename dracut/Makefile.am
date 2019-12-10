
lcdbootmsgdir = @DRACUTDIR@/modules.d/99lcdbootmsg
rpi_rtcdir = @DRACUTDIR@/modules.d/99rpi-rtc-ds3231

lcdbootmsg_DATA = lcdbootmsg/module-setup.sh
rpi_rtc_DATA = rpi-rtc-ds3231/module-setup.sh \
	rpi-rtc-ds3231/60-rtc-ds3231-sync.rules \
	rpi-rtc-ds3231/hwclock.conf

EXTRA_DIST = $(DATA)

install-data-hook:
	chmod 755 $(DESTDIR)$(lcdbootmsgdir)/module-setup.sh
	chmod 755 $(DESTDIR)$(rpi_rtcdir)/module-setup.sh
