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
    hostonly="" instmods i2c-dev
    inst_multiple \
        /usr/bin/lcdcontrol \
        $systemdsystemunitdir/lcdbootmsg.service
    mkdir -p "$initdir/$systemdsystemunitdir/systemd-journald.service.wants"
    ln_r "$systemdsystemunitdir/lcdbootmsg.service" "$systemdsystemunitdir/systemd-journald.service.wants/lcdbootmsg.service"
}

