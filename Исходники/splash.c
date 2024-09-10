void splash_logo(u32 splash_id)
{
	bmp_t *bmp;
	int rval = 0;
	u32 out_ptr = 0;
	u32 gzip_logo;
	int gzip_logo_len;

	/* Select the free memory for store the decomprssed data */
	if (logo_addr == NULL)
#if (CHIP_REV == I1)
		logo_addr = (u8 *)BSB_RAM_START;
#else
		logo_addr = (u8 *)0xc2000000;
#endif

	if (splash_id == 0) {
		gzip_logo = (u32)&__gzip_logo_1;
		gzip_logo_len = __gzip_logo_1_len;
	} else if (splash_id == 1) {
		gzip_logo = (u32)&__gzip_logo_2;
		gzip_logo_len = __gzip_logo_2_len;
	} else if (splash_id == 2) {
		gzip_logo = (u32)&__gzip_logo_3;
		gzip_logo_len = __gzip_logo_3_len;
	} else if (splash_id == 3) {
		gzip_logo = (u32)&__gzip_logo_4;
		gzip_logo_len = __gzip_logo_4_len;
	} else if (splash_id == 4) {
		gzip_logo = (u32)&__gzip_logo_5;
		gzip_logo_len = __gzip_logo_5_len;
	} else {
		putstr("Splash_Err : splash_id should be between 1 and 5!");
		putstr("\r\n");
		/* If splash id is not valid, VOUT_BG_BLUE */
		//vout_set_monitor_bg_color(chan, 0x29, 0xf0, 0x6e);
		return;
	}

	if (gzip_logo_len == 0) {
		putstr("Splash_Err : splash logo length = 0!");
		return;
	}

	out_ptr = decompress("splash",
		   (u32) gzip_logo,
		   ((u32) gzip_logo) + gzip_logo_len,
		   (u32) logo_addr,
		   (u32) &__heap_start,
		   (u32) &__heap_end);

	/** Use the golbal variable to store the BMP info for VOUT OSD used.
	 */
	bmp = bld_get_splash_bmp();

	/* Parse the BMP file header */
	rval = bld_parse_bmp(logo_addr, bmp);

	if (rval == 0) {
		/* Assign the the BMP raw data offset to the bmp buffer */
		bmp->buf = (logo_addr + bmp->header.fheader.offset);
		/* Assign the the BMP width, height, pitch from the info header */
		bmp->width = bmp->header.iheader.width;
		/* BMP pitch need be the mutilple of 4 */
		if ((bmp->width % 4) != 0)
			bmp->width = ((bmp->header.iheader.width / 4) + 1) * 4;

		bmp->height = bmp->header.iheader.height;
		bmp->pitch  = bmp->width;
		bmp->size   = bmp->header.iheader.bmp_data_size;
	} else {
		putstr("Splash_Err : Parsing BMP header!");
		putstr("\r\n");
		return;
	}
}