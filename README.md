## Dracut scripts to automate DS3231 from a cold boot scenario
(Currently targeting RPI zero,3b,4b with future potential for ODROIDs.)

This is not required if you have a consistent NTP uplink (LAN or WAN).

Disable or remove `fake-hwclock` package before use.

## Included Dracut module for openSUSE/SUSE

### rpi-rtc-ds3231

The dracut modules provide a udev rule, and necessary configuration files for setting the system time during boot.
This is done from within the initrd referencing the ds3231 RTC module.

The following entry is required in 

`/boot/efi/extraconfig.txt`:
```
dtoverlay=i2c-rtc,ds3231
```

## Note:

`timedatectl` process must be restarted to reflect changes of `chronyd` or `ntpd`.

File configuration or status changes should be followed by: 

`systemctl restart systemd-timedated.service`
