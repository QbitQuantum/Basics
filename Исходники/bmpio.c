myBMP * loadBMP(char *name)
{
FILE * inFile = NULL;
myBMP * mybm = NULL;
BITMAPINFOHEADER bmih;
BITMAPFILEHEADER bmfh;
ubyte bmpinfoheader[64];
ulong headerSize;
int mapentrysize = 0;		/* 0 indicates no colormap */
long bPad;
ulong my_row_bytes,bmp_row_bytes;

#define LBM_cleanUp(err) do { if ( inFile ) fclose(inFile); if ( mybm ) freeBMP(mybm); return( NULL); } while(0)

#define GET_2B(array,offset) ((uword) (ubyte)(array[offset+0]) + \
						 	(((uword) (ubyte)(array[offset+1])) << 8))
#define GET_4B(array,offset) ((ulong) (ubyte)(array[offset+0]) + \
						 	(((ulong) (ubyte)(array[offset+1])) << 8) + \
						 	(((ulong) (ubyte)(array[offset+2])) << 16) + \
						 	(((ulong) (ubyte)(array[offset+3])) << 24))
	
	if ( (inFile = fopen(name,"rb")) == NULL ) 
		LBM_cleanUp("fopen");

	/* Read and verify the bitmap file header */

	if (! FReadOk(inFile, &bmfh, sizeof(BITMAPFILEHEADER)))
		LBM_cleanUp("read short");

	if ( bmfh.bfType != BM_TAG )
		LBM_cleanUp("bmp sign");

	bPad = bmfh.bfOffBits;

	/* We ignore the remaining fileheader fields */

	/* The infoheader might be 12 bytes (OS/2 1.x), 40 bytes (Windows),
	 * or 64 bytes (OS/2 2.x).	Check the first 4 bytes to find out which.
	 */
	if (! FReadOk(inFile, bmpinfoheader, 4))
		LBM_cleanUp("read short");

	headerSize = (ulong) GET_4B(bmpinfoheader,0);

	if (headerSize < 12 || headerSize > 64)
		LBM_cleanUp("bad header size");

	if (! FReadOk(inFile, bmpinfoheader+4, headerSize-4))
		LBM_cleanUp("read short");

	if ( ( mybm = new(myBMP)) == NULL )
		LBM_cleanUp("malloc");

	memcpy((char *)(&(bmih)),bmpinfoheader,	min(sizeof(BITMAPINFOHEADER),headerSize));

	switch (bmih.biBitCount) 
	{
		case 8:			/* colormapped image */
			mapentrysize = 4;		/* Windows uses RGBQUAD colormap */
			if ( bmih.biClrUsed == 0 ) bmih.biClrUsed = 256;
			break;
		case 24:			/* RGB image */
			mapentrysize = 0;
			break;
		default:
			LBM_cleanUp("bad depth");
			break;
	}

	/* Compute distance to bitmap data --- will adjust for colormap below */
	bPad -= (headerSize + 14);

	/* Read the colormap, if any */
	if (mapentrysize > 0 && bmih.biClrUsed > 0) 
	{
		RGBQUAD pal[256];
		int i;

		mybm->ncolors = bmih.biClrUsed;
		if ( mybm->ncolors > 256 ) mybm->ncolors  = 256;

		if ( (mybm->palette = malloc(256*3)) == NULL )
			LBM_cleanUp("malloc");

		if (! FReadOk(inFile, pal , (mapentrysize * mybm->ncolors)))
			LBM_cleanUp("read short");

		for(i=0;i<mybm->ncolors;i++) 
		{
			mybm->palette[i*3 + 0] = pal[i].R;
			mybm->palette[i*3 + 1] = pal[i].G;
			mybm->palette[i*3 + 2] = pal[i].B;
		}

		/* account for size of colormap */
		bPad -= mybm->ncolors * mapentrysize;
	}

	/* Skip any remaining pad bytes */
	if (bPad < 0)			/* incorrect bfOffBits value? */
		LBM_cleanUp("bad header length");
	else if ( bPad > 0 ) 
	{
		fseek(inFile,bPad,SEEK_CUR);
	}

	/* Compute row width in file, including padding to 4-byte boundary */
	if (bmih.biBitCount == 24)	my_row_bytes = bmih.biWidth * 3;
	else						my_row_bytes = bmih.biWidth;

	bmp_row_bytes = (my_row_bytes+3)&(~3) ;

	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biSizeImage = bmp_row_bytes * abs(bmih.biHeight);

	mybm->width = bmih.biWidth;
	mybm->height = abs(bmih.biHeight);
	mybm->type = ( bmih.biBitCount == 24 ) ? MBTYPE_24BIT_RGB : MBTYPE_8BIT_PAL;

	mybm->dataBytes = my_row_bytes * mybm->height;

	if ( (mybm->data = malloc(mybm->dataBytes + bmp_row_bytes)) == NULL )
		LBM_cleanUp("malloc failed");

	{
	int step;
	ubyte * ptr;
	int y;
	ubyte garbage[4];

		if ( bmih.biHeight > 0 )
		{
			step = - (int)my_row_bytes;
			ptr = mybm->data + my_row_bytes * (mybm->height - 1);
		}
		else
		{
			step = my_row_bytes;
			ptr = mybm->data;
		}

		for(y=0;y<mybm->height;y++)
		{
			FRead(inFile,ptr,my_row_bytes);
			FRead(inFile,garbage,bmp_row_bytes - my_row_bytes);
			
			if (bmih.biBitCount == 24)
				swapBGRtoRGB(ptr,my_row_bytes);

			ptr += step;
		}
	}

	fclose(inFile); inFile = NULL;

return mybm;
}