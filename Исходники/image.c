/**
 * boot_ramdisk_high - relocate init ramdisk
 * @lmb: pointer to lmb handle, will be used for memory mgmt
 * @rd_data: ramdisk data start address
 * @rd_len: ramdisk data length
 * @initrd_start: pointer to a ulong variable, will hold final init ramdisk
 *      start address (after possible relocation)
 * @initrd_end: pointer to a ulong variable, will hold final init ramdisk
 *      end address (after possible relocation)
 *
 * boot_ramdisk_high() takes a relocation hint from "initrd_high" environement
 * variable and if requested ramdisk data is moved to a specified location.
 *
 * Initrd_start and initrd_end are set to final (after relocation) ramdisk
 * start/end addresses if ramdisk image start and len were provided,
 * otherwise set initrd_start and initrd_end set to zeros.
 *
 * returns:
 *      0 - success
 *     -1 - failure
 */
int boot_ramdisk_high(struct lmb *lmb, ulong rd_data, ulong rd_len,
		  ulong *initrd_start, ulong *initrd_end)
{
	char	*s;
	ulong	initrd_high;
	int	initrd_copy_to_ram = 1;

	if ((s = getenv("initrd_high")) != NULL) {
		/* a value of "no" or a similar string will act like 0,
		 * turning the "load high" feature off. This is intentional.
		 */
		initrd_high = simple_strtoul(s, NULL, 16);
		if (initrd_high == ~0)
			initrd_copy_to_ram = 0;
	} else {
		/* not set, no restrictions to load high */
		initrd_high = ~0;
	}


#ifdef CONFIG_LOGBUFFER
	/* Prevent initrd from overwriting logbuffer */
	lmb_reserve(lmb, logbuffer_base() - LOGBUFF_OVERHEAD, LOGBUFF_RESERVE);
#endif

	debug("## initrd_high = 0x%08lx, copy_to_ram = %d\n",
			initrd_high, initrd_copy_to_ram);

	if (rd_data) {
		if (!initrd_copy_to_ram) {	/* zero-copy ramdisk support */
			debug("   in-place initrd\n");
			*initrd_start = rd_data;
			*initrd_end = rd_data + rd_len;
			lmb_reserve(lmb, rd_data, rd_len);
		} else {
			if (initrd_high)
				*initrd_start = (ulong)lmb_alloc_base(lmb,
						rd_len, 0x1000, initrd_high);
			else
				*initrd_start = (ulong)lmb_alloc(lmb, rd_len,
								 0x1000);

			if (*initrd_start == 0) {
				puts("ramdisk - allocation error\n");
				goto error;
			}
			bootstage_mark(BOOTSTAGE_ID_COPY_RAMDISK);

			*initrd_end = *initrd_start + rd_len;
			printf("   Loading Ramdisk to %08lx, end %08lx ... ",
					*initrd_start, *initrd_end);

			memmove_wd((void *)*initrd_start,
					(void *)rd_data, rd_len, CHUNKSZ);

#ifdef CONFIG_MP
			/*
			 * Ensure the image is flushed to memory to handle
			 * AMP boot scenarios in which we might not be
			 * HW cache coherent
			 */
			flush_cache((unsigned long)*initrd_start, rd_len);
#endif
			puts("OK\n");
		}
	} else {
		*initrd_start = 0;
		*initrd_end = 0;
	}
	debug("   ramdisk load start = 0x%08lx, ramdisk load end = 0x%08lx\n",
			*initrd_start, *initrd_end);

	return 0;

error:
	return -1;
}