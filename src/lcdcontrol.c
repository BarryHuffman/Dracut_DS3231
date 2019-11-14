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

#include <unistd.h>

#include "rpi-lcd.h"

int
main ()
{
  int dev;

  dev = lcdSetup(0x27, 1);

#if 0
  lcdClear (dev);

  lcdDisplayOff (dev);
  sleep (10);
  lcdDisplayOn (dev);

  lcdWriteString (dev, 1, "Hello1\nHello2");
#endif

  lcdClose(dev);

  return 0;
}
