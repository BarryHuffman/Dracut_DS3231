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

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/rtnetlink.h>
#include <libeconf.h>

#include "rpi-lcd.h"

static int rows = 2;
static char *line[4] = {"eth0:", "\\4{eth0}", NULL, NULL};
static int has_ifaddrs = 0;

static void
output_iface_ip (int device, const char *iface,
		 struct ifaddrs *addrs, sa_family_t family)
{
  struct ifaddrs *p;
  void *addr = NULL;

  if (!addrs)
    return;

  for (p = addrs; p; p = p->ifa_next)
    {
      if (!p->ifa_name ||
	  !p->ifa_addr ||
	  p->ifa_addr->sa_family != family)
	continue;

      if (iface)
	{
	  /* Filter out by interface name */
	  if (strcmp(p->ifa_name, iface) != 0)
	    continue;
	}
      else
	{
	  /* Select the "best" interface */
	  if ((p->ifa_flags & IFF_LOOPBACK) ||
	      !(p->ifa_flags & IFF_UP) ||
	      !(p->ifa_flags & IFF_RUNNING))
	    continue;
	}

      addr = NULL;
      switch (p->ifa_addr->sa_family)
	{
	case AF_INET:
	  addr = &((struct sockaddr_in *) p->ifa_addr)->sin_addr;
	  break;
	case AF_INET6:
	  addr = &((struct sockaddr_in6 *) p->ifa_addr)->sin6_addr;
	  break;
	}

      if (addr)
	{
	  char buf[INET6_ADDRSTRLEN + 1];

	  inet_ntop (family, addr, buf, sizeof(buf));
	  lcdWriteString(device, 0, buf);

	  return;
	}
    }
}

static int
print_lines (int device)
{
  sa_family_t family = AF_INET;
  struct ifaddrs *addrs = NULL;

  if (getifaddrs (&addrs))
    {
      fprintf (stderr, "Error: getifaddrs() failed: %m\n");
      return -1;
    }

  lcdClear (device);
  for (int i = 0; i < rows; i++)
    {
      lcdGotoLine (device, i+1);

      if (line[i] != NULL || strlen (line[i]) > 0)
	{
	  size_t len = strlen (line[i]);
	  for (unsigned int j = 0; j < len; j++)
	    {
	      if (line[i][j] == '\\')
		{
		  if (line[i][j+1] == '4' && line[i][j+2] == '{')
		    {
		      char buf[128];

		      has_ifaddrs = 1;
		      j+=3;
		      for (unsigned int k = 0; (k+j) < len; k++)
			{
			  if (line[i][j+k] != '}')
			    buf[k] = line [i][j+k];
			  else
			    {
			      buf[k] = '\0';
			      j+=k;
			      output_iface_ip (device, buf, addrs, family);
			      break;
			    }
			}
		    }
		  else
		    goto out_char;
		}
	      else
	      out_char:
		lcdWriteChar (device, line[i][j]);
	    }
	}
    }
  freeifaddrs (addrs);

  return 0;
}

static int
watch_ifaddrs (int device)
{
  int fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);

  if (fd < 0)
    {
      fprintf (stderr, "Failed to create netlink socket: %m\n");
      return 1;
    }

  struct sockaddr_nl saddr;
  char buffer[4096];
  struct nlmsghdr *nlh;

  memset(&saddr, 0, sizeof(saddr));
  saddr.nl_family = AF_NETLINK;
  saddr.nl_groups = RTMGRP_LINK|RTMGRP_IPV4_IFADDR;

  if (bind(fd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0)
    {
      fprintf (stderr, "Failed to bind netlink socket: %m\n");
      close (fd);
      return 1;
    }

  nlh = (struct nlmsghdr *)buffer;
  while (1)
    {
      ssize_t len = recv (fd, nlh, 4096, 0);

      if (len < 0)
	{
	  if (errno == EINTR || errno == EAGAIN)
	    {
	      usleep (250000);
	      continue;
	    }

	  fprintf (stderr, "Failed to read netlink: %m\n");
	  continue;
	}

      while ((NLMSG_OK(nlh, len)) && (nlh->nlmsg_type != NLMSG_DONE))
	{
	  if (nlh->nlmsg_type == RTM_NEWADDR ||
	      nlh->nlmsg_type == RTM_DELADDR ||
	      nlh->nlmsg_type == RTM_DELLINK)
	    print_lines (device);
	  nlh = NLMSG_NEXT(nlh, len);
        }
    }

  close (fd);

  return 0;
}

int
main (void)
{
  econf_file *key_file = NULL;
  econf_err error;
  int device;

  error = econf_readDirs (&key_file, "/usr/etc", "/etc",
			  "lcdnetmon", ".conf", "=", "#");
  if (error)
    {
      if (error != ECONF_NOFILE)
	{
	  fprintf (stderr, "ERROR: econf_readDirs: %s\n",
		   econf_errString (error));
	  return 1;
	}
      else
	fprintf (stderr, "Warning: lcdnetmon.conf not found\n");
    }
  else
    {
      econf_getIntValueDef (key_file, "", "ROWS", &rows, rows);
      econf_getStringValueDef (key_file, "", "LINE1", &line[0], line[0]);
      econf_getStringValueDef (key_file, "", "LINE2", &line[1], line[1]);
      econf_getStringValueDef (key_file, "", "LINE3", &line[2], NULL);
      econf_getStringValueDef (key_file, "", "LINE4", &line[3], NULL);
      econf_free (key_file);
    }

  device = lcdSetup(0x27, 1, 1);

  if (print_lines (device) != 0)
    return 1;

  if (has_ifaddrs)
    return watch_ifaddrs (device);
  else
    return 0;
}
