struct bi_record *
decompress_kernel(unsigned long load_addr, int num_words, unsigned long cksum)
{
#ifdef INTERACTIVE_CONSOLE
	int timer = 0;
	char ch;
#endif
	char *cp;
	struct bi_record *rec;
	unsigned long rec_loc, initrd_loc, TotalMemory = 0;

	serial_fixups();
	com_port = serial_init(0, NULL);

#ifdef CONFIG_LOPEC
	/*
	 * This should work on any board with an MPC10X which is properly
	 * initalized.
	 */
	TotalMemory = mpc10x_get_mem_size(MPC10X_MEM_MAP_B);
#endif

	/* assume the chunk below 8M is free */
	end_avail = (char *)0x00800000;

	/*
	 * Reveal where we were loaded at and where we
	 * were relocated to.
	 */
	puts("loaded at:     "); puthex(load_addr);
	puts(" "); puthex((unsigned long)(load_addr + (4*num_words)));
	puts("\n");
	if ( (unsigned long)load_addr != (unsigned long)&start )
	{
		puts("relocated to:  "); puthex((unsigned long)&start);
		puts(" ");
		puthex((unsigned long)((unsigned long)&start + (4*num_words)));
		puts("\n");
	}

	/*
	 * We link ourself to 0x00800000.  When we run, we relocate
	 * ourselves there.  So we just need __image_begin for the
	 * start. -- Tom
	 */
	zimage_start = (char *)(unsigned long)(&__image_begin);
	zimage_size = (unsigned long)(&__image_end) -
			(unsigned long)(&__image_begin);

	initrd_size = (unsigned long)(&__ramdisk_end) -
		(unsigned long)(&__ramdisk_begin);

	/*
	 * The zImage and initrd will be between start and _end, so they've
	 * already been moved once.  We're good to go now. -- Tom
	 */
	avail_ram = (char *)PAGE_ALIGN((unsigned long)_end);
	puts("zimage at:     "); puthex((unsigned long)zimage_start);
	puts(" "); puthex((unsigned long)(zimage_size+zimage_start));
	puts("\n");

	if ( initrd_size ) {
		puts("initrd at:     ");
		puthex((unsigned long)(&__ramdisk_begin));
		puts(" "); puthex((unsigned long)(&__ramdisk_end));puts("\n");
	}

	avail_ram = (char *)0x00400000;
	end_avail = (char *)0x00800000;
	puts("avail ram:     "); puthex((unsigned long)avail_ram); puts(" ");
	puthex((unsigned long)end_avail); puts("\n");

	if (keyb_present)
		CRT_tstc();  /* Forces keyboard to be initialized */
#ifdef CONFIG_GEMINI
	/*
	 * If cmd_line is empty and cmd_preset is not, copy cmd_preset
	 * to cmd_line.  This way we can override cmd_preset with the
	 * command line from Smon.
	 */

	if ( (cmd_line[0] == '\0') && (cmd_preset[0] != '\0'))
		memcpy (cmd_line, cmd_preset, sizeof(cmd_preset));
#endif

	/* Display standard Linux/PPC boot prompt for kernel args */
	puts("\nLinux/PPC load: ");
	cp = cmd_line;
	memcpy (cmd_line, cmd_preset, sizeof(cmd_preset));
	while ( *cp ) putc(*cp++);

#ifdef INTERACTIVE_CONSOLE
	/*
	 * If they have a console, allow them to edit the command line.
	 * Otherwise, don't bother wasting the five seconds.
	 */
	while (timer++ < 5*1000) {
		if (tstc()) {
			while ((ch = getc()) != '\n' && ch != '\r') {
				/* Test for backspace/delete */
				if (ch == '\b' || ch == '\177') {
					if (cp != cmd_line) {
						cp--;
						puts("\b \b");
					}
				/* Test for ^x/^u (and wipe the line) */
				} else if (ch == '\030' || ch == '\025') {
					while (cp != cmd_line) {
						cp--;
						puts("\b \b");
					}
				} else {
					*cp++ = ch;
					putc(ch);
				}
			}
			break;  /* Exit 'timer' loop */
		}
		udelay(1000);  /* 1 msec */
	}
	*cp = 0;
#endif
	puts("\n");

	puts("Uncompressing Linux...");
	gunzip(0, 0x400000, zimage_start, &zimage_size);
	puts("done.\n");

	/*
	 * Create bi_recs for cmd_line and initrds
	 */
	rec_loc = _ALIGN((unsigned long)(zimage_size) +
			(1 << 20) - 1, (1 << 20));
	rec = (struct bi_record *)rec_loc;

	/* We need to make sure that the initrd and bi_recs do not
	 * overlap. */
	if ( initrd_size ) {
		initrd_loc = (unsigned long)(&__ramdisk_begin);
		/* If the bi_recs are in the middle of the current
		 * initrd, move the initrd to the next MB
		 * boundary. */
		if ((rec_loc > initrd_loc) &&
				((initrd_loc + initrd_size) > rec_loc)) {
			initrd_loc = _ALIGN((unsigned long)(zimage_size)
					+ (2 << 20) - 1, (2 << 20));
		 	memmove((void *)initrd_loc, &__ramdisk_begin,
				 initrd_size);
	         	puts("initrd moved:  "); puthex(initrd_loc);
		 	puts(" "); puthex(initrd_loc + initrd_size);
		 	puts("\n");
		}
	}
 
	rec->tag = BI_FIRST;
	rec->size = sizeof(struct bi_record);
	rec = (struct bi_record *)((unsigned long)rec + rec->size);

	if ( TotalMemory ) {
		rec->tag = BI_MEMSIZE;
		rec->data[0] = TotalMemory;
		rec->size = sizeof(struct bi_record) + sizeof(unsigned long);
		rec = (struct bi_record *)((unsigned long)rec + rec->size);
	}

	rec->tag = BI_CMD_LINE;
	memcpy( (char *)rec->data, cmd_line, strlen(cmd_line)+1);
	rec->size = sizeof(struct bi_record) + strlen(cmd_line) + 1;
	rec = (struct bi_record *)((unsigned long)rec + rec->size);

	if ( initrd_size ) {
		rec->tag = BI_INITRD;
		rec->data[0] = initrd_loc;
		rec->data[1] = initrd_size;
		rec->size = sizeof(struct bi_record) + 2 *
			sizeof(unsigned long);
		rec = (struct bi_record *)((unsigned long)rec +
				rec->size);
	}

	rec->tag = BI_LAST;
	rec->size = sizeof(struct bi_record);
	rec = (struct bi_record *)((unsigned long)rec + rec->size);
	puts("Now booting the kernel\n");
	serial_close(com_port);

	return (struct bi_record *)rec_loc;
}