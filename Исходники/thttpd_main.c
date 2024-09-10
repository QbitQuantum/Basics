int thttp_main(int argc, char *argv[])
{
  struct in_addr addr;
#ifdef CONFIG_EXAMPLE_THTTPD_NOMAC
  uint8_t mac[IFHWADDRLEN];
#endif
  char *thttpd_argv = "thttpd";
  int ret;

  /* Configure SLIP */

#ifdef CONFIG_NET_SLIP
  ret = slip_initialize(SLIP_DEVNO, CONFIG_NET_SLIPTTY);
  if (ret < 0)
    {
      message("ERROR: SLIP initialization failed: %d\n", ret);
      exit(1);
    }
#endif

/* Many embedded network interfaces must have a software assigned MAC */

#ifdef CONFIG_EXAMPLE_THTTPD_NOMAC
  message("Assigning MAC\n");

  mac[0] = 0x00;
  mac[1] = 0xe0;
  mac[2] = 0xde;
  mac[3] = 0xad;
  mac[4] = 0xbe;
  mac[5] = 0xef;
  uip_setmacaddr(NET_DEVNAME, mac);
#endif

  /* Set up our host address */

  message("Setup network addresses\n");
  addr.s_addr = HTONL(CONFIG_THTTPD_IPADDR);
  uip_sethostaddr(NET_DEVNAME, &addr);

  /* Set up the default router address */

  addr.s_addr = HTONL(CONFIG_EXAMPLE_THTTPD_DRIPADDR);
  uip_setdraddr(NET_DEVNAME, &addr);

  /* Setup the subnet mask */

  addr.s_addr = HTONL(CONFIG_EXAMPLE_THTTPD_NETMASK);
  uip_setnetmask(NET_DEVNAME, &addr);

  /* Initialize the NXFLAT binary loader */

  message("Initializing the NXFLAT binary loader\n");
  ret = nxflat_initialize();
  if (ret < 0)
    {
      message("ERROR: Initialization of the NXFLAT loader failed: %d\n", ret);
      exit(2);
    }

  /* Create a ROM disk for the ROMFS filesystem */

  message("Registering romdisk\n");
  ret = romdisk_register(0, (uint8_t*)romfs_img, NSECTORS(romfs_img_len), SECTORSIZE);
  if (ret < 0)
    {
      message("ERROR: romdisk_register failed: %d\n", ret);
      nxflat_uninitialize();
      exit(1);
    }

  /* Mount the file system */

  message("Mounting ROMFS filesystem at target=%s with source=%s\n",
         MOUNTPT, ROMFSDEV);

  ret = mount(ROMFSDEV, MOUNTPT, "romfs", MS_RDONLY, NULL);
  if (ret < 0)
    {
      message("ERROR: mount(%s,%s,romfs) failed: %s\n",
              ROMFSDEV, MOUNTPT, errno);
      nxflat_uninitialize();
    }

  /* Start THTTPD.  At present, symbol table info is passed via global variables */

  g_thttpdsymtab   = exports;
  g_thttpdnsymbols = NEXPORTS;

  message("Starting THTTPD\n");
  msgflush();
  thttpd_main(1, &thttpd_argv);
  message("THTTPD terminated\n");
  msgflush();
  return 0;
}