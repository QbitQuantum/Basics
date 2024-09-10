/*
 *  board_final_init()
 *
 *  Do any final initialization, such as adding commands to the
 *  user interface.
 *
 *  If you don't want a user interface, put the startup code here.
 *  This routine is called just before CFE starts its user interface.
 *
 *  Input parameters:
 *     nothing
 *
 *  Return value:
 *     nothing
 */
void
board_final_init(void)
{
	char *addr, *mask, *wait_time;
	char buf[512], *cur = buf;
#ifdef CFG_ROMBOOT
	char *laddr = NULL;
#endif
#if !CFG_SIM
	char *boot_cfg = NULL;
	char *go_cmd = "go;";
#endif
	int commit = 0;
	uint32 ncdl;
#if CFG_WL && CFG_WLU && CFG_SIM
	char *ssid;
#endif

	ui_init_bcm947xxcmds();

	/* Force commit of embedded NVRAM */
	commit = restore_defaults;

	/* Set the SDRAM NCDL value into NVRAM if not already done */
	if ((getintvar(NULL, "sdram_ncdl") == 0) &&
	    ((ncdl = si_memc_get_ncdl(sih)) != 0)) {
		sprintf(buf, "0x%x", ncdl);
		nvram_set("sdram_ncdl", buf);
		commit = 1;
	}

	/* Set the bootloader version string if not already done */
	sprintf(buf, "CFE %s", EPI_VERSION_STR);
	if (strcmp(nvram_safe_get("pmon_ver"), buf) != 0) {
		nvram_set("pmon_ver", buf);
		commit = 1;
	}


	/* Set the size of the nvram area if not already done */
	sprintf(buf, "%d", MAX_NVRAM_SPACE);
	if (strcmp(nvram_safe_get("nvram_space"), buf) != 0) {
		nvram_set("nvram_space", buf);
		commit = 1;
	}

#if CFG_FLASH || CFG_SFLASH || CFG_NFLASH
#if !CFG_SIM
	/* Commit NVRAM only if in FLASH */
	if (
#ifdef BCMNVRAMW
		!nvram_inotp() &&
#endif
		commit) {
		printf("Committing NVRAM...");
		nvram_commit();
		printf("done\n");
		if (restore_defaults) {
			printf("Waiting for reset button release...");
			reset_release_wait();
			printf("done\n");
		}
	}

	/* Reboot after restoring defaults */
	if (restore_defaults)
		si_watchdog(sih, 1);
#endif	/* !CFG_SIM */
#else
	if (commit)
		printf("Flash not configured, not commiting NVRAM...\n");
#endif /* CFG_FLASH || CFG_SFLASH || CFG_NFLASH */

	/*
	 * Read the wait_time NVRAM variable and set the tftp max retries.
	 * Assumption: tftp_rrq_timeout & tftp_recv_timeout are set to 1sec.
	 */
	if ((wait_time = nvram_get("wait_time")) != NULL) {
		tftp_max_retries = atoi(wait_time);
		if (tftp_max_retries > MAX_WAIT_TIME)
			tftp_max_retries = MAX_WAIT_TIME;
		else if (tftp_max_retries < MIN_WAIT_TIME)
			tftp_max_retries = MIN_WAIT_TIME;
	}
#ifdef CFG_ROMBOOT
	else if (board_bootdev_rom(sih)) {
		tftp_max_retries = 10;
	}
#endif

	/* Configure network */
	if (cfe_finddev("eth0")) {
		int res;

		if ((addr = nvram_get("lan_ipaddr")) &&
		    (mask = nvram_get("lan_netmask")))
			sprintf(buf, "ifconfig eth0 -addr=%s -mask=%s",
			        addr, mask);
		else
			sprintf(buf, "ifconfig eth0 -auto");

		res = ui_docommand(buf);

#ifdef CFG_ROMBOOT
		/* Try indefinite netboot only while booting from ROM
		 * and we are sure that we dont have valid nvram in FLASH
		 */
		while (board_bootdev_rom(sih) && !addr) {
			char ch;

			cur = buf;
			/* Check if something typed at console */
			if (console_status()) {
				console_read(&ch, 1);
				/* Check for Ctrl-C */
				if (ch == 3) {
					if (laddr)
						MFREE(osh, laddr, MAX_SCRIPT_FSIZE);
					xprintf("Stopped auto netboot!!!\n");
					return;
				}
			}

			if (!res) {
				char *bserver, *bfile, *load_ptr;

				if (!laddr)
					laddr = MALLOC(osh, MAX_SCRIPT_FSIZE);

				if (!laddr) {
					load_ptr = (char *) 0x00008000;
					xprintf("Failed malloc for boot_script, Using :0x%x\n",
						(unsigned int)laddr);
				}
				else {
					load_ptr = laddr;
				}
				bserver = (bserver = env_getenv("BOOT_SERVER"))
					? bserver:"192.168.1.1";

				if ((bfile = env_getenv("BOOT_FILE"))) {
					int len;

					if (((len = strlen(bfile)) > 5) &&
					    !strncmp((bfile + len - 5), "cfesh", 5)) {
						cur += sprintf(cur,
						"batch -raw -tftp -addr=0x%x -max=0x%x %s:%s;",
							(unsigned int)load_ptr,
							MAX_SCRIPT_FSIZE, bserver, bfile);
					}
					if (((len = strlen(bfile)) > 3)) {
						if (!strncmp((bfile + len - 3), "elf", 3)) {
							cur += sprintf(cur,
							"boot -elf -tftp -max=0x5000000 %s:%s;",
							bserver, bfile);
						}
						if (!strncmp((bfile + len - 3), "raw", 3)) {
							cur += sprintf(cur,
							"boot -raw -z -tftp -addr=0x00008000"
							" -max=0x5000000 %s:%s;",
							bserver, bfile);
						}
					}
				}
				else {  /* Make last effort */
					cur += sprintf(cur,
						"batch -raw -tftp -addr=0x%x -max=0x%x %s:%s;",
						(unsigned int)load_ptr, MAX_SCRIPT_FSIZE,
						bserver, "cfe_script.cfesh");
					cur += sprintf(cur,
						"boot -elf -tftp -max=0x5000000 %s:%s;",
						bserver, "boot_file.elf");
					cur += sprintf(cur,
						"boot -raw -z -tftp -addr=0x00008000"
						" -max=0x5000000 %s:%s;",
						bserver, "boot_file.raw");
				}

				ui_docommand(buf);
				cfe_sleep(3*CFE_HZ);
			}

			sprintf(buf, "ifconfig eth0 -auto");
			res = ui_docommand(buf);
		}
#endif /* CFG_ROMBOOT */
	}
#if CFG_WL && CFG_WLU && CFG_SIM
	if ((ssid = nvram_get("wl0_ssid"))) {
		sprintf(buf, "wl join %s", ssid);
		ui_docommand(buf);
	}
#endif

#if !CFG_SIM
	/* Try to run boot_config command if configured.
	 * make sure to leave space for "go" command.
	 */
	if ((boot_cfg = nvram_get("boot_config"))) {
		if (strlen(boot_cfg) < (sizeof(buf) - sizeof(go_cmd)))
			cur += sprintf(cur, "%s;", boot_cfg);
		else
			printf("boot_config too long, skipping to autoboot\n");
	}

	/* Boot image */
	cur += sprintf(cur, go_cmd);
#endif	/* !CFG_SIM */

	/* Startup */
	if (cur > buf)
		env_setenv("STARTUP", buf, ENV_FLG_NORMAL);
}