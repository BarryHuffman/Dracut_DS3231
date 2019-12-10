# C-Library and Utilities to control a HD44780 LCD display on a Raspberry Pi.

## librpi-lcd
librpi-lcd is a library which provides functions to control a HD44780 LCD
display connected via an i2c bus on a Raspberry Pi.

## lcdcontrol
This utility provides a command line interface to  manage the LCD display:
 * init - initializes the LCD display
 * clear - clears the LCD display, cursor is moved to home position
 * display=on - enables the display (switch backlight on)
 * display=off - disables the display (switch backlight off)
 * cursor=on - enables cursor
 * cursor=off - disables cursor
 * cursor=blink - enables a blinking cursor
 * line=<number> - moves cursor to the beginning of this line
 * str=<text> - prints the text on the current cursor position

## lcdnetmon
This utility reads a configuration file and prints the corresponding
output to a LCD display. It can monitor the network interfaces and 
update the output accordingly, so that the display always shows the
current IP addresses.

Configuration files:
  * /usr/etc/lcdnetmon.conf - distribution provided default configuration
  * /etc/lcdnetmon.conf - admin provided file, overrides /usr/etc
  * /etc/lcdnetmon.conf.d/*.conf - admin provided snippes overriding either entries from /usr/etc/lcdnetmon.conf or /etc/lcdnetmon.conf

Variables:
  * ROWS - number of rows of the display
  * LINE1, LINE2, ... - Text lcdnetmon should print

Special codes in text:
  * \4{iface} - Prints the IPv4 address of interface "iface"

Example configuration file for a 4x20 LCD display:
```
ROWS=4
LINE1="eth0/eth1/wlan0"
LINE2="\4{eth0}"
LINE3="\4{eth1}"
LINE4="\4{wlan0}"
```

lcdnetmon will print the following:
 * line 1: "eth0/eth1/wlan0"
 * line 2: IPv4 address of eth0 if one is set
 * line 3: IPv4 address of eth1 if one is set
 * line 4: IPv4 address of wlan0 if one is set

If the IPv4 address of any of the interfaces changes, the output will
change, too.

## Dracut modules for openSUSE/SUSE distributions

### rpi-rtc-ds3231

This dracut modules provides a udev rule and necessary configuration files
to set the system time during boot from the initrd by using a 
ds3231 rtc module.


