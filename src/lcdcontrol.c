/* Copyright (C) 2019  Thorsten Kukuk

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License version 2.1 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "rpi-lcd.h"

int
main (int argc, char **argv)
{
  int dev;
  int c = 1;

  if (argc > 1 && strcmp (argv[1], "init") == 0)
    {
      dev = lcdSetup(0x27, 1, 1);
      c++;
    }
  else
    dev = lcdSetup(0x27, 1, 0);

  if (dev < 0) {
    fprintf (stderr, "ERROR: couldn't open /dev/i2c-%i: %m\n", 1);
    exit (1);
  }

  for (int i = c; i < argc; i++)
    {
      if (strncasecmp ("str=", argv[i], 4) == 0)
	lcdWriteString (dev, 0, &argv[i][4]);
      else if (strcasecmp ("clear", argv[i]) == 0)
	lcdClear (dev);
      else if (strcasecmp ("display=on", argv[i]) == 0)
	lcdDisplayOn (dev);
      else if (strcasecmp ("display=off", argv[i]) == 0)
	lcdDisplayOff (dev);
      else if (strcasecmp ("cursor=on", argv[i]) == 0)
	lcdCursorOn (dev);
      else if (strcasecmp ("cursor=off", argv[i]) == 0)
	lcdCursorOff (dev);
      else if (strcasecmp ("cursor=blink", argv[i]) == 0)
	lcdCursorBlink (dev);
      else if (strncasecmp ("line=", argv[i], 5) == 0)
	lcdGotoLine (dev, atoi (&argv[i][5]));
      else
	{
	  fprintf (stderr, "Error: unknown argument: '%s'\n", argv[i]);
	  exit (1);
	}
    }

  lcdClose(dev);

  return 0;
}
