#!/bin/bash

# called by dracut
check() {
    return 0
}

# called by dracut
depends() {
    return 0
}

# called by dracut
install() {
    inst /etc/adjtime
    inst /usr/sbin/hwclock
    mkdir -p "${initdir}${systemdsystemunitdir}/systemd-udevd.service.d/"
    inst_simple "${moddir}/hwclock.conf" "${systemdsystemunitdir}/systemd-udevd.service.d/hwclock.conf"
    mkdir -p "${initdir}/etc/udev/rules.d"
    inst_simple "${moddir}/60-rtc-ds3231-sync.rules" "/etc/udev/rules.d/60-rtc-ds3231-sync.rules"
}

