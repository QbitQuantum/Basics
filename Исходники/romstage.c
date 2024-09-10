void cache_as_ram_main(unsigned long bist, unsigned long cpu_init_detectedx)
{
	u32 val;

	/*
	 * All cores: allow caching of flash chip code and data
	 * (there are no cache-as-ram reliability concerns with family 14h)
	 */
	__writemsr (0x20c, (0x0100000000ull - CACHE_ROM_SIZE) | 5);
	__writemsr (0x20d, (0x1000000000ull - CACHE_ROM_SIZE) | 0x800);

	/* All cores: set pstate 0 (1600 MHz) early to save a few ms of boot time */
	__writemsr (0xc0010062, 0);

	amd_initmmio();

	if (!cpu_init_detectedx && boot_cpu()) {
		post_code(0x30);
		sb_Poweron_Init();

		post_code(0x31);
		fintek_enable_serial(SERIAL_DEV, CONFIG_TTYS0_BASE);
		console_init();
	}

	/* Halt if there was a built in self test failure */
	post_code(0x34);
	report_bist_failure(bist);

	/* Load MPB */
	val = cpuid_eax(1);
	printk(BIOS_DEBUG, "BSP Family_Model: %08x\n", val);
	printk(BIOS_DEBUG, "cpu_init_detectedx = %08lx\n", cpu_init_detectedx);

	post_code(0x37);
	agesawrapper_amdinitreset();

	post_code(0x39);
	agesawrapper_amdinitearly();

	int s3resume = acpi_is_wakeup_s3();
	if (!s3resume) {
		post_code(0x40);
		agesawrapper_amdinitpost();

		post_code(0x42);
		agesawrapper_amdinitenv();
		amd_initenv();

	} else { 			/* S3 detect */
		printk(BIOS_INFO, "S3 detected\n");

		post_code(0x60);
		agesawrapper_amdinitresume();

		agesawrapper_amds3laterestore();

		post_code(0x61);
		prepare_for_resume();
	}

	post_code(0x50);
	copy_and_run();
	printk(BIOS_ERR, "Error: copy_and_run() returned!\n");

	post_code(0x54);	/* Should never see this post code. */
}