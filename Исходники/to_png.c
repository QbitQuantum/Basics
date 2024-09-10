int PicBuf_to_PNG(const GEN_PAR * pg, const OUT_PAR * po)
{
	FILE *fd;
	int row_c, /*byte_c, */ x;
	const RowBuf *row;
	const PicBuf *pb;
	int ppm[][3] = { {255, 255, 255}, {0, 0, 0} };
/*, {255,0,0}, {0,255,0},
		{0,0,255},{0,255,255},{255,0,255},{255,255,0}};
*/
	int colour;

/**
 ** gifdraw-parts
 **/
	pdImagePtr im;
	int pdcol;

	if (pg == NULL || po == NULL)
		return ERROR;
	pb = po->picbuf;
	if (pb == NULL)
		return ERROR;

	if (!pg->quiet)
		Eprintf("\nWriting PNG output: %s\n", po->outfile);
	if (*po->outfile != '-') {

/*
#ifdef VAX
	if ((fd = fopen(po->outfile, WRITE_BIN, "rfm=var", "mrs=512")) == NULL)
#else
*/
		if ((fd = fopen(po->outfile, WRITE_BIN)) == NULL)
/*
#endif
*/
			goto ERROR_EXIT;
	} else
		fd = stdout;

/**
 ** create image structure
 **/
	im = pdImageCreate(pb->nc, pb->nr);

	if (pb->depth > 1) {
/** 
 ** allocate some colors ( ?? eight colors supported by hp2xx ?? )
 **/
		for (colour = 0; colour < PDNCOL; colour++)
/*  pdcol = pdImageColorAllocate(im, ppm[colour][0], ppm[colour][1], 
				    ppm[colour][2]);
*/
			pdcol =
			    pdImageColorAllocate(im, pt.clut[colour][0],
						 pt.clut[colour][1],
						 pt.clut[colour][2]);
		for (row_c = 0; row_c < pb->nr; row_c++) {
			row = get_RowBuf(pb, pb->nr - row_c - 1);
			if (row == NULL)
				continue;

			for (x = 0; x < pb->nc; x++) {
				colour = index_from_RowBuf(row, x, pb);
				pdImageSetPixel(im, x, row_c, colour);
			}
			if ((!pg->quiet) && (row_c % 10 == 0))
				/* For the impatients among us ...   */
				Eprintf(".");
		}
	} else {
/** 
 ** allocate two colors ( ?? eight colors supported by hp2xx ?? )
 **/
		for (colour = 0; colour < 2; colour++)
			pdcol =
			    pdImageColorAllocate(im, ppm[colour][0],
						 ppm[colour][1],
						 ppm[colour][2]);

		for (row_c = 0; row_c < pb->nr; row_c++) {
			row = get_RowBuf(pb, pb->nr - row_c - 1);
			if (row == NULL)
				continue;

			for (x = 0; x < pb->nc; x++) {
				colour = index_from_RowBuf(row, x, pb);
				pdImageSetPixel(im, x, row_c, colour);
			}

			if ((!pg->quiet) && (row_c % 10 == 0))
				/* For the impatients among us ...   */
				Eprintf(".");
		}
	}

	pdImagePNG(im, fd);

	pdImageDestroy(im);

	fflush(fd);

	if (!pg->quiet)
		Eprintf("\n");
	if (fd != stdout)
		fclose(fd);
	return 0;

      ERROR_EXIT:
	PError("write_PNG");
	return ERROR;
}