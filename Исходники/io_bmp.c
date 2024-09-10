int loadBMP4(FILE* fp, unsigned char* data, int w, int h, int band, int comp, unsigned char* red,
             unsigned char* blue, unsigned char* green)
{
	int i, j, c, c1, x, y, nybnum, rv, padw;
	unsigned char* pp;

	rv = 0;
	c = c1 = 0;

	/* read uncompressed data */
	if (comp == BI_RGB) {
		/* 'w' padded to a multiple of 8pix (32 bits) */
		padw = ((w + 7) / 8) * 8;

		for (i = h - 1; i >= 0; i--) {
			pp = data + (i * w * band);

			for (j = nybnum = 0; j < padw; j++, nybnum++) {
				/* read next unsigned char */
				if ((nybnum & 1) == 0) {
					c      = getc(fp);
					nybnum = 0;
				}

				if (j < w) {
					int s = (c & 0xf0) >> 4;
					*pp   = red[s];
					pp++;
					if (band == 3) {

						*pp = green[s];
						pp++;
						*pp = blue[s];
						pp++;
					}
					c <<= 4;
				}
			}
			if (FERROR(fp)) break;
		}