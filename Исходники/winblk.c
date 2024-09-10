int 
winblkopen(struct open_file *f, ...)
/* file, devname, unit, partition */
{
	va_list ap;
	struct winblk *ctx = NULL;
	char *devname;
	int unit;
	int partition;
	TCHAR wdevname[6];
	DWORD wres;
	int i;
	int start_386bsd;

	int error = 0;

	ctx = (struct winblk *)alloc(sizeof(*ctx));
	if (!ctx) {
		error = ENOMEM;
		goto end;
	}
	f->f_devdata = ctx;

	va_start(ap, f);
	devname = va_arg(ap, char*);
	unit = va_arg(ap, int);
	partition = va_arg(ap, int);
        va_end(ap);

	/*
	 *  Windows' device name must be 3 uppper letters and 1 digit
	 *  following a semicolon like "DSK1:".
	 */
	if (strlen(devname) != 3 || unit < 0 || 9 < unit) {
		error = ENODEV;
		goto end;
	}
	wsprintf(wdevname, TEXT("%C%C%C%d:"),
		toupper(devname[0]),
		toupper(devname[1]),
		toupper(devname[2]),
		unit);
	DEBUG_PRINTF((TEXT("winblk.open: block device name is '%s'\n"),
		      wdevname));

	ctx->hDevice = CreateFile(wdevname, GENERIC_READ, 0, NULL,    
				  OPEN_EXISTING, 0, NULL);
	if (ctx->hDevice == INVALID_HANDLE_VALUE) {
		win_printf(TEXT("can't open %s.\n"), wdevname);
		error = ENODEV; /* XXX, We shuld check GetLastError(). */
		goto end;
	}

	/*
	 *  get DISK_INFO
	 *  CHS, sector size and device flags.
	 */
	if (!DeviceIoControl(ctx->hDevice, DISK_IOCTL_GETINFO,
			     &ctx->di, sizeof(ctx->di),
			     NULL, 0, &wres, NULL)) {
		win_printf(TEXT("DeviceIoControl() failed.error=%d\n"),
			   GetLastError());

		error = EIO; /* XXX, We shuld check GetLastError(). */
		goto end;
	}

#ifdef DEBUG
	win_printf(TEXT("DISK_INFO: CHS=%d:%d:%d  block size=%d  flag="),
		   ctx->di.di_cylinders,
		   ctx->di.di_heads,
		   ctx->di.di_sectors,
		   ctx->di.di_bytes_per_sect);
	if (ctx->di.di_flags & DISK_INFO_FLAG_MBR) {
		win_printf(TEXT("MBR "));
	}
	if (ctx->di.di_flags & DISK_INFO_FLAG_CHS_UNCERTAIN) {
		win_printf(TEXT("CHS_UNCERTAIN "));
	}
	if (ctx->di.di_flags & DISK_INFO_FLAG_UNFORMATTED) {
		win_printf(TEXT("UNFORMATTED "));
	}
	if (ctx->di.di_flags & DISK_INFO_FLAG_PAGEABLE) {
		win_printf(TEXT("PAGEABLE "));
	}
	win_printf(TEXT("\n"));
#endif /* DEBUG */

	if (!(ctx->di.di_flags & DISK_INFO_FLAG_MBR) ||
	     (ctx->di.di_flags & DISK_INFO_FLAG_CHS_UNCERTAIN) ||
	     (ctx->di.di_flags & DISK_INFO_FLAG_UNFORMATTED) ||
	     (ctx->di.di_bytes_per_sect != BLKSZ)) {
		win_printf(TEXT("invalid flags\n"));
		error = EINVAL;
		goto end;
	}

	/*
	 *  read MBR
	 */
	if (error = rawread(ctx, MBR_BBSECTOR, 1, ctx->buf)) {
		goto end;
	}
	memcpy(&ctx->mbr, &ctx->buf[MBR_PARTOFF], sizeof(ctx->mbr));

	for (i = 0; i < NMBRPART; i++) {
	        DEBUG_PRINTF((TEXT("%d: type=%d %d(%d) (%d:%d:%d - %d:%d:%d)")
			      TEXT(" flag=0x%02x\n"),
			      i,
			      ctx->mbr[i].mbrp_typ,
			      ctx->mbr[i].mbrp_start,
			      ctx->mbr[i].mbrp_size,
			      ctx->mbr[i].mbrp_scyl,
			      ctx->mbr[i].mbrp_shd,
			      ctx->mbr[i].mbrp_ssect,
			      ctx->mbr[i].mbrp_ecyl,
			      ctx->mbr[i].mbrp_ehd,
			      ctx->mbr[i].mbrp_esect,
			      ctx->mbr[i].mbrp_flag));
	}

	/*
	 *  find BSD partition
	 */
	ctx->start = -1;
	start_386bsd = -1;
	for (i = 0; i < NMBRPART; i++) {
		if (ctx->mbr[i].mbrp_typ == MBR_PTYPE_NETBSD) {
			ctx->start = ctx->mbr[i].mbrp_start;
			break;
		}
		if (ctx->mbr[i].mbrp_typ == MBR_PTYPE_386BSD) {
			start_386bsd = ctx->mbr[i].mbrp_start;
		}
	}
	if (ctx->start == -1) {
		ctx->start = start_386bsd;
	}

	if (ctx->start == -1) {
		/*
		 *  BSD partition is not found.
		 *  Try to use entire disk.
		 */
		ctx->start = 0;
		win_printf(TEXT("no BSD partition, start sector=0x%x\n"),
			   ctx->start);
		goto end;
	}

	/*
	 *  read disklabel
	 */
	if (error = rawread(ctx, ctx->start + LABELSECTOR, 1, ctx->buf)) {
		goto end;
	}
	memcpy(&ctx->dl, &ctx->buf[LABELOFFSET], sizeof(ctx->dl));

	if (ctx->dl.d_magic != DISKMAGIC ||
	    ctx->dl.d_magic2 != DISKMAGIC ||
	    dkcksum(&ctx->dl) != 0) {
		win_printf(TEXT("invalid disklabel, start sector=0x%x\n"),
			   ctx->start);
		/*
		 *  Disklabel is not found.
		 *  Try to use entire partition.
		 */
		goto end;
	}

	if (partition < 0 || ctx->dl.d_npartitions <= partition) {
		error = EINVAL;
		goto end;
	}

	ctx->start = ctx->dl.d_partitions[partition].p_offset;
	win_printf(TEXT("start sector=0x%x\n"), ctx->start);

      end:
	if (error && ctx) {
		free(ctx, sizeof(*ctx));
		f->f_devdata = NULL;
	}
	return (error);
}