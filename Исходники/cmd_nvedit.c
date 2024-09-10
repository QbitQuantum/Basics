int _do_setenv (int flag, int argc, char *argv[])
{
	DECLARE_GLOBAL_DATA_PTR;

	int   i, len, oldval;
	int   console = -1;
	uchar *env, *nxt = NULL;
	uchar *name;
	bd_t *bd = gd->bd;

	uchar *env_data = env_get_addr(0);

	if (!env_data)	/* need copy in RAM */
		return 1;

	name = argv[1];

	/*
	 * search if variable with this name already exists
	 */
	oldval = -1;
	for (env=env_data; *env; env=nxt+1) {
		for (nxt=env; *nxt; ++nxt)
			;
		if ((oldval = envmatch(name, env-env_data)) >= 0)
			break;
	}

	/*
	 * Delete any existing definition
	 */
	if (oldval >= 0) {
#ifndef CONFIG_ENV_OVERWRITE

		/*
		 * Ethernet Address and serial# can be set only once,
		 * ver is readonly.
		 */
		if ( (strcmp (name, "serial#") == 0) ||
		    ((strcmp (name, "ethaddr") == 0)
#if defined(CONFIG_OVERWRITE_ETHADDR_ONCE) && defined(CONFIG_ETHADDR)
		     && (strcmp (env_get_addr(oldval),MK_STR(CONFIG_ETHADDR)) != 0)
#endif	/* CONFIG_OVERWRITE_ETHADDR_ONCE && CONFIG_ETHADDR */
		    ) ) {
			printf ("Can't overwrite \"%s\"\n", name);
			return 1;
		}
#endif

		/* Check for console redirection */
		if (strcmp(name,"stdin") == 0) {
			console = stdin;
		} else if (strcmp(name,"stdout") == 0) {
			console = stdout;
		} else if (strcmp(name,"stderr") == 0) {
			console = stderr;
		}

		if (console != -1) {
			if (argc < 3) {		/* Cannot delete it! */
				printf("Can't delete \"%s\"\n", name);
				return 1;
			}

			/* Try assigning specified device */
			if (console_assign (console, argv[2]) < 0)
				return 1;

#ifdef CONFIG_SERIAL_MULTI
			if (serial_assign (argv[2]) < 0)
				return 1;
#endif
		}

		/*
		 * Switch to new baudrate if new baudrate is supported
		 */
		if (strcmp(argv[1],"baudrate") == 0) {
			int baudrate = simple_strtoul(argv[2], NULL, 10);
			int i;
			for (i=0; i<N_BAUDRATES; ++i) {
				if (baudrate == baudrate_table[i])
					break;
			}
			if (i == N_BAUDRATES) {
				printf ("## Baudrate %d bps not supported\n",
					baudrate);
				return 1;
			}
			printf ("## Switch baudrate to %d bps and press ENTER ...\n",
				baudrate);
			udelay(50000);
			gd->baudrate = baudrate;
#ifdef CONFIG_PPC
			gd->bd->bi_baudrate = baudrate;
#endif

#if defined(RT6855A_ASIC_BOARD) || defined(RT6855A_FPGA_BOARD)
			bbu_uart_init();
#else
			serial_setbrg ();
#endif

			udelay(50000);
			for (;;) {
				if (getc() == '\r')
				      break;
			}
		}

		if (*++nxt == '\0') {
			if (env > env_data) {
				env--;
			} else {
				*env = '\0';
			}
		} else {
			for (;;) {
				*env = *nxt++;
				if ((*env == '\0') && (*nxt == '\0'))
					break;
				++env;
			}
		}
		*++env = '\0';
	}

#ifdef CONFIG_NET_MULTI
	if (strncmp(name, "eth", 3) == 0) {
		char *end;
		int   num = simple_strtoul(name+3, &end, 10);

		if (strcmp(end, "addr") == 0) {
			eth_set_enetaddr(num, argv[2]);
		}
	}
#endif


	/* Delete only ? */
	if ((argc < 3) || argv[2] == NULL) {
		env_crc_update ();
		return 0;
	}

	/*
	 * Append new definition at the end
	 */
	for (env=env_data; *env || *(env+1); ++env)
		;
	if (env > env_data)
		++env;
	/*
	 * Overflow when:
	 * "name" + "=" + "val" +"\0\0"  > ENV_SIZE - (env-env_data)
	 */
	len = strlen(name) + 2;
	/* add '=' for first arg, ' ' for all others */
	for (i=2; i<argc; ++i) {
		len += strlen(argv[i]) + 1;
	}
	if (len > (&env_data[ENV_SIZE]-env)) {
		printf ("## Error: environment overflow, \"%s\" deleted\n", name);
		return 1;
	}
	while ((*env = *name++) != '\0')
		env++;
	for (i=2; i<argc; ++i) {
		char *val = argv[i];

		*env = (i==2) ? '=' : ' ';
		while ((*++env = *val++) != '\0')
			;
	}

	/* end is marked with double '\0' */
	*++env = '\0';

	/* Update CRC */
	env_crc_update ();

	/*
	 * Some variables should be updated when the corresponding
	 * entry in the enviornment is changed
	 */

	if (strcmp(argv[1],"ethaddr") == 0) {
		char *s = argv[2];	/* always use only one arg */
		char *e;
		for (i=0; i<6; ++i) {
			bd->bi_enetaddr[i] = s ? simple_strtoul(s, &e, 16) : 0;
			if (s) s = (*e) ? e+1 : e;
		}
#ifdef CONFIG_NET_MULTI
		eth_set_enetaddr(0, argv[2]);
#endif
		return 0;
	}

	if (strcmp(argv[1],"ipaddr") == 0) {
		char *s = argv[2];	/* always use only one arg */
		char *e;
		unsigned long addr;
		bd->bi_ip_addr = 0;
		for (addr=0, i=0; i<4; ++i) {
			ulong val = s ? simple_strtoul(s, &e, 10) : 0;
			addr <<= 8;
			addr  |= (val & 0xFF);
			if (s) s = (*e) ? e+1 : e;
		}
		bd->bi_ip_addr = htonl(addr);
		return 0;
	}
	if (strcmp(argv[1],"loadaddr") == 0) {
		load_addr = simple_strtoul(argv[2], NULL, 16);
		return 0;
	}
#if (CONFIG_COMMANDS & CFG_CMD_NET)
	if (strcmp(argv[1],"bootfile") == 0) {
		copy_filename (BootFile, argv[2], sizeof(BootFile));
		return 0;
	}
#endif	/* CFG_CMD_NET */

#ifdef CONFIG_AMIGAONEG3SE
	if (strcmp(argv[1], "vga_fg_color") == 0 ||
	    strcmp(argv[1], "vga_bg_color") == 0 ) {
		extern void video_set_color(unsigned char attr);
		extern unsigned char video_get_attr(void);

		video_set_color(video_get_attr());
		return 0;
	}
#endif	/* CONFIG_AMIGAONEG3SE */

#if 0
	if (strcmp(argv[1],"twe0") == 0) {
		printf("\n Reset  to Flash environment  \n");
	{

		unsigned int regvalue,kk0;


		kk0 = simple_strtoul(argv[2], NULL, 16);
		
		regvalue = *(volatile u_long *)(RALINK_SYSCTL_BASE + 0x0308);

	printf("\n Default FLASH_CS1_CFG = %08X \n",regvalue);

    regvalue &= ~(0x3 << 26);
	regvalue |= (0x1 << 26);

	regvalue |= (0x1 << 24);

	regvalue &= ~(0x3 << 20);
	regvalue |= (0x1 << 20);

	regvalue &= ~(0x3 << 16);
	regvalue |= (0x1 << 16);

	regvalue &= ~(0xF << 12);
	regvalue |= (kk0 << 12);


	*(volatile u_long *)(RALINK_SYSCTL_BASE + 0x0308) = regvalue;

	regvalue = *(volatile u_long *)(RALINK_SYSCTL_BASE + 0x0308);

		}
	}
#endif

	return 0;
}